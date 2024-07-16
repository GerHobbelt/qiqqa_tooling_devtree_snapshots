#ifndef _WIN32
#include <unistd.h>  // for sleep
#else
#include <windows.h>
static void sleep(int n) {
	Sleep(n * 1000);
}
#endif
#include <limits.h>

#include "cmph_benchmark.h"

#include "monolithic_examples.h"

static void bm_sleep(int iters) {
  sleep(1);
}

static void bm_increment(int iters) {
  int i, v = 0;
  for (i = 0; i < INT_MAX; ++i) {
    v += i;
  }
}


#if defined(BUILD_MONOLITHIC)
#define main		cmph_benchmark_test_main
#endif

int main(int argc, const char** argv) {
  BM_REGISTER(bm_sleep, 1);
  BM_REGISTER(bm_increment, 1);
  run_benchmarks(argc, argv);
  return 0;
}

