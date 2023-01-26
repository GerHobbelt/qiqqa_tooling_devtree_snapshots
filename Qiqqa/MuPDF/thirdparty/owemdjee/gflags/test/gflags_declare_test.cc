#include <gflags/gflags.h>

#include "monolithic_examples.h"


#if defined(BUILD_MONOLITHIC)
DECLARE_string(message); // in gflags_delcare_test.cc
#else
DEFINE_string(message, "", "The message to print");
#endif
void gflags_print_message(); // in gflags_declare_flags.cc



#if defined(BUILD_MONOLITHIC)
#define main(cnt, arr)      gflags_test_declare_main(cnt, arr)
#endif

int main(int argc, const char** argv)
{
  GFLAGS_NAMESPACE::SetUsageMessage("Test compilation and use of gflags_declare.h");
  GFLAGS_NAMESPACE::ParseCommandLineFlags(&argc, &argv, true);
  gflags_print_message();
  return 0;
}
