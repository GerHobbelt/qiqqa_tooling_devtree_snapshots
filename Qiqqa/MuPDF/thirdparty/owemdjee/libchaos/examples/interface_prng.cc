#include <chaos.h>
#include <chaos/monolithic_examples.h>

CHAOS_PRNG_XOROSHIRO128PLUS prng;

static int test_and_check(uint64_t sollwert, uint64_t check = 0)
{
	auto c = prng.next();
	check += c;

	int rv = (check != sollwert);
	if (rv)
		fprintf(stderr, "Test failed (sollwert: 0x%016zx, actual: 0x%016zx)\n", (size_t)sollwert, (size_t)check);
	return rv;
}

#if defined(BUILD_MONOLITHIC)
#define main chaos_interface_main
#endif

int main(void) {
	uint64_t a = 0x84242f96eca9c41d, b = 0xa3c65b8776f96855, c, check;

	// SEED
	prng.seed(a);
	if (test_and_check(0x964401ac48f0f3b3ULL))
		return 1;

	// reseed:
	prng << b;

	// NEXT
	check = 0;
	c = prng.next();
	check += c;
	c << prng;
	check += c;
	c = prng();
	check += c;

	if (test_and_check(0x7f00bd5b586a65a8ULL, check))
		return 1;

	return 0;
}
