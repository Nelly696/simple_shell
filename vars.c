#include "shell.h"

/**
 * is_command_chain - checks if the current character
 * in the buffer is a chain delimiter
 * @info: the parameter struct
 * @buffer: the char buffer
 * @position: address of the current position in the buffer
 *
 * Return: 1 if it is a chain delimiter, 0 otherwise
 */
int is_command_chain(info_t *info, char *buffer, size_t *position)
{
	size_t j = *position;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buffer[j] == ';') /* found end of this command */
	{
		buffer[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*position = j;
	return (1);
}

/**
 * check_cmd_chain - checks if we should continue
 * chaining based on the last status
 * @info: the parameter struct
 * @b: the char buffer
 * @p: address of the current position in the buffer
 * @s: starting position in the buffer
 * @l: length of the buffer
 *
 * Return: Void
 */
void check_cmd_chain(info_t *info, char *b, size_t *p, size_t s, size_t l)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			b[start] = 0;
			j = l;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			b[start] = 0;
			j = l;
		}
	}

	*p = j;
}

/**
 * substitute_aliases - substitutes aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int substitute_aliases(info_t *info)
{
	int i;
	list_t *alias_node;
	char *value;

	for (i = 0; i < 10; i++)
	{
		alias_node = node_starts_with(info->alias, info->argv[0], '=');
		if (!alias_node)
			return (0);
		free(info->argv[0]);
		value = _strchr(alias_node->str, '=');
		if (!value)
			return (0);
		value = _strdup(value + 1);
		if (!value)
			return (0);
		info->argv[0] = value;
	}
	return (1);
}

/**
 * substitute_variables - substitutes variables in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int substitute_variables(info_t *info)
{
	int i = 0;
	list_t *env_node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		env_node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (env_node)
		{
			replace_string(&(info->argv[i]),
					_strdup(_strchr(env_node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string_content - replaces the content of a string
 * @old_content: address of the old content
 * @new_content: new content
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string_content(char **old_content, char *new_content)
{
	free(*old_content);
	*old_content = new_content;
	return (1);
}

