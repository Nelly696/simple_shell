#include "shell.h"

/**
 * myShellHistory - prints the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: to maintain constant function prototype.
 *  Return: Always 0
 */
int myShellHistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unsetAlias - Deletes the alias specified by str from the alias list
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unsetAlias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * setAlias - Adds the alias specified by str to the alias list
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int setAlias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unsetAlias(info, str));

	unsetAlias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * printAlias - Prints the alias specified by node
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int printAlias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * myAlias - mimics the alias builtin (man alias)
 * @info:to maintain constant function prototype.
 *  Return: Always 0
 */
int myAlias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			setAlias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
