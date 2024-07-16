// A simple benchmark tool around getrusage

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if !defined(_WIN32) && 0
#define HAVE_GETRUSAGE 1
#endif

#ifdef HAVE_GETRUSAGE 
#include <sys/resource.h>
#else
#include <plf_nanotimer_c_api.h>
#endif

#include "cmph_benchmark.h"

typedef struct {
  const char* name;
  void (*func)(int);
  int iters;
#ifdef HAVE_GETRUSAGE 
  struct rusage begin;
  struct rusage end;
#else
  nanotimer_data_t timer;
#endif
} benchmark_t;

static benchmark_t* global_benchmarks = NULL;

#ifdef HAVE_GETRUSAGE 

/* Subtract the `struct timeval' values X and Y,
   storing the result in RESULT.
   Return 1 if the difference is negative, otherwise 0.  */

int timeval_subtract ( 
    struct timeval *result, struct timeval *x, struct timeval* y) {
  /* Perform the carry for the later subtraction by updating y. */
  if (x->tv_usec < y->tv_usec) {
    int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
    y->tv_usec -= 1000000 * nsec;
    y->tv_sec += nsec;
  }
  if (x->tv_usec - y->tv_usec > 1000000) {
    int nsec = (x->tv_usec - y->tv_usec) / 1000000;
    y->tv_usec += 1000000 * nsec;
    y->tv_sec -= nsec;
  }

  /* Compute the time remaining to wait.
     tv_usec is certainly positive. */
  result->tv_sec = x->tv_sec - y->tv_sec;
  result->tv_usec = x->tv_usec - y->tv_usec;

  /* Return 1 if result is negative. */
  return x->tv_sec < y->tv_sec;
}

#endif

benchmark_t* find_benchmark(const char* name) {
  benchmark_t* benchmark = global_benchmarks;
  while (benchmark && benchmark->name != NULL) {
    if (strcmp(benchmark->name, name) == 0) break;
    ++benchmark;
  }
  if (!benchmark || !benchmark->name) return NULL;
  return benchmark;
}

int global_benchmarks_length() {
  benchmark_t* benchmark = global_benchmarks;
  int length = 0;
  if (benchmark == NULL) return 0;
  while (benchmark->name != NULL) ++length, ++benchmark;
  return length;
}

void bm_register(const char* name, void (*func)(int), int iters) {
  benchmark_t benchmark;
  int length = global_benchmarks_length();
  benchmark.name = name;
  benchmark.func = func;
  benchmark.iters = iters;
  assert(!find_benchmark(name));
  global_benchmarks = (benchmark_t *)realloc(
      global_benchmarks, (length + 2)*sizeof(benchmark_t));
  global_benchmarks[length] = benchmark;
  memset(&benchmark, 0, sizeof(benchmark_t));  // pivot
  global_benchmarks[length + 1] = benchmark;
}

void bm_start(const char* name) {
  benchmark_t* benchmark;

  benchmark = find_benchmark(name);
  assert(benchmark);
#ifdef HAVE_GETRUSAGE
 {
  struct rusage rs;

  int ret = getrusage(RUSAGE_SELF, &rs);
  if (ret != 0) {
    perror("rusage failed");    
    exit(-1);
  }
  benchmark->begin = rs;
 }
#else
  nanotimer(&benchmark->timer);
  nanotimer_start(&benchmark->timer);
#endif
  (*benchmark->func)(benchmark->iters);
}

void bm_end(const char* name) { 
  benchmark_t* benchmark;
#ifdef HAVE_GETRUSAGE 
  struct rusage rs;

  int ret = getrusage(RUSAGE_SELF, &rs);  
  if (ret != 0) {
    perror("rusage failed");    
    exit(-1);
  }
#endif

  benchmark = find_benchmark(name);
#ifdef HAVE_GETRUSAGE 
  benchmark->end = rs;

  struct timeval utime;
  timeval_subtract(&utime, &benchmark->end.ru_utime, &benchmark->begin.ru_utime);
  struct timeval stime;
  timeval_subtract(&stime, &benchmark->end.ru_stime, &benchmark->begin.ru_stime);
  
  printf("Benchmark: %s\n", benchmark->name);
  printf("User time used  : %ld.%06ld\n",
         utime.tv_sec, (long int)utime.tv_usec);
  printf("System time used: %ld.%06ld\n",
         stime.tv_sec, (long int)stime.tv_usec);
#else
  double t = nanotimer_get_elapsed_ms(&benchmark->timer);

  printf("Benchmark: %s\n", benchmark->name);
  printf("Time used  : %.6lf\n", t);
#endif
  printf("\n");
}
 
void run_benchmarks(int argc, const char** argv) {
  benchmark_t* benchmark = global_benchmarks;
  while (benchmark && benchmark->name != NULL) {
    bm_start(benchmark->name);
    bm_end(benchmark->name);
    ++benchmark;
  }
}

