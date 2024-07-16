#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "monolithic_examples.h"

static int help(const char * prname)
{
	fprintf(stderr, "USE: %s <n><wordsizeinbits>\n", prname);
	return EXIT_FAILURE;
}


#if defined(BUILD_MONOLITHIC)
#define main		cmph_bdz_gen_lookup_table_main
#endif

int main(int argc, const char ** argv)
{
	if(argc != 3)
		return help(argv[0]);
	int n = atoi(argv[1]);
	int wordsize = (atoi(argv[2]) >> 1);
	int i, j, n_assigned;
	for(i = 0; i < n; i++)
	{
		int num = i;
		n_assigned = 0;
		for(j = 0; j < wordsize; j++)
		{			
			if ((num & 0x0003) != 3) 
			{
				n_assigned++;
				//fprintf(stderr, "num:%d\n", num);
			}
			num = num >> 2;
		}
		if(i%16 == 0) fprintf(stderr, "\n");
		fprintf(stderr, "%d, ", n_assigned);	
	} 
	fprintf(stderr, "\n");
	return EXIT_SUCCESS;
}
