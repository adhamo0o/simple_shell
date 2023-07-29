#include "shell.h"

/**
 * main - main function of the shell
 *
 * @argc: ...
 * @argv: ...
 *
 * Return: 0.
 */
int main(int argc, char **argv)
{
	char *line = NULL, **args;
	int status = 0;

	(void)argc;
	(void)argv;

	if (isatty(STDIN_FILENO))
		loop();
	else
	{
		line = read_line();
		args = cut_line(line);
		status = execute_(args);

		free(args);
		free(line);
		if (status == 0)
			return (EXIT_SUCCESS);
	}

	if (status == 127)
		return (127);
	else
		return (EXIT_SUCCESS);
}

/**
 * loop - Run the shell program in interactive mode
 */
void loop(void)
{
	char *line, **args;
	int status;

	do {
		printf("($) ");
		line = read_line();
		args = cut_line(line);
		status = execute_(args);

		free(line);
		free(args);
	} while (status);
}
