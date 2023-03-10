///////////////////////////////////////////////////////////////////////
// File:        lstmtraining.cpp
// Description: Training program for LSTM-based networks.
// Author:      Ray Smith
//
// (C) Copyright 2013, Google Inc.
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
///////////////////////////////////////////////////////////////////////

#ifdef HAVE_TESSERACT_CONFIG_H
#  include "config_auto.h"
#endif

#include <tesseract/debugheap.h>

#include <cerrno>
#if defined(__USE_GNU)
#  include <cfenv> // for feenableexcept
#endif
#include "common/commontraining.h"
#include "unicharset/fileio.h"             // for LoadFileLinesToStrings
#include "unicharset/lstmtester.h"
#include "unicharset/lstmtrainer.h"
#include "params.h"
#include "tprintf.h"
#include "unicharset/unicharset_training_utils.h"

using namespace tesseract;

FZ_HEAPDBG_TRACKER_SECTION_START_MARKER(_)

static INT_PARAM_FLAG(debug_interval, 0, "How often to display the alignment.");
static STRING_PARAM_FLAG(net_spec, "", "Network specification");
static INT_PARAM_FLAG(net_mode, 192, "Controls network behavior.");
static INT_PARAM_FLAG(perfect_sample_delay, 0, "How many imperfect samples between perfect ones.");
static DOUBLE_PARAM_FLAG(target_error_rate, 0.01, "Final error rate in percent.");
static DOUBLE_PARAM_FLAG(weight_range, 0.1, "Range of initial random weights.");
static DOUBLE_PARAM_FLAG(learning_rate, 10.0e-4, "Weight factor for new deltas.");
static BOOL_PARAM_FLAG(reset_learning_rate, false,
                       "Resets all stored learning rates to the value specified by --learning_rate.");
static DOUBLE_PARAM_FLAG(momentum, 0.5, "Decay factor for repeating deltas.");
static DOUBLE_PARAM_FLAG(adam_beta, 0.999, "Decay factor for repeating deltas.");
#if !defined(BUILD_MONOLITHIC)
static INT_PARAM_FLAG(max_image_MB, 6000, "Max memory to use for images.");
#else
DECLARE_INT_PARAM_FLAG(max_image_MB);        // already declared in lstmeval.cpp
#endif
static STRING_PARAM_FLAG(continue_from, "", "Existing model to extend");
static STRING_PARAM_FLAG(model_output, "lstmtrain", "Basename for output models");
static STRING_PARAM_FLAG(train_listfile, "",
                         "File listing training files in lstmf training format.");
#if !defined(BUILD_MONOLITHIC)
static STRING_PARAM_FLAG(eval_listfile, "", "File listing eval files in lstmf training format.");
#else
DECLARE_STRING_PARAM_FLAG(eval_listfile);        // already declared in lstmeval.cpp
#endif
#if defined(__USE_GNU)
static BOOL_PARAM_FLAG(debug_float, false, "Raise error on certain float errors.");
#endif
static BOOL_PARAM_FLAG(stop_training, false, "Just convert the training model to a runtime model.");
static BOOL_PARAM_FLAG(convert_to_int, false, "Convert the recognition model to an integer model.");
static BOOL_PARAM_FLAG(sequential_training, false,
                       "Use the training files sequentially instead of round-robin.");
static INT_PARAM_FLAG(append_index, -1,
                      "Index in continue_from Network at which to"
                      " attach the new network defined by net_spec");
static BOOL_PARAM_FLAG(debug_network, false, "Get info on distribution of weight values");
static INT_PARAM_FLAG(max_iterations, 0, "If set, exit after this many iterations");
#if !defined(BUILD_MONOLITHIC)
static STRING_PARAM_FLAG(traineddata, "", "Combined Dawgs/Unicharset/Recoder for language model");
#else
DECLARE_STRING_PARAM_FLAG(traineddata);        // already declared in lstmeval.cpp
#endif
static STRING_PARAM_FLAG(old_traineddata, "",
                         "When changing the character set, this specifies the old"
                         " character set that is to be replaced");
static BOOL_PARAM_FLAG(randomly_rotate, false,
                       "Train OSD and randomly turn training samples upside-down");

// Number of training images to train between calls to MaintainCheckpoints.
const int kNumPagesPerBatch = 100;

FZ_HEAPDBG_TRACKER_SECTION_END_MARKER(_)

// Apart from command-line flags, input is a collection of lstmf files, that
// were previously created using tesseract with the lstm.train config file.
// The program iterates over the inputs, feeding the data to the network,
// until the error rate reaches a specified target or max_iterations is reached.
#if defined(TESSERACT_STANDALONE) && !defined(BUILD_MONOLITHIC)
extern "C" int main(int argc, const char** argv)
#else
extern "C" int tesseract_lstm_training_main(int argc, const char** argv)
#endif
{
  tesseract::CheckSharedLibraryVersion();
  ParseArguments(&argc, &argv);
#if defined(__USE_GNU)
  if (FLAGS_debug_float) {
    // Raise SIGFPE for unwanted floating point calculations.
    feenableexcept(FE_DIVBYZERO | FE_OVERFLOW | FE_INVALID);
  }
#endif
  if (FLAGS_model_output.empty()) {
    tprintf("ERROR: Must provide a --model_output!\n");
    return EXIT_FAILURE;
  }
  if (FLAGS_traineddata.empty()) {
    tprintf("ERROR: Must provide a --traineddata, see training documentation\n");
    return EXIT_FAILURE;
  }

  // Check write permissions.
  std::string test_file = FLAGS_model_output.c_str();
  test_file += "_wtest";
  FILE *f = fopen(test_file.c_str(), "wb");
  if (f != nullptr) {
    fclose(f);
    if (remove(test_file.c_str()) != 0) {
      tprintf("ERROR: Failed to remove {}: {}\n", test_file.c_str(), strerror(errno));
      return EXIT_FAILURE;
    }
  } else {
    tprintf("ERROR: Model output cannot be written: {}\n", strerror(errno));
    return EXIT_FAILURE;
  }

  // Setup the trainer.
  std::string checkpoint_file = FLAGS_model_output.c_str();
  checkpoint_file += "_checkpoint";
  std::string checkpoint_bak = checkpoint_file + ".bak";
  tesseract::LSTMTrainer trainer(FLAGS_model_output.c_str(), checkpoint_file.c_str(),
                                 FLAGS_debug_interval,
                                 static_cast<int64_t>(FLAGS_max_image_MB) * 1048576);
#if !defined(NDEEBUG)
  trainer.SetDebug(true);
#endif
  if (!trainer.InitCharSet(FLAGS_traineddata.c_str())) {
    tprintf("ERROR: Failed to read {}\n", FLAGS_traineddata.c_str());
    return EXIT_FAILURE;
  }

  // Reading something from an existing model doesn't require many flags,
  // so do it now and exit.
  if (FLAGS_stop_training || FLAGS_debug_network) {
    if (!trainer.TryLoadingCheckpoint(FLAGS_continue_from.c_str(), nullptr)) {
      tprintf("ERROR: Failed to read continue from: {}\n", FLAGS_continue_from.c_str());
      return EXIT_FAILURE;
    }
    if (FLAGS_debug_network) {
      trainer.DebugNetwork();
    } else {
      if (FLAGS_convert_to_int) {
        trainer.ConvertToInt();
      }
      if (!trainer.SaveTraineddata(FLAGS_model_output.c_str())) {
        tprintf("ERROR: Failed to write recognition model : {}\n", FLAGS_model_output.c_str());
      }
    }
    return EXIT_SUCCESS;
  }

  // Get the list of files to process.
  if (FLAGS_train_listfile.empty()) {
    tprintf("ERROR: Must supply a list of training filenames! --train_listfile\n");
    return EXIT_FAILURE;
  }
  std::vector<std::string> filenames;
  if (!tesseract::LoadFileLinesToStrings(FLAGS_train_listfile.c_str(), &filenames)) {
    tprintf("ERROR: Failed to load list of training filenames from {}\n", FLAGS_train_listfile.c_str());
    return EXIT_FAILURE;
  }

  // Checkpoints always take priority if they are available.
  if (trainer.TryLoadingCheckpoint(checkpoint_file.c_str(), nullptr) ||
      trainer.TryLoadingCheckpoint(checkpoint_bak.c_str(), nullptr)) {
    tprintf("Successfully restored trainer from {}\n", checkpoint_file.c_str());
  } else {
    if (!FLAGS_continue_from.empty()) {
      // Load a past model file to improve upon.
      if (!trainer.TryLoadingCheckpoint(FLAGS_continue_from.c_str(),
                                        FLAGS_append_index >= 0 ? FLAGS_continue_from.c_str()
                                                                : FLAGS_old_traineddata.c_str())) {
        tprintf("ERROR: Failed to continue from: {}\n", FLAGS_continue_from.c_str());
        return EXIT_FAILURE;
      }
      tprintf("Continuing from {}\n", FLAGS_continue_from.c_str());
      if (FLAGS_reset_learning_rate) {
        trainer.SetLearningRate(FLAGS_learning_rate);
        tprintf("Set learning rate to {}\n", static_cast<float>(FLAGS_learning_rate));
      }
      trainer.InitIterations();
    }
    if (FLAGS_continue_from.empty() || FLAGS_append_index >= 0) {
      if (FLAGS_append_index >= 0) {
        tprintf("Appending a new network to an old one!!");
        if (FLAGS_continue_from.empty()) {
          tprintf("ERROR: Must set --continue_from for appending!\n");
          return EXIT_FAILURE;
        }
      }
      // We are initializing from scratch.
      if (!trainer.InitNetwork(FLAGS_net_spec.c_str(), FLAGS_append_index, FLAGS_net_mode,
                               FLAGS_weight_range, FLAGS_learning_rate, FLAGS_momentum,
                               FLAGS_adam_beta)) {
        tprintf("ERROR: Failed to create network from spec: {}\n", FLAGS_net_spec.c_str());
        return EXIT_FAILURE;
      }
      trainer.set_perfect_delay(FLAGS_perfect_sample_delay);
    }
  }
  if (!trainer.LoadAllTrainingData(
          filenames,
          FLAGS_sequential_training ? tesseract::CS_SEQUENTIAL : tesseract::CS_ROUND_ROBIN,
          FLAGS_randomly_rotate)) {
    tprintf("ERROR: Load of images failed!!\n");
    return EXIT_FAILURE;
  }

  tesseract::LSTMTester tester(static_cast<int64_t>(FLAGS_max_image_MB) * 1048576);
  tesseract::TestCallback tester_callback = nullptr;
  if (!FLAGS_eval_listfile.empty()) {
    using namespace std::placeholders; // for _1, _2, _3...
    if (!tester.LoadAllEvalData(FLAGS_eval_listfile.c_str())) {
      tprintf("ERROR: Failed to load eval data from: {}\n", FLAGS_eval_listfile.c_str());
      return EXIT_FAILURE;
    }
    tester_callback = std::bind(&tesseract::LSTMTester::RunEvalAsync, &tester, _1, _2, _3, _4);
  }

  int max_iterations = FLAGS_max_iterations;
  if (max_iterations < 0) {
    // A negative value is interpreted as epochs
    max_iterations = filenames.size() * (-max_iterations);
  } else if (max_iterations == 0) {
    // "Infinite" iterations.
    max_iterations = INT_MAX;
  }

  do {
    // Train a few.
    int iteration = trainer.training_iteration();
    for (int target_iteration = iteration + kNumPagesPerBatch;
         iteration < target_iteration && iteration < max_iterations;
         iteration = trainer.training_iteration()) {
      trainer.TrainOnLine(&trainer, false);
    }
    std::string log_str;
    trainer.MaintainCheckpoints(tester_callback, log_str);
    tprintf("{}\n", log_str.c_str());
  } while (trainer.best_error_rate() > FLAGS_target_error_rate &&
           (trainer.training_iteration() < max_iterations));
  tprintf("Finished! Selected model with minimal training error rate (BCER) = {}\n",
          trainer.best_error_rate());
  return EXIT_SUCCESS;
} /* main */
