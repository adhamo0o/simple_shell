#include "shell.h"

/**
 * get_executable_path - function that return the path
 * @executable_name: the name
 * Return: the path
 */
char* get_executable_path(const char* executable_name)
{
	char command[256];
	FILE* fp;
	char* path = NULL;

	sprintf(command, "which %s", executable_name);
	fp = popen(command, "r");

	if (fp == NULL)
	{
		perror("popen");
		return (NULL);
	}
	path = (char*)malloc(256 * sizeof(char));
	if (path == NULL)
	{
		perror("malloc");
		pclose(fp);
		return (NULL);
	}
	if (fgets(path, 256, fp) != NULL)
	{
		path[strcspn(path, "\n")] = '\0';
	}
	else
	{
		free(path);
		path = NULL;
	}

	pclose(fp);
	return (path);
}

/**
 * execute_line - function that execute the files
 * @args: to execute
 * Return: 1 on sucess and 0 if not
 */
int execute_line(char **args)
{
	int status, i = 0;
	pid_t pid;
	char *sys[] = {"exit", "cd"};
	char *env[] = {NULL};
	char *executable;

	for(i = 0; i < 2; i+)
	{
		if (strcmp(args[0], sys[i]) == 0)
			return (0);
	}

	if(pid == 0)
	{
		executable = get_executable_path(args[0]);
		if (executable == NULL)
		{
			perror("Executable not found");
			return (1);
		}
		if (execve(executable, args, env) == -1)
			perror("something wrong");
		free(executable);
	}
	else if (pid < 0)
		perror("something error");
	else
	{
		wait(&status);
		return (1);
	}

	return (1);
}
