#include "shell.h"
/**
 *puts_fun - print an input string
 * @str: string to be printed
 *
 * Return: Nothing
 */
void puts_fun(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		putchar_fun(str[i]);
		i++;
	}
}

/**
 * putchar_fun - write char c to stderr
 * @c: character
 *
 * Return: On success 1
 */
int putchar_fun(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * putfd_fun - write character c
 * @c: character to print
 * @fd: filedescriptor to write to
 *
 * Return: On success 1
 */
int putfd_fun(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *putsfd_fun - print an input string
 * @str: string to be printed
 * @fd: filedescriptor to write to
 *
 * Return: number of chars put
 */
int putsfd_fun(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
