#include "shell.h"

/**
 * main - main function of the shell
 *
 * Return: 0.
 */
int main(int __attribute__((unused)) argc, char *argv[])
{
	shell_loop(argv[0]);
	return (0);
}
