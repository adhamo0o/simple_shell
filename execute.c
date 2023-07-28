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
	"env",
	"setenv",
	"unsetenv"
	};

	return (sizeof(builtin_str) / sizeof(char *));
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
		"env",
		"setenv",
		"unsetenv"
	};
	int (*builtin_func[]) (char **) = {
		&cd_fun,
		&exit_fun,
		&env_fun,
		&setenv_fun,
		&unsetenv
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
