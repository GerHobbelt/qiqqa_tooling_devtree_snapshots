#include <chrono>
#include <csv2/reader.hpp>
#include <iostream>

#include "monolithic_examples.h"

#if defined(BUILD_MONOLITHIC)
#define main		csv2_fieldcount_main
#endif

using namespace csv2;

int main(int argc, const char **argv) {
  if (argc != 2) {
    std::cout << "Usage: ./fieldcount <csv_file>\n";
    return EXIT_FAILURE;
  }

  Reader<delimiter<','>, quote_character<'"'>, first_row_is_header<false>> csv;
  if (csv.mmap(argv[1])) {
    size_t cells{0};
    for (const auto row : csv) {
      for (const auto cell : row) {
        cells += 1;
      }
    }
    std::cout << cells << "\n";
	return EXIT_SUCCESS;
  } else {
    std::cout << "0\n";
	return EXIT_SUCCESS;
  }
}
