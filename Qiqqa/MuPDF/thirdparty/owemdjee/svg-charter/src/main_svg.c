#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "parser.h"
#include "renderer.h"

#ifdef BUILD_MONOLITHIC
#include "monolithic_examples.h"
#endif


static off_t fsize(const char *filename) {
    struct stat st; 

    if (stat(filename, &st) == 0)
        return st.st_size;

    return -1; 
}

#ifdef BUILD_MONOLITHIC
#define main(c, a)		charter_svg_main(c, a)
#endif

int main(int argc, const char** argv)
{   
    if (argc < 2)
    {
        fprintf(stderr, "usage: charter file\n");
        return EXIT_FAILURE;
    }
    FILE *fp;
    fp = fopen(argv[1], "r");
	if (!fp)
	{
		fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
		return EXIT_FAILURE;
	}
	long size = fsize(argv[1]);
	char * fcontent = malloc(size + 1);
    fread(fcontent, 1, size, fp);
	fcontent[size] = 0;
    fclose(fp);
    
    chart * c = parse_chart(fcontent);
    char * svg = chart_to_svg(c);
    printf("%s\n", svg);
    chart_free(c);
    free(svg);
    free(fcontent);

    return EXIT_SUCCESS;
}
