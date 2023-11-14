#include "shell.h"

/**
 * obtain_history_file - returns the history file path
 * @info: Parameter struct
 * Return: Allocated string containing the history file path
 */
char *obtain_history_file(info_t *info)
{
	char *buf, *home_dir;

	home_dir = _getenv(info, "HOME=");
	if (!home_dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(home_dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, home_dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_shell_history - creates or appends to the shell history file
 * @info: The parameter struct
 * Return: 1 on success, -1 on failure
 */
int write_shell_history(info_t *info)
{
	ssize_t fd;
	char *filename = obtain_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->shell_history; node; node = node->next)
	{
		_puts_to_file_descriptor(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads shell history from a file
 * @info: The parameter struct
 * Return: Number of history entries read on success, 0 on failure
 */
int read_history(info_t *info)
{
	int i, last = 0, history_entry_count = 0;
	ssize_t fd, rdlen, file_size = 0;
	struct stat file_stat;
	char *buf = NULL, *filename = obtain_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &file_stat))
		file_size = file_stat.st_size;
	if (file_size < 2)
		return (0);
	buf = malloc(sizeof(char) * (file_size + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, file_size);
	buf[file_size] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < file_size; i++)
	{
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			append_to_history_list(info, buf + last, history_entry_count++);
			last = i + 1;
		}
	}
	if (last != i)
		append_to_history_list(info, buf + last, history_entry_count++);
	free(buf);
	info->history_count = history_entry_count;
	while (info->history_count-- >= SHELL_HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	reenumerate_history(info);
	return (info->history_count);
}

/**
 * append_to_history_list - appends an entry to the shell history list
 * @info: The parameter struct
 * @buf: The buffer containing the entry
 * @history_entry_count: The history entry count
 * Return: Always 0
 */
int append_to_history_list(info_t *info, char *buf, int history_entry_count)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, history_entry_count);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * reenumerate_history - renumbers the shell history list entries
 * @info: The parameter struct
 * Return: The new shell history count
 */
int reenumerate_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	return (info->history_count = i);
}

