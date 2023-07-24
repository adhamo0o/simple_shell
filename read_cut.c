#include "shell.h"
#define BUFSIZE 128
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
		perror("problem in allocation");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		if((c = getchar()) == '\n' || c == EOF)
		{
			line[len] = '\0';
			return line;
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
				perror("problem in ");
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

	tokens = malloc(Buffer * sizeof(char *));
	if(!tokens)
	{
		perror("problem in allocation");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, " ");
	while (token)
	{
		tokens[i++] = token;
		if (i >= Buffer)
			{
				Buffer += BUFSIZE;
				tokens = realloc(tokens, Buffer * sizeof(char *));
				if (!tokens)
				{
					perror("problem in allocation");
					exit(EXIT_FAILURE);
				}
			}
		token = strtok(NULL, " ");
	}
	tokens[i] = NULL;
	return tokens;
}
