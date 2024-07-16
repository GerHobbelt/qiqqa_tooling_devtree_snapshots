#include <chaos.h> // library header
#include <chaos/monolithic_examples.h>

#include <iostream>

// initialize chaos machine (64-bit version)
CHAOS_MACHINE_XORRING64 longmachine;

#if defined(BUILD_MONOLITHIC)
#define main chaos_long_period_urandom_main
#endif

int main(void) {
	longmachine.set_space(100000);    // 2^6400000 period length
	longmachine << 0x8a5cd789635d2dffULL; // initialize with seed
	while (true) {
		uint32_t rv = longmachine.pull();
		printf("%08x", rv);
	}
	return 0;
}
