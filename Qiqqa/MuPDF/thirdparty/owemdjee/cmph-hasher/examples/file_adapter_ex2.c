#include <cmph.h>
#include <stdio.h>
#include <string.h>

#include "monolithic_examples.h"

// Create minimal perfect hash function from in-disk keys using BDZ algorithm


#if defined(BUILD_MONOLITHIC)
#define main		cmph_file_adapter_ex2_main
#endif

int main(int argc, const char **argv)
{   
	if (argc < 2)
	{ 
		fprintf(stderr, "file_adapter_ex2 <file:keys.txt> <key:jjjjjjjjjj>...\n");
		return EXIT_FAILURE;
	}
	// Open file with newline separated list of keys
	const char* path = "keys.txt";
	if (argc >= 2)
		path = argv[1];
	FILE * keys_fd = fopen(path, "r");
	cmph_t *hash = NULL;
	if (keys_fd == NULL) 
	{
	  fprintf(stderr, "File \"%s\" not found\n", path);
		return EXIT_FAILURE;
	}	
	// Source of keys
	cmph_io_adapter_t *source = cmph_io_nlfile_adapter(keys_fd);

	cmph_config_t *config = cmph_config_new(source);
	cmph_config_set_algo(config, CMPH_BDZ);
	hash = cmph_new(config);
	cmph_config_destroy(config);

	do {
		// Find key
		const char* key = "jjjjjjjjjj";
		if (argc >= 3)
			key = argv[2];
		unsigned int id = cmph_search(hash, key, (cmph_uint32)strlen(key));
		fprintf(stderr, "Key: %s --> Id:%u\n", key, id);
		argc--;
		argv++;
	} while (argc >= 3);

	// Destroy hash
	cmph_destroy(hash);
	cmph_io_nlfile_adapter_destroy(source);   
	fclose(keys_fd);
	return EXIT_SUCCESS;
}
