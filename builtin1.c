#include "shell.h"

/**
 * myhistory_fun - display history list.
 * @info: Structure containing args.
 *  Return: Always 0
 */
int myhistory_fun(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - unset alias
 * @info: struct
 * @str: string
 *
 * Return: Always 0.
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = strchr_fun(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - set alias
 * @info: struct
 * @str: string
 *
 * Return: Always 0.
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = strchr_fun(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - print an alias
 * @node: alias node
 *
 * Return: Always 0.
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = strchr_fun(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * myalias_fun - man alias
 * @info: Structure containing arguments.
 *  Return: Always 0
 */

int myalias_fun(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = strchr_fun(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
