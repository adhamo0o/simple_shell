#include "shell.h"

/**
 **_memset_fun - fills memory
 *@s: ptr to memory area
 *@b: byte to fill *s with
 *@n: amount of bytes to be filled
 *Return: (s) a ptr to the memory area s
 */
char *_memset_fun(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 *ffree_fun - free a string
 *@pp: string of strings
 */
void ffree_fun(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 *_realloc_fun - reallocate block of memory
 *@ptr: ptr
 @old_size: byte size of previous block
 *@new_size: byte size of new block
 *Return: ptr to da ol'block nameen
 */
void *_realloc_fun(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
