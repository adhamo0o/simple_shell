#include "shell.h"

/**
 * strlen_fun - return length of string
 * @s: string
 *
 * Return: length of string
 */
int strlen_fun(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * strcmp_fun - perform lexicogarphic comparison of two strangs
 * @s1: firststr
 * @s2: second str
 *
 * Return: -1 or 1
 */
int strcmp_fun(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - check if needle starts with haystack
 * @haystack: string
 * @needle: substring to find
 *
 * Return: address of next char
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * strcat_fun - concatenate two strings
 * @dest: destination buffer
 * @src: source buffer
 *
 * Return: ptr
 */
char *strcat_fun(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
