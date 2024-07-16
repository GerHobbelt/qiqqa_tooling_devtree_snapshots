#include <cstdio>
#include <cstdlib>

#include "mph_bits.h"

#include "monolithic_examples.h"

using namespace cxxmph;

using cxxmph::dynamic_2bitset;
using cxxmph::nextpoweroftwo;


#if defined(BUILD_MONOLITHIC)
#define main		cmph_mph_bits_test_main
#endif

int main(int argc, const char** argv) {
  if ((branch_free_end(15, ones())) != -1) return EXIT_FAILURE;
  if ((branch_free_end(15, 0)) != 15) return EXIT_FAILURE;
#if 0
	if ((branch_free_end2(15, 16, ones())) != 16) {
    fprintf(stderr, "bfe2: %d\n", branch_free_end2(15, 16, ones()));
    return EXIT_FAILURE;
  }
  if ((branch_free_end2(15, 16, 0)) != 15) return EXIT_FAILURE;
#endif
	dynamic_2bitset small(256, true);
  for (uint32_t i = 0; i < small.size(); ++i) small.set(i, i % 4);
  for (uint32_t i = 0; i < small.size(); ++i) {
    if (small[i] != i % 4) {
      fprintf(stderr, "wrong bits %d at %d expected %d\n", small[i], i, i % 4);
      return EXIT_FAILURE;
    }
  }

  uint32_t size = 256;
  dynamic_2bitset bits(size, true /* fill with ones */);
  for (uint32_t i = 0; i < size; ++i) {
    if (bits[i] != 3)  {
      fprintf(stderr, "wrong bits %d at %d expected %d\n", bits[i], i, 3);
      return EXIT_FAILURE;
    }
  }
  for (uint32_t i = 0; i < size; ++i) bits.set(i, 0);
  for (uint32_t i = 0; i < size; ++i) {
    if (bits[i] != 0)  {
      fprintf(stderr, "wrong bits %d at %d expected %d\n", bits[i], i, 0);
      return EXIT_FAILURE;
    }
  }
  for (uint32_t i = 0; i < size; ++i) bits.set(i, i % 4);
  for (uint32_t i = 0; i < size; ++i) {
    if (bits[i] != i % 4) {
      fprintf(stderr, "wrong bits %d at %d expected %d\n", bits[i], i, i % 4);
      return EXIT_FAILURE;
    }
  }
  dynamic_2bitset size_corner1(1);
  if (size_corner1.size() != 1) return EXIT_FAILURE;
  dynamic_2bitset size_corner2(2);
  if (size_corner2.size() != 2) return EXIT_FAILURE;
  (dynamic_2bitset(4, true)).swap(size_corner2);
  if (size_corner2.size() != 4) return EXIT_FAILURE;
  for (uint32_t i = 0; i < size_corner2.size(); ++i) {
    if (size_corner2[i] != 3) return EXIT_FAILURE;
  }
  size_corner2.clear();
  if (size_corner2.size() != 0) return EXIT_FAILURE;

  dynamic_2bitset empty;
  empty.clear();
  dynamic_2bitset large(1000, true);
  empty.swap(large);
  
  if (rank64(0) != 0) return EXIT_FAILURE;
  if (rank64(1) != 1) return EXIT_FAILURE;
  if (rank64(2) != 1) return EXIT_FAILURE;
  if (rank64(255) != 8) return EXIT_FAILURE;
  if (rank64(ones()) != 64) return EXIT_FAILURE;
  
  if (nextpoweroftwo(3) != 4) return EXIT_FAILURE;
  uint32_t de_bruijn32 = 0x4653adf;
  for (int i = 0; i < 32; ++i) {
    uint32_t b = 1 << i;
    // b &= -b;
    b *= de_bruijn32;
    b >>= 27;  // 32 - log(32)
  }
  uint64_t de_bruijn64 = 0x218a392cd3d5dbfULL;
  for (int i = 0; i < 64; ++i) {
    uint64_t b = 1ULL << i;
    // b &= -b;
    b *= de_bruijn64;
    b >>= 64-6;  // 64 - log(64)
  }

  return EXIT_SUCCESS;
}
