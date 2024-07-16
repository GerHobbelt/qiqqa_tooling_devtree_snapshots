#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

#include "mph_map.h"
#include "map_tester.h"
#include "test.h"

#include "monolithic_examples.h"

using namespace cxxmph;


#if defined(BUILD_MONOLITHIC)
#define main		cmph_mph_map_test_main
#endif

int main(int argc, const char** argv) {
  mph_map<int64_t, int64_t> b;
  int32_t num_keys = 1000*10;
  for (int i = 0; i < num_keys; ++i) {
    b.insert(make_pair(i, i));
  }
  b.rehash(b.size());
  for (int i = 0; i < 1000000; ++i) {
    auto it = b.find(i % num_keys);
    if (it == b.end()) {
      std::cerr << "Failed to find " << i << std::endl;
      return EXIT_FAILURE;
    }
    if (it->first != it->second || it->first != i % num_keys) {
      std::cerr << "Found " << it->first << " looking for " << i << std::endl;
      return EXIT_FAILURE;
    }
  }

  mph_map<string, int> h;
  h.insert(std::make_pair("-1",-1));
  mph_map<string, int>::const_iterator it;
  for (it = h.begin(); it != h.end(); ++it) {
    if (it->second != -1) return EXIT_FAILURE;
  }
  int32_t num_valid = 100;
  for (int i = 0; i < num_valid; ++i) {
     char buf[10];    
     snprintf(buf, 10, "%d", i);
     h.insert(std::make_pair(buf, i));
  }
  for (int j = 0; j < 100; ++j) {
    for (int i = 1000; i > 0; --i) {
       char buf[10];    
       snprintf(buf, 10, "%d", i - 1);
       auto it = h.find(buf);
       if (i < num_valid && it->second != i - 1) return EXIT_FAILURE;
    }
  }
  for (int j = 0; j < 100; ++j) {
    for (int i = 1000; i > 0; --i) {
       char buf[10];    
       int key = i*100 - 1;
       snprintf(buf, 10, "%d", key);
       auto it = h.find(buf);
       if (key < num_valid && it->second != key) return EXIT_FAILURE;
    }
  }
  fprintf(stderr, "Size is %zu\n", h.size());
  for (int i = 0; i < num_valid; ++i) {
     char buf[10];    
     snprintf(buf, 10, "%d", i);
     h.erase(buf);
  }
  if (h.size() != 1) {
    fprintf(stderr, "Erase failed: size is %zu\n", h.size());
    return EXIT_FAILURE;
  }
	return EXIT_SUCCESS;
}



#if 0

typedef MapTester<mph_map> Tester;

CXXMPH_CXX_TEST_CASE(empty_find, Tester::empty_find);
CXXMPH_CXX_TEST_CASE(empty_erase, Tester::empty_erase);
CXXMPH_CXX_TEST_CASE(small_insert, Tester::small_insert);
CXXMPH_CXX_TEST_CASE(large_insert, Tester::large_insert);
CXXMPH_CXX_TEST_CASE(small_search, Tester::small_search);
CXXMPH_CXX_TEST_CASE(default_search, Tester::default_search);
CXXMPH_CXX_TEST_CASE(large_search, Tester::large_search);
CXXMPH_CXX_TEST_CASE(string_search, Tester::string_search);
CXXMPH_CXX_TEST_CASE(rehash_zero, Tester::rehash_zero);
CXXMPH_CXX_TEST_CASE(rehash_size, Tester::rehash_size);
CXXMPH_CXX_TEST_CASE(erase_value, Tester::erase_value);
CXXMPH_CXX_TEST_CASE(erase_iterator, Tester::erase_iterator);

#endif
