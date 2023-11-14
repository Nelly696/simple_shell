#include "shell.h"

/**
 * custom_strcpy - custom implementation to copy a string
 * @destination: the destination
 * @source: the source
 *
 * Return: pointer to destination
 */
char *custom_strcpy(char *destination, char *source)
{
	int index = 0;

	if (destination == source || source == NULL)
		return (destination);

	while (source[index])
	{
		destination[index] = source[index];
		index++;
	}

	destination[index] = '\0';
	return (destination);
}

/**
 * custom_strdup - custom implementation to duplicate a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *custom_strdup(const char *str)
{
	int length = 0;
	char *result;

	if (str == NULL)
		return (NULL);

	while (*str++)
		length++;

	result = malloc(sizeof(char) * (length + 1));

	if (!result)
		return (NULL);

	for (length++; length--;)
		result[length] = *--str;

	return (result);
}

/**
 * custom_puts - custom implementation to print an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void custom_puts(char *str)
{
	int index = 0;

	if (!str)
		return;

	while (str[index] != '\0')
	{
		_putchar(str[index]);
		index++;
	}
}

/**
 * custom_putchar - custom implementation to write the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int custom_putchar(char c)
{
	static int buffer_index;
	static char custom_buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || buffer_index >= WRITE_BUF_SIZE)
	{
		write(1, custom_buffer, buffer_index);
		buffer_index = 0;
	}

	if (c != BUF_FLUSH)
		custom_buffer[buffer_index++] = c;

	return (1);
}

