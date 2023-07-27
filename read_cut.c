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

<<<<<<< HEAD
	if (getline(&line, &Buffer, stdin) == -1)
=======
	line = malloc(Buffer);
	if (!line)
	{
		perror(str);
		return (NULL);
	}
	while (1)
>>>>>>> d08c21c657a8adb3975cd7c59cefa53e67d358a9
	{
		if (feof(stdin))
			exit(EXIT_SUCCESS);
		else
		{
<<<<<<< HEAD
			perror("failure to read line");
			exit(EXIT_FAILURE);
=======
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
>>>>>>> d08c21c657a8adb3975cd7c59cefa53e67d358a9
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
<<<<<<< HEAD
		fprintf(stderr, "allocation failure\n");
		exit(EXIT_FAILURE);
=======
		perror(str);
		return (NULL);
>>>>>>> d08c21c657a8adb3975cd7c59cefa53e67d358a9
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
<<<<<<< HEAD
				fprintf(stderr, "alloctaion failure\n");
				exit(EXIT_FAILURE);
=======
				free(tokens);
				perror(str);
				return (NULL);
>>>>>>> d08c21c657a8adb3975cd7c59cefa53e67d358a9
			}
		}
		token = strtok(NULL, delimeter);
	}
	tokens[i] = NULL;
	return (tokens);
}
