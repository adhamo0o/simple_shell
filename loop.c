#include "shell.h"
/**
 * hsh_fun - main shell loop
 * @info: parameter
 * @av: arg vector
 *
 * Return: 0 on success
 */
int hsh_fun(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive_fun(info))
			_puts_fun("$ ");
		_eputchar_fun(BUF_FLUSH);
		r = get_input_fun(info);
		if (r != -1)
		{
			set_info_fun(info, av);
			builtin_ret_fun = find_builtin_fun(info);
			if (builtin_ret_fun == -1)
				find_cmd_fun(info);
		}
		else if (interactive_fun(info))
			_putchar_fun('\n');
		free_info_fun(info, 0);
	}
	write_history_fun(info);
	free_info_fun(info, 1);
	if (!interactive_fun(info) && info->status)
		exit(info->status);
	if (builtin_ret_fun == -2)
	{
		if (info->err_num_fun == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_re_funt);
}

/**
 * find_builtin_fun - find a builtin cmd
 * @info: parameter
 *
 * Return: -1 if builtin not found,
 */
int find_builtin_fun(info_t *info)
{
	int i, built_in_ret_fun = -1;
	builtin_table_fun builtintbl_fun[] = {
		{"exit", _myexit_fun},
		{"env", _myenv_fun},
		{"help", _myhelp_fun},
		{"history", _myhistory_fun},
		{"setenv", _mysetenv_fun},
		{"unsetenv", _myunsetenv_fun},
		{"cd", _mycd_fun},
		{"alias", _myalias_fun},
		{NULL, NULL}
	};

	for (i = 0; builtintbl_fun[i].type; i++)
		if (_strcmp_fun(info->argv[0], builtintbl_fun[i].type) == 0)
		{
			info->line_count_fun++;
			built_in_ret_fun = builtintbl_fun[i].func(info);
			break;
		}
	return (built_in_ret_fun);
}

/**
 * find_cmd_fun - find a cmd
 * @info: parameter
 *
 * Return: void
 */
void find_cmd_fun(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag_fun == 1)
	{
		info->line_count_fun++;
		info->linecount_flag_fun = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim_fun(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path_fun(info, _getenv_fun(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd_fun(info);
	}
	else
	{
		if ((interactive_fun(info) || _getenv_fun(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd_fun(info, info->argv[0]))
			fork_cmd_fun(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error_fun(info, "not found\n");
		}
	}
}

/**
 * fork_cmd_fun - fork cmd
 * @info: parameter
 *
 * Return: void
 */
void fork_cmd_fun(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ_fun(info)) == -1)
		{
			free_info_fun(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
