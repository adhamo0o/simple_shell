#include "shell.h"
/**
 * hshell - main shell loop
 * @info: parameter
 * @av: arg vector
 *
 * Return: 0 on success
 */
int hshell(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive_fun(info))
			_puts("$ ");
		_putchar(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive_fun(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive_fun(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - find a builtin cmd
 * @info: parameter
 *
 * Return: -1 if builtin not found,
 */
int find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl_fun[] = {
		{"exit", myexit_fun},
		{"env", myenv_fun},
		{"help", myhelp_fun},
		{"history", myhistory_fun},
		{"setenv", mysetenv_fun},
		{"unsetenv", myunsetenv_fun},
		{"cd", mycd_fun},
		{"alias", myalias_fun},
		{NULL, NULL}
	};

	for (i = 0; builtintbl_fun[i].type; i++)
		if (strcmp_fun(info->argv[0], builtintbl_fun[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl_fun[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - find a cmd
 * @info: parameter
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_del(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, getenv_fun(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive_fun(info) || getenv_fun(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - fork cmd
 * @info: parameter
 *
 * Return: void
 */
void fork_cmd(info_t *info)
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
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
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
