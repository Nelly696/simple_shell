#include "shell.h"

/**
 * **custom_strtow - custom string splitting function,
 * ignores repeat delimiters
 * @input_str: the input string
 * @delimiter_str: the delimiter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **custom_strtow(char *input_str, char *delimiter_str)
{
	int i, j, k, m, num_words = 0;
	char **result_array;

	if (input_str == NULL || input_str[0] == 0)
		return (NULL);
	if (!delimiter_str)
		delimiter_str = " ";
	for (i = 0; input_str[i] != '\0'; i++)
		if (!is_custom_delim(input_str[i], delimiter_str) &&
		    (is_custom_delim(input_str[i + 1], delimiter_str) || !input_str[i + 1]))
			num_words++;
	if (num_words == 0)
		return (NULL);
	result_array = malloc((1 + num_words) * sizeof(char *));
	if (!result_array)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (is_custom_delim(input_str[i], delimiter_str))
			i++;
		k = 0;
		while (!is_custom_delim(input_str[i + k], delimiter_str) && input_str[i + k])
			k++;
		result_array[j] = malloc((k + 1) * sizeof(char));
		if (!result_array[j])
		{
			for (k = 0; k < j; k++)
				free(result_array[k]);
			free(result_array);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			result_array[j][m] = input_str[i++];
		result_array[j][m] = 0;
	}
	result_array[j] = NULL;
	return (result_array);
}

/**
 * **custom_strtow2 - custom string splitting function
 * @input_str: the input string
 * @d: the delimiter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **custom_strtow2(char *input_str, char d)
{
	int i, j, k, m, num_words = 0;
	char **result_array;

	if (input_str == NULL || input_str[0] == 0)
		return (NULL);
	for (i = 0; input_str[i] != '\0'; i++)
		if ((input_str[i] != d && input_str[i + 1] == d) ||
		    (input_str[i] != d && !input_str[i + 1]) || input_str[i + 1] == d)
			num_words++;
	if (num_words == 0)
		return (NULL);
	result_array = malloc((1 + num_words) * sizeof(char *));
	if (!result_array)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (input_str[i] == d && input_str[i] != d)
			i++;
		k = 0;
		while (input_str[i + k] != d && input_str[i + k] && input_str[i + k] != d)
			k++;
		result_array[j] = malloc((k + 1) * sizeof(char));
		if (!result_array[j])
		{
			for (k = 0; k < j; k++)
				free(result_array[k]);
			free(result_array);
			return (NULL);
		}

		for (m = 0; m < k; m++)
			result_array[j][m] = input_str[i++];
		result_array[j][m] = 0;
	}

	result_array[j] = NULL;
	return (result_array);
}

