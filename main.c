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
	size_t bufsize = 0;
	FILE *f;

	(void)argc;
	(void)argv;

	if (isatty(STDIN_FILENO))
		loop();
	else
	{
		f = stdin;
		while(getline(&line, &bufsize, f) != -1)
		{
		line[strcspn(line, "\n")] = '\0';
		args = cut_line(line);
		status = execute_(args);

		free(args);
		if (status == 0)
			break;
		}
		free(line);
	}
	return (status);
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
