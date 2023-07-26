#include "shell.h"

/**
 * shell_loop - main loop of the shell
 *
 * @str: string.
 *
 * Return: Nothing.
*/

void shell_loop(char *str)
{
	char *line;
	char **words;
	int status;
	int n = 1, i;

	do {
		i = isatty(STDIN_FILENO);
		if (i)
			printf("($) ");
		line = read_line(str);
		words = cut_line(line, str);
		status = execute_line(words, str, n);
		if (status == 2)
			n++;
		else if (status == 0)
			exit(EXIT_SUCCESS);

		free(line);
		free(words);
	} while (status);
}
