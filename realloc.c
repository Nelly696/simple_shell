#include "shell.h"

/**
 * custom_memset - fills memory with a constant byte
 * @memory_area: the pointer to the memory area
 * @byte: the byte to fill *memory_area with
 * @size: the amount of bytes to be filled
 * Return: (memory_area) a pointer to the memory area
 */
char *custom_memset(char *memory_area, char byte, unsigned int size)
{
	unsigned int i;

	for (i = 0; i < size; i++)
		memory_area[i] = byte;
	return (memory_area);
}

/**
 * free_string_array - frees a string array
 * @string_array: string array to free
 */
void free_string_array(char **string_array)
{
	char **temp = string_array;

	if (!string_array)
		return;
	while (*string_array)
		free(*string_array++);
	free(temp);
}

/**
 * cus_realloc - reallocates a block of memory
 * @prev_ptr: pointer to previous malloc'ated block
 * @old_size: byte size of the previous block
 * @new_size: byte size of the new block
 *
 * Return: pointer to the old block if reallocation fails
 */
void *cus_realloc(void *prev_ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!prev_ptr)
		return (malloc(new_size));

	if (!new_size)
		return (free(prev_ptr), NULL);

	if (new_size == old_size)
		return (prev_ptr);

	new_ptr = malloc(new_size);

	if (!new_ptr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;

	while (old_size--)
		new_ptr[old_size] = ((char *)prev_ptr)[old_size];

	free(prev_ptr);
	return (new_ptr);
}

