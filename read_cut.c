#include "shell.h"
#define BUFSIZE 128
/**
 * read_line - read line from the shell
 * @str: string
 *
 * Return: pointer to the line.
*/
char *read_line(char *str)
{
	char *line;
	int len = 0, Buffer = BUFSIZE;
	char c;

	line = malloc(Buffer);
	if (!line)
	{
		perror(str);
		return (NULL);
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
				free(line);
				perror(str);
				return (NULL);
			}
		}
	}
}

/**
 * cut_line - cut line into strings
 *
 * @line: to cut
 * @str: string
 *
 * Return: array of strings.
*/
char **cut_line(char *line, char *str)
{
	char **tokens;
	char *token;
	int Buffer = BUFSIZE, i = 0;

	if (!line)
		return (NULL);
	token = strtok(line, " ");
	tokens = malloc(Buffer * sizeof(char *));
	if (!tokens)
	{
		perror(str);
		return (NULL);
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
				perror(str);
				return (NULL);
			}
		}
		token = strtok(NULL, " ");
	}
	tokens[i] = NULL;
	return (tokens);
}
