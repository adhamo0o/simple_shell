#include "shell.h"
/**
 * myexit_fun - exit the shell
 * @info: Structure containing args.
 *  Return: exit with a given exit status
 */

int myexit_fun(info_t *info)
{
	int exitcheck;

	if (info->argv[1])  /* If there is an exit arg */
	{
		exitcheck = erratoi_fun(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_puts(info->argv[1]);
			_putchar('\n');
			return (1);
		}
		info->err_num = erratoi_fun(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - change current directory
 * @info: Structure containing args.
 *  Return: Always 0
 */

int _mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = getenv_fun(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = getenv_fun(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (strcmp_fun(info->argv[1], "-") == 0)
	{
		if (!getenv_fun(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(getenv_fun(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dir = getenv_fun(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_puts(info->argv[1]), _putchar('\n');
	}
	else
	{
		setenv_fun(info, "OLDPWD", getenv_fun(info, "PWD="));
		setenv_fun(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - help fun.
 * @info: Structure containing args.
 *  Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
