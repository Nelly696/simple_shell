#include "shell.h"

/**
 * initialize_info - initializes the info_t struct
 * @info: struct address
 */
void initialize_info(info_t *info)
{
	info->arguments = NULL;
	info->argument_vector = NULL;
	info->executable_path = NULL;
	info->argument_count = 0;
}

/**
 * populate_info - populates the info_t struct
 * @info: struct address
 * @av: argument vector
 */
void populate_info(info_t *info, char **av)
{
	int i = 0;

	info->program_name = av[0];
	if (info->arguments)
	{
		info->argument_vector = split_string_into_tokens(info->arguments, " \t");
		if (!info->argument_vector)
		{
			info->argument_vector = malloc(sizeof(char *) * 2);
			if (info->argument_vector)
			{
				info->argument_vector[0] = duplicate_string(info->arguments);
				info->argument_vector[1] = NULL;
			}
		}
		for (i = 0; info->argument_vector && info->argument_vector[i]; i++)
			;
		info->argument_count = i;

		replace_aliases(info);
		replace_variables(info);
	}
}

/**
 * deallocate_info - deallocates fields of the info_t struct
 * @info: struct address
 * @all: true if deallocating all fields
 */
void deallocate_info(info_t *info, int all)
{
	ffree(info->argument_vector);
	info->argument_vector = NULL;
	info->executable_path = NULL;
	if (all)
	{
		if (!info->command_buffer)
			free(info->arguments);
		if (info->environment)
			free_list(&(info->environment));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environment_strings);
		info->environment_strings = NULL;
		bfree((void **)info->command_buffer);
		if (info->read_file_descriptor > 2)
			close(info->read_file_descriptor);
		_putchar(BUF_FLUSH);
	}
}

