#include <chaos.h>
#include <chaos/monolithic_examples.h>

chaos::truely<CHAOS_MACHINE_XORRING64, std::random_device> gen;

#if defined(BUILD_MONOLITHIC)
#define main chaos_truely_random_main
#endif

int main(void) {
	for (size_t i = 0; i < 30; i += 3)
		printf("0x%016zx\t0x%016zx\t0x%016zx\n", gen(), gen(), gen());
	return 0;
}
