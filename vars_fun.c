#include "shell.h"
/**
 * is_chain_fun - test if current char in buffer is a chain
 * @info: parameter 
 * @buf: char buffer
 * @p: address of current position in buf
 *
 * Return: 1
 */
int is_chain_fun(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain_fun - checks we continue chaining based on last status
 * @info: parameter
 * @buf: char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain_fun(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias_fun - replace aliases in string
 * @info: the parameter
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias_fun(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with_fun(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr_fun(node->str, '=');
		if (!p)
			return (0);
		p = _strdup_fun(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars_fun - replace vars in string
 * @info: parameter
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars_fun(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp_fun(info->argv[i], "$?"))
		{
			replace_string_fun(&(info->argv[i]),
					_strdup_fun(convert_number_fun(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp_fun(info->argv[i], "$$"))
		{
			replace_string_fun(&(info->argv[i]),
					_strdup_fun(convert_number_fun(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with_fun(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string_fun(&(info->argv[i]),
					_strdup_fun(_strchr_fun(node->str, '=') + 1));
			continue;
		}
		replace_string_fun(&info->argv[i], _strdup_fun(""));

	}
	return (0);
}

/**
 * replace_string_fun - replace string
 * @old: old string
 * @new: new string
 *
 * Return: 1 if replaced
 */
int replace_string_fun(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
