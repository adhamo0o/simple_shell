#include "shell.h"

/**
 * read_line - read line from the shell
 *
 * Return: pointer to the line.
*/
char *read_line(void)
{
	char *line;
	int len = 0, Buffer = BUFSIZE;
	char c;

	line = malloc(Buffer);
	if (!line)
	{
		fprintf(stderr, "Allocation error\n");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		c = getchar();
		if (c == '\n' || c == EOF)
		{
			line[len] = '\0';
			return (line);
		}
		else
		{
			line[len++] = c;
		}
		if (len >= Buffer)
		{
			Buffer += BUFSIZE;
			line = realloc(line, Buffer);
			if (!line)
			{
				fprintf(stderr, "Allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}

/**
 * cut_line - cut line into strings
 *
 * @line: to cut
 *
 * Return: array of strings.
*/
char **cut_line(char *line)
{
	char **tokens;
	char *token;
	int Buffer = BUFSIZE, i = 0;

	if (!line)
		return (NULL);
	token = strtok(line, delimmeter);
	tokens = malloc(Buffer * sizeof(char *));
	if (!tokens)
	{
		fprintf(stderr, "Allocation error\n");
		exit(EXIT_FAILURE);
	}
	while (token)
	{
		tokens[i++] = token;
		if (i == Buffer)
		{
			Buffer += BUFSIZE;
			tokens = realloc(tokens, Buffer * sizeof(char *));
			if (!tokens)
			{
				free(tokens);
				fprintf(stderr, "Allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, " ");
	}
	tokens[i] = NULL;
	return (tokens);
}

/**
 * get_path - Get an array of dir
 *
 * Return: An array of dir
 */

char **get_path()
{
	char *path, *token, **dir;
	int bufsize = BUFSIZE, i = 0;

	path = getenv("PATH");
	dir = malloc(bufsize * sizeof(char *));
	if (!dir)
	{
		fprintf(stderr, "Allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(path, ":");
	while (token != NULL)
	{
		dir[i] = token;
		i++;

		if (i >= bufsize)
		{
			bufsize += BUFSIZE;
			dir = realloc(dir, bufsize * sizeof(char *));
			if (!dir)
			{
				fprintf(stderr, "Allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, ":");
	}

	dir[i] = NULL;
	return (dir);
}

/**
 * lanch - Launch a process and execute a command
 * @args: The arguments of the command
 *
 * Return: Always returns 1
 */
int lanch(char **args)
{
	char *envp[] = {NULL}, **dir;
	pid_t pid;
	int status, i = 0;

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, envp) == -1)
		{
			dir = get_path();
			while (dir[i] != NULL)
			{
				excution(dir[i], args);
				i++;
			}
			free(dir);
			exit(127);
		}
	}
	else if (pid < 0)
		perror("hsh");
	else
	{
		waitpid(pid, &status, WUNTRACED);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
			return (127);
		}
	}
	return (1);
}
/**
 * excution - execute the command
 * @dir: ....
 * @args: .....
 *
 * Return: Nothing
 */
void excution(char *dir, char **args)
{
	char *path;

	path = malloc(strlen(dir) + strlen(args[0]) + 2);
	if (!path)
	{
		fprintf(stderr, "Allocation error\n");
		exit(EXIT_FAILURE);
	}
	sprintf(path, "%s/%s", dir, args[0]);
	if (execve(path, args, environ) == 0)
	{
		free(path);
		exit(EXIT_SUCCESS);
	}
}
