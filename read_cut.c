#include "shell.h"
#define BUFSIZE 128
#define delimeter " \t\r\n\a" 
/**
 * read_line - read line from the shell
 *
 * Return: pointer to the line.
*/
char *read_line(void)
{
	char *line = NULL;
	size_t Buffer = 0
	char c;

	if (getline(&line, &Buffer, stdin) == -1)
	{
		if (feof(stdin))
			exit(EXIT_SUCCESS);
		else
		{
			perror("failure to read line");
			exit(EXIT_FAILURE);
		}
	}
	return (line);
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
	token = strtok(line, delimeter);
	tokens = malloc(Buffer * sizeof(char *));
	if (!tokens)
	{
		fprintf(stderr, "allocation failure\n");
		exit(EXIT_FAILURE);
	}
	while (token)
	{
		tokens[i++] = token;
		if (i >= Buffer)
		{
			Buffer += BUFSIZE;
			tokens = realloc(tokens, Buffer * sizeof(char *));
			if (!tokens)
			{
				fprintf(stderr, "alloctaion failure\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, delimeter);
	}
	tokens[i] = NULL;
	return (tokens);
}
