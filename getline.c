#include "shell.h"
int lsh_launch(char **args)
{
	pid_t pid, wpid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		char *const envp[] = {NULL};
		if (execve(args[0], args, envp) == -1)
		{
			perror("lsh");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("lsh");
	}
	else
	{
		do
		{
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return 1;
}




/**
 * get_line - function that get the line
 * Return: the read line
 */
char *get_line(void)
{
	char *line = NULL;
	size_t buffer = 0;

	if(getline(&line, &buffer, stdin) = -1)
	{
		if(feof(stdin))
			exit(EXIT_SUCCESS);
		else
		{
			perror("failure to gitline");
			exit(EXIT_FAILURE);
		}
	}
	return (line);
}




/**
 * split_line - function that splits the line
 * @line: the splits line
 * Return: the split line
 */
char **split_line(char *line)
{
	int position = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token;

	if (!tokens)
	{
		fprintf(stderr, "failure\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, delim);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += buf_size;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if (!tokens)
			{
				fprintf(stderr, "allocation failure\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, delim);
	}
	tokens[position] = NULL;
	return tokens;
}
