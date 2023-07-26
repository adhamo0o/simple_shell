#include "shell.h"

/**
 * main - main function of the shell
 *
 * @argc: ...
 * @argv: ...
 *
 * Return: 0.
 */
int main(int __attribute__((unused)) argc, char *argv[])
{
	char *line;
	char **words;
	int status;
	int n = 1, i;

	do {
		i = isatty(STDIN_FILENO);
		if (i)
			printf("($) ");
		line = read_line(argv[0]);
		words = cut_line(line, argv[0]);
		status = execute_line(words, argv[0], n);
		if (status == 2)
			n++;

		free(line);
		free(words);
	} while (status);
	return (0);
}
