#include "shell.h"

/**
 * myenv_fun - printenv
 * @info: Structure containing args.
 * Return: Always 0
 */
int myenv_fun(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * getenv_fun - get value of an env
 * @info: Structure containing args.
 * @name: env var
 *
 * Return: value
 */
char *getenv_fun(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * mysetenv_fun - Initialize a new env var
 * @info: Structure containing args.
 *  Return: Always 0
 */
int mysetenv_fun(info_t *info)
{
	if (info->argc != 3)
	{
		_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (setenv_fun(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * myunsetenv_fun - Remove env var
 * @info: Structure containing potential args.
 *  Return: Always 0
 */
int myunsetenv_fun(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_puts("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unsetenv_fun(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - populate env linked list
 * @info: Structure containing potential args.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
