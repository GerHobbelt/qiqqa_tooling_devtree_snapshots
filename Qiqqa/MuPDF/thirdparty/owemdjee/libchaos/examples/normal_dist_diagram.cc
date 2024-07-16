#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>

#include <chaos.h>
#include <chaos/monolithic_examples.h>

CHAOS_MACHINE_NCG gen;

#if defined(BUILD_MONOLITHIC)
#define main chaos_normal_dist_diagram_main
#endif

int main(void) {
	std::normal_distribution<> d(5, 2);
	std::map<int, int> hist;

	for (int n = 0; n < 5 * 10000; ++n)
		++hist[std::round(d(gen))];

	for (auto p : hist)
		std::cout << std::fixed << std::setprecision(1) << std::setw(2) << p.first
		          << ' ' << std::string(p.second / 200, '*') << '\n';

	return 0;
}
