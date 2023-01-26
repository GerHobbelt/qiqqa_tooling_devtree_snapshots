#include <iostream>
#include <gflags/gflags.h>

#include "monolithic_examples.h"


DEFINE_string(message, "Hello World!", "The message to print");

static bool ValidateMessage(const char* flagname, const std::string &message)
{
  return !message.empty();
}
DEFINE_validator(message, ValidateMessage);



#if defined(BUILD_MONOLITHIC)
#define main(cnt, arr)      gflags_test_config_main(cnt, arr)
#endif

int main(int argc, const char** argv)
{
  gflags::SetUsageMessage("Test CMake configuration of gflags library (gflags-config.cmake)");
  gflags::SetVersionString("0.1");
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  std::cout << FLAGS_message << std::endl;
  gflags::ShutDownCommandLineFlags();
  return 0;
}
