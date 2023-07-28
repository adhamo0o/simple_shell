#include "shell.h"

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
 * setenv_fun - Set a new environment variable
 * @args: The arguments passed to the setenv
 *
 * Return: Always returns 1
 */
int setenv_fun(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		fprintf(stderr, "setenv VARIABLE VALUE\n");
		return (1);
	}

	if (setenv(args[1], args[2], 1) == -1)
	{
		perror("setenv failure");
		return (1);
	}

	return (1);
}

/**
 * unsetenv_ - Unset an environment variable.
 * @args: The arguments passed to the unsetenv
 *
 * Return: Always returns 1
 */
int unsetenv_(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "unsetenv VARIABLE\n");
		return (1);
	}

	if (unsetenv(args[1]) == -1)
	{
		perror("unsetenv failure");
		return (1);
	}

	return (1);
}
