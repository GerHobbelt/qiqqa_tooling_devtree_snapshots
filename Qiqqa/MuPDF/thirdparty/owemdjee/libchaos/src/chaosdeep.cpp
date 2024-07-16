#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <chaos.h>
#include <chaos/monolithic_examples.h>

using namespace std;

CHAOS_MACHINE_NCG mc;

static void checksum(std::ifstream &file) {
	CHAOS_MACHINE_NCG::size_push word;
	mc.reset();
	while (file.read(reinterpret_cast<char *>(&word), sizeof(word)))
		mc.push(word);
	mc.push(word);
}

#if defined(BUILD_MONOLITHIC)
#define main chaos_deep_main
#endif

int main(int argc, const char **argv) {
	mc.set_space(2);
	mc.set_time(1);

	ifstream file(argv[1]);
	checksum(file); // FIXME: just for testing...

	for (size_t i = 0; i < 32; i++)
		printf("0x%016zx\t0x%016zx\t0x%016zx\t0x%016zx\n", (uint64_t)mc.pull(), (uint64_t)mc.pull(), (uint64_t)mc.pull(), (uint64_t)mc.pull());

	return 0;
}
