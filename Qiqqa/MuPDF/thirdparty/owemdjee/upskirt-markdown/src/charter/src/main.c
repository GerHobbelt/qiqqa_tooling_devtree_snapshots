#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "renderer.h"

extern int charter_svg_main(int argc, const char* argv[]);
extern int charter_tex_main(int argc, const char* argv[]);
extern int tiny_expr_repl_main(int argc, const char* argv[]);

typedef int main_f(int argc, const char* argv[]);

struct dispatch_table_rec
{
	const char* command;
	main_f* func;
};

static const struct dispatch_table_rec dispatch_table[] =
{
	{ "svg", charter_svg_main },
	{ "tex", charter_tex_main },
	{ "repl", tiny_expr_repl_main },
};

static void print_command_list(void)
{
	int i;
	fprintf(stderr, "\nCommands:\n");
	for (i = 0; i < sizeof(dispatch_table) / sizeof(dispatch_table[0]); i++)
	{
		fprintf(stderr, "  %s\n", dispatch_table[i].command);
	}
}

// MONOLITHIC dispatcher
int main(int argc, const char* argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "usage: charter command file\n");
		print_command_list();
		return EXIT_FAILURE;
    }

	const char* cmd = argv[1];
	int i;
	for (i = 0; i < sizeof(dispatch_table) / sizeof(dispatch_table[0]); i++)
	{
		const struct dispatch_table_rec* rec = &dispatch_table[i];
		if (strcmp(rec->command, cmd) == 0)
		{
			return rec->func(argc - 1, argv + 1);
		}
	}
	fprintf(stderr, "Unknown command '%s'\n", cmd);
	print_command_list();
	return EXIT_FAILURE;
}
