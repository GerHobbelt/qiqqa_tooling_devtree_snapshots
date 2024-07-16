#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>

#include "flatten_iterator.h"

#include "monolithic_examples.h"

using namespace cxxmph;
using namespace std;


#if defined(BUILD_MONOLITHIC)
#define main		cmph_flatten_iterator_test_main
#endif

int main(int argc, const char** argv) {
  vector<int> flat;
  vector<vector<int>> v;
  v.push_back(vector<int>());
  for (int i = 0; i < 100; ++i) {
    v.push_back(vector<int>());
    for (int j = 0; j < 100; ++j) {
      v[i].push_back(j);
    }
  }
  flat.clear();
  for (const auto& ie : v) {
    for (const auto& je : ie) {
      flat.push_back(je);
    }
  }
  auto begin = make_flatten_begin(&v);
  auto end = make_flatten_end(&v);
  uint32_t i = 0;
  for (auto it = begin; it != end; ++it, ++i) {
    if (i > flat.size()) {
			fprintf(stderr, "size error\n");
			return EXIT_FAILURE;
		}
    if (flat[i] != *it) {
      fprintf(stderr, "expected: %d got %d\n", flat[i], *it);
			return EXIT_FAILURE;
    }
  }

  v[v.size()-1].clear();
  flat.clear();
  for (const auto& ie : v) {
    for (const auto& je : ie) {
      flat.push_back(je);
    }
  }
  begin = make_flatten_begin(&v);
  end = make_flatten_end(&v);
  i = 0;
  for (auto it = begin; it != end; ++it, ++i) {
    if (i > flat.size()) {
			fprintf(stderr, "size error\n");
			return EXIT_FAILURE;
		}
    if (flat[i] != *it) {
      fprintf(stderr, "expected: %d got %d\n", flat[i], *it);
			return EXIT_FAILURE;
    }
  }

  v[v.size()/2].clear();
  flat.clear();
  for (const auto& ie : v) {
    for (const auto& je : ie) {
      flat.push_back(je);
    }
  }
  begin = make_flatten_begin(&v);
  end = make_flatten_end(&v);
  i = 0;
  for (auto it = begin; it != end; ++it, ++i) {
    if (i > flat.size()) {
			fprintf(stderr, "size error\n");
			return EXIT_FAILURE;
		}
    if (flat[i] != *it) {
      fprintf(stderr, "expected: %d got %d\n", flat[i], *it);
			return EXIT_FAILURE;
    }
  }
  
  flatten_const_iterator<vector<vector<int>>> const_begin(begin);
  flatten_const_iterator<vector<vector<int>>> const_end(end);
  i = 0;
  for (auto it = const_begin; it != const_end; ++it, ++i) {
    if (flat[i] != *it) return EXIT_FAILURE;
  }
  auto it1 = make_flatten_begin(&v);
  auto it2 = make_flatten_begin(&v);
  if (it1 != it2) return EXIT_FAILURE;

  flatten_iterator<vector<vector<int>>> default_constructed;
  default_constructed = flatten_iterator<vector<vector<int>>>(&v, v.begin());

  vector<vector<pair<string, string>>> vs;
  vector<vector<pair<string, string>>>::iterator myot;
  vector<pair<string, string>>::iterator myit;
  make_flatten(&vs, myot, myit);

	return EXIT_SUCCESS;
}
