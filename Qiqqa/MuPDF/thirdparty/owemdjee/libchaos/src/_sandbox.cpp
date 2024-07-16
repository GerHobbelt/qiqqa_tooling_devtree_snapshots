#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>

#include <chaos.h>
#include <chaos/monolithic_examples.h>

#if defined(BUILD_MONOLITHIC)
#define main chaos_sandbox_main
#endif

int main() {
	std::random_device rd;

	CHAOS_MACHINE_NCG gen;
	CHAOS_PRNG_KISS prng;

	prng << 0x55;
	printf("\n");

	chaos::truely<CHAOS_MACHINE_NCG, std::random_device> x(100);

	for (size_t i = 0; i < 5000; i++)
		printf(">> 0x%016zx\n", (uint64_t)x());

	printf("SEED: 0x%016zx\n", (uint64_t)rd());

	gen << 0x44;
	gen.push(0x55);

	uint32_t a = 0x66;

	gen << a << 0x55;
	gen.push(a);

	uint32_t b, c;
	gen >> b >> c;

	printf("--> 0x%016zx\n", (uint64_t)b);
	printf("--> 0x%016zx\n", (uint64_t)c);
	printf("--> 0x%016zx\n", (uint64_t)gen());
	printf("--> 0x%016zx\n", (uint64_t)gen.pull());

	std::normal_distribution<> d(5, 2);

	std::map<int, int> hist;

	for (int n = 0; n < 100000; ++n)
		++hist[std::round(d(x))];

	for (auto p : hist)
		std::cout << std::fixed << std::setprecision(1) << std::setw(2) << p.first
		          << ' ' << std::string(p.second / 200, '*') << '\n';

	return 0;
}
