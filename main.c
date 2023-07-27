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
	size_t bufsize = 0;
	int status = 0;

	(void)argc;
	(void)argv;

	if (isatty(STDIN_FILENO))
		loop();
	else
	{
		while (getline(&line, &bufsize, stdin) != -1)
		{
			line[strcspn(line, "\n")] = '\0';
			args = cut_line(line);
			status = execute(args);

			free(args);
			if (status == 0)
				break;
		}

		free(line);
	}

	if (status == 127)
		return (status);
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
		status = execute(args);

		free(line);
		free(args);
	} while (status);
}
