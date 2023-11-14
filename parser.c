#include "shell.h"

/**
 * is_executable_cmd - determines if a file is an executable command
 * @shell_info: the shell information struct
 * @file_path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_executable_cmd(info_t *shell_info, char *file_path)
{
	struct stat file_stat;

	(void)shell_info;
	if (!file_path || stat(file_path, &file_stat))
		return (0);

	if (file_stat.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_chars - duplicates characters in a given range
 * @path_string: the PATH string
 * @start_index: starting index
 * @stop_index: stopping index
 *
 * Return: pointer to the new buffer
 */
char *duplicate_chars(char *path_string, int start_index, int stop_index)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start_index; i < stop_index; i++)
		if (path_string[i] != ':')
			buffer[k++] = path_string[i];
	buffer[k] = 0;
	return (buffer);
}

/**
 * find_cmd_in_path - finds the command in the PATH string
 * @shell_info: the shell information struct
 * @path_string: the PATH string
 * @command: the command to find
 *
 * Return: full path of the command if found, or NULL
 */
char *find_cmd_in_path(info_t *shell_info, char *path_string, char *command)
{
	int i = 0, current_pos = 0;
	char *full_path;

	if (!path_string)
		return (NULL);

	if ((_strlen(command) > 2) && starts_with(command, "./"))
	{
		if (is_executable_cmd(shell_info, command))
			return (command);
	}

	while (1)
	{
		if (!path_string[i] || path_string[i] == ':')
		{
			full_path = duplicate_chars(path_string, current_pos, i);
			if (!*full_path)
				_strcat(full_path, command);
			else
			{
				_strcat(full_path, "/");
				_strcat(full_path, command);
			}
			if (is_executable_cmd(shell_info, full_path))
				return (full_path);

			if (!path_string[i])
				break;

			current_pos = i;
		}
		i++;
	}
	return (NULL);
}

