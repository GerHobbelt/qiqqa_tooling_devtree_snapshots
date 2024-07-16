#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "mph_index.h"

#include "monolithic_examples.h"

using std::cerr;
using std::endl;
using std::string;
using std::vector;
using namespace cxxmph;


#if defined(BUILD_MONOLITHIC)
#define main		cmph_mph_index_test_main
#endif

int main(int argc, const char** argv) {

  srand(1);
  vector<string> keys;
  keys.push_back("davi");
  keys.push_back("paulo");
  keys.push_back("joao");
  keys.push_back("maria");
  keys.push_back("bruno");
  keys.push_back("paula");
  keys.push_back("diego");
  keys.push_back("diogo");
  keys.push_back("algume");

  SimpleMPHIndex<string> mph_index;
  if (!mph_index.Reset(keys.begin(), keys.end(), keys.size())) { return EXIT_FAILURE; }
  vector<int> ids;
  for (vector<int>::size_type i = 0; i < keys.size(); ++i) {
     ids.push_back(mph_index.index(keys[i]));
     cerr << " " << *(ids.end() - 1);
  }
  cerr << endl;
  sort(ids.begin(), ids.end());
  for (vector<int>::size_type i = 0; i < ids.size(); ++i) assert(ids[i] == static_cast<vector<int>::value_type>(i));

  vector<int> k2;
  for (int i = 0; i < 512;  ++i) { k2.push_back(i); }
  SimpleMPHIndex<int> k2_index;
  if (!k2_index.Reset(k2.begin(), k2.end(), k2.size())) { return EXIT_FAILURE; }

  // Test serialization
  vector<uint32_t> params;
  dynamic_2bitset g;
  vector<uint32_t> ranktable;
  mph_index.swap(params, g, ranktable);
  assert(mph_index.size() == 0);
  mph_index.swap(params, g, ranktable);
  assert(mph_index.size() == ids.size());
  for (vector<int>::size_type i = 0; i < ids.size(); ++i) assert(ids[i] == static_cast<vector<int>::value_type>(i));

  FlexibleMPHIndex<false, true, int64_t, seeded_hash<std::hash<int64_t>>::hash_function> square_empty;
  auto id = square_empty.index(1);
  FlexibleMPHIndex<false, false, int64_t, seeded_hash<std::hash<int64_t>>::hash_function> unordered_empty;
  id ^= unordered_empty.index(1);
  FlexibleMPHIndex<true, false, int64_t, seeded_hash<std::hash<int64_t>>::hash_function> minimal_empty;
  id ^= minimal_empty.index(1);

  return EXIT_SUCCESS;
}
