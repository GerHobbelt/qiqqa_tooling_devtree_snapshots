#include "benchmark/benchmark.h"

static void BM_empty(benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(state.iterations());
  }
}
BENCHMARK(BM_empty);
