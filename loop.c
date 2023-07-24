#include "shell.h"

/**
 * shell_loop - main loop of the shell
 *
 * Return: Nothing.
*/

void shell_loop(void)
{
	char *line;
	char **words;
	int status;

	do {
		printf("($) ");
		line = read_line();
		words = cut_line(line);
		status = execute_line(words);

		free(line);
		free(words);
	} while (status);
}
