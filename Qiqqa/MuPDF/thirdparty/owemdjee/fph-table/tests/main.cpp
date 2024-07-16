
#include "monolithic_examples.h"

void TestSet();
void TestFPH();
void TestMapPerformance();

#if defined(BUILD_MONOLITHIC)
#define main    fph_tests_main
#endif

int main() {
    TestSet();
    TestFPH();
    TestMapPerformance();
    return 0;
}
