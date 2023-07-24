#include "shell.h"

/**
 * execute_line - execute the files
 *
 * @args: to execute
 *
 * Return: 1 if succes, 0 if not.
*/

int execute_line(char **args)
{
	int i, status;
	pid_t pid;
	char *sys[] = {"exit", "cd"};

	for (i = 0; i < 2; i++)
	{
		if (strcmp(args[0], sys[i]) == 0)
		{
			return (0);
		}
	}

	pid = fork();

	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
			perror("something wrong");
	}
	else if (pid < 0)
	{
		perror("something wrong");
	}
	else
	{
		wait(&status);
		return (1);
	}
	return (1);
}
