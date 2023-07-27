#include "shell.h"

/**
 * num_builtins - Get the number of built-in commands
 *
 * Return: The number of built-in commands
 */
int num_builtins(void)
{
	char *builtin_str[] = {
	"cd",
	"exit",
	"env"
	};

	return (sizeof(builtin_str) / sizeof(char *));
}

/**
 * cd_fun - Changeworking directory
 * @args: The arguments
 *
 * Return: Always returns 1
 */
int cd_fun(char **args)
{
	char *home;
	char *old;
	char current[PATH_MAX];

	if (args[1] == NULL || strcmp(args[1], "~") == 0)
	{
		home = getenv("HOME");
		if (!home)
		{
			fprintf(stderr, "cd: %s\n", "HOME not set");
			return (1);
		}
		if (chdir(home) == -1)
			perror("cd");
	} else if (strcmp(args[1], "-") == 0)
	{
		old = getenv("OLDPWD");
		if (!old)
		{
			fprintf(stderr, "cd: OLDPWD not set\n");
			return (1);
		}
		if (chdir(old) == -1)
			perror("cd");
	} else
	{
		if (chdir(args[1]) == -1)
		{
			perror("cd");
		}
	}
	if (getcwd(current, PATH_MAX) == NULL)
	{
		perror("getcwd");
	}
	if (setenv("PWD", current, 1) == -1)
	{
		perror("setenv");
	}
	return (1);
}

/**
 * exit_fun - Exit shell program
 * @args: The arguments
 *
 * Return: Always returns 0
 */
int exit_fun(char **args)
{
	(void)args;
	return (0);
}

/**
 * env_fun - Print environment
 * @args: The arguments
 *
 * Return: Always returns 1 to continue the shell loop
 */
int env_fun(char **args)
{
	int i = 0;

	(void)args;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}

	return (1);
}

/**
 * execute - Execute a command by launching a process or
 * running a built-in command
 * @args: The arguments of the command
 *
 * Return: The exit status of the command
 */
int execute(char **args)
{
	int i;
	char *builtin_str[] = {
		"cd",
		"exit",
		"env"
	};
	int (*builtin_func[]) (char **) = {
		&cd_fun,
		&exit_fun,
		&env_fun
	};

	if (args[0] == NULL)
		return (1);

	for (i = 0; i < num_builtins(); i++)
	{
		if (strcmp(args[0], builtin_str[i]) == 0)
			return ((*builtin_func[i])(args));
	}

	return (lanch(args));
}
