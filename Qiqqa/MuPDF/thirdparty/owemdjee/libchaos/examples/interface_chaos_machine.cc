#include <chaos.h>
#include <chaos/monolithic_examples.h>

CHAOS_MACHINE_XORRING64 machine;

static int test(uint64_t sollwert, uint64_t check) {
	int rv = (check != sollwert);
	if (rv)
		fprintf(stderr, "Test failed (sollwert: 0x%016zx, actual: 0x%016zx)\n",
		        (size_t)sollwert, (size_t)check);
	return rv;
}

static int test_and_check(uint64_t sollwert, uint64_t check = 0) {
	auto c = machine.pull();
	check += c;

	return test(sollwert, check);
}

#if defined(BUILD_MONOLITHIC)
#define main chaos_machine_interface_main
#endif

int main(void) {
	uint64_t a = 0x84242f96eca9c41d, b = 0xa3c65b8776f96855, c, check;

	// PUSH
	machine.push(a);
	machine << b;

	if (test(0x84242f96eca9c41d, a))
		return 1;
	if (test(0xa3c65b8776f96855, b))
		return 1;

	// PULL
	check = machine.pull();
	machine >> c;
	check += c;
	check += machine();

	return test_and_check(0xf25566d9bb9cbb4b, check);
}
