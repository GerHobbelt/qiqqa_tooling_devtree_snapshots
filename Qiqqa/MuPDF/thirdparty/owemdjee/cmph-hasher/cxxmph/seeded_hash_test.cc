#include "seeded_hash.h"

#include <unordered_map>
#include <string>
#include <iostream>

#include "monolithic_examples.h"

using std::cerr;
using std::endl;
using std::string;
using std::unordered_map;
using namespace cxxmph;


#if defined(BUILD_MONOLITHIC)
#define main		cmph_seeded_has_test_main
#endif

int main(int argc, const char** argv) {
  auto hasher = seeded_hash_function<Murmur3StringPiece>();
  string key1("0");
  string key2("1");
  auto h1 = hasher.hash128(key1, 1);
  auto h2 = hasher.hash128(key2, 1);
  if (h1 == h2) {
    fprintf(stderr, "unexpected murmur collision\n");
    return EXIT_FAILURE;
  }

  unordered_map<uint64_t, int> g;
  for (int i = 0; i < 1000; ++i) g[i] = i;
  for (int i = 0; i < 1000; ++i) if (g[i] != i) return EXIT_FAILURE;

  auto inthasher = seeded_hash_function<std::hash<uint64_t>>();
  unordered_map<h128, uint64_t, h128::hash32> g2;
  for (uint64_t i = 0; i < 1000; ++i) {
    auto h = inthasher.hash128(i, 0);
    if (g2.find(h) != g2.end()) {
      std::cerr << "Incorrectly found " << i << std::endl;
      return EXIT_FAILURE;
    }
    if (h128::hash32()(h) != h[3]) {
      cerr << "Buggy hash method." << endl;
      return EXIT_FAILURE;
    }
    auto h2 = inthasher.hash128(i, 0);
    if (!(h == h2)) {
      cerr << "h 64(0) " << h.get64(0) << " h 64(1) " << h.get64(1) << endl;
      cerr << " h2 64(0) " << h2.get64(0) << " h2 64(1) " << h2.get64(1) << endl;
      cerr << "Broken equality for h128" << endl;
      return EXIT_FAILURE;
    }
    if (h128::hash32()(h) != h128::hash32()(h2)) {
      cerr << "Inconsistent hash method." << endl;
      return EXIT_FAILURE;
    }
    g2[h] = i;
    if (g2.find(h) == g2.end()) {
      std::cerr << "Incorrectly missed " << i << std::endl;
      return EXIT_FAILURE;
    }
  }
    
  for (uint64_t i = 0; i < 1000; ++i) if (g2[inthasher.hash128(i, 0)] != i) return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
