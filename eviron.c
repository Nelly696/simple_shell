#include "shell.h"

/**
 * myEnvironment - prints the current environment
 * @info: to maintain a constant function prototype.
 * Return: Always 0
 */
int myEnvironment(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * getEnvironmentVariable - gets the value of an environment variable
 * @info: to maintain a constant function prototype.
 * @name: env var name
 * Return: the value
 */
char *getEnvironmentVariable(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * mySetEnvironment - Initializes a new environment variable
 * @info: to maintain a constant function prototype.
 *  Return: Always 0
 */
int mySetEnvironment(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (SetEnvironmentVariable(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * myUnsetEnvironment - Remove an environment variable
 * @info: to maintain a constant function prototype.
 * Return: Always 0
 */
int myUnsetEnvironment(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unSetEnvironment(info, info->argv[i]);

	return (0);
}

/**
 * populateEnvironmentList - populates env linked list
 * @info: to maintain a constant function prototype.
 * Return: Always 0
 */
int populateEnvironmentList(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
