#include "shell.h"

/**
 * shell_loop - main loop of the shell
 *
 * Return: Nothing.
*/

void shell_loop(char *str)
{
	char *line;
	char **words;
	int status;
	int n = 1;

	do {
		printf("($) ");
		line = read_line(str);
		words = cut_line(line, str);
		status = execute_line(words, str, n);
		if (status == 2)
			n++;

		free(line);
		free(words);
	} while (status);
}
