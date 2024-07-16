#include <cstdio>
#include <vector>
#include "debruijn_index.h" 
#include "mph_bits.h"

#include "monolithic_examples.h"

using namespace std;
using cxxmph::debruijn_index;
using cxxmph::reseed32;


#if defined(BUILD_MONOLITHIC)
#define main		cmph_debruijn_index_main
#endif

int main(int argc, const char** argv) {
  srand(8);
  uint32_t seed = rand();
  debruijn_index ri(16);
  if (!ri.insert(reseed32(8, seed), 4)) {
    fprintf(stderr, "Insertion failed\n");
  }
  if (ri.size() != 1) {
    fprintf(stderr, "Wrong size: %d\n", ri.size());
		return EXIT_FAILURE;
  }
  if (ri.index(reseed32(8, seed)) != 0) {
    fprintf(stderr, "Found key at wrong index %d\n", ri.index(3));
		return EXIT_FAILURE;
  }
  for (int i = 0; i < 8; ++i) {
    if (!ri.insert(reseed32(i, seed), 4)) {
      fprintf(stderr, "The %d th insertion failed\n", i);
			return EXIT_FAILURE;
    }
  }
  vector<bool> p(9);
  for (int i = 0; i < 9; ++i) {
    if (p[ri.index(reseed32(i, seed))]) {
      fprintf(stderr, "The %d key collided at %d\n", i, ri.index(i));
			return EXIT_FAILURE;
    }
    p[ri.index(reseed32(i, seed))] = true;
  }
  for (int i = 0; i < 4; ++i) {
    if (!p[i]) {
      fprintf(stderr, "Missed key %d\n", i);
			return EXIT_FAILURE;
    }
  }
	return EXIT_SUCCESS;
}
