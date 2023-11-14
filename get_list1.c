#include "shell.h"

/**
 * get_list_length - determines the length of the linked list
 * @current_node: pointer to the first node
 *
 * Return: size of the list
 */
size_t get_list_length(const list_t *current_node)
{
	size_t count = 0;

	while (current_node)
	{
		current_node = current_node->next;
		count++;
	}
	return (count);
}

/**
 * convert_list_to_strings - returns an array of strings from the list->str
 * @head: pointer to the first node
 *
 * Return: array of strings
 */
char **convert_list_to_strings(list_t *head)
{
	list_t *current_node = head;
	size_t length = get_list_length(head), i;
	char **strings;
	char *str;

	if (!head || !length)
		return (NULL);

	strings = malloc(sizeof(char *) * (length + 1));
	if (!strings)
		return (NULL);

	for (i = 0; current_node; current_node = current_node->next, i++)
	{
		str = malloc(_strlen(current_node->str) + 1);
		if (!str)
		{
			for (size_t j = 0; j < i; j++)
				free(strings[j]);
			free(strings);
			return (NULL);
		}

		str = _strcpy(str, current_node->str);
		strings[i] = str;
	}
	strings[i] = NULL;
	return (strings);
}

/**
 * display_list - prints all elements of a list_t linked list
 * @current_node: pointer to the first node
 *
 * Return: size of the list
 */
size_t display_list(const list_t *current_node)
{
	size_t count = 0;

	while (current_node)
	{
		_puts(convert_number(current_node->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(current_node->str ? current_node->str : "(nil)");
		_puts("\n");
		current_node = current_node->next;
		count++;
	}
	return (count);
}

/**
 * find_node_starts_with - returns a node whose string starts with a prefix
 * @current_node: pointer to the list head
 * @prefix: string to match
 * @c: the next character after the prefix to match
 *
 * Return: matching node or NULL
 */
list_t *find_node_starts_with(list_t *current_node, char *prefix, char c)
{
	char *p = NULL;

	while (current_node)
	{
		p = starts_with(current_node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (current_node);
		current_node = current_node->next;
	}
	return (NULL);
}

/**
 * obtain_node_index - gets the index of a node
 * @head_node: pointer to the list head
 * @target_node: pointer to the node
 *
 * Return: index of the node or -1
 */
ssize_t obtain_node_index(list_t *head_node, list_t *target_node)
{
	size_t index = 0;

	while (head_node)
	{
		if (head_node == target_node)
			return (index);
		head_node = head_node->next;
		index++;
	}
	return (-1);
}

