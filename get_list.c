#include "shell.h"

/**
 * add_new_node - adds a node to the beginning of the list
 * @list_head: pointer to the head of the list
 * @data: string data for the new node
 * @index: index of the new node
 *
 * Return: address of the new head node
 */
list_t *add_new_node(list_t **list_head, const char *data, int index)
{
	list_t *new_head;

	if (!list_head)
		return (NULL);

	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);

	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->index = index;

	if (data)
	{
		new_head->str_data = _strdup(data);
		if (!new_head->str_data)
		{
			free(new_head);
			return (NULL);
		}
	}

	new_head->next = *list_head;
	*list_head = new_head;

	return (new_head);
}

/**
 * add_node_to_end - adds a node to the end of the list
 * @list_head: pointer to the head of the list
 * @data: string data for the new node
 * @index: index of the new node
 *
 * Return: address of the new node
 */
list_t *add_node_to_end(list_t **list_head, const char *data, int index)
{
	list_t *new_node, *node;

	if (!list_head)
		return (NULL);

	node = *list_head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->index = index;

	if (data)
	{
		new_node->str_data = _strdup(data);
		if (!new_node->str_data)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (node)
	{
		while (node->next)
			node = node->next;

		node->next = new_node;
	}
	else
		*list_head = new_node;

	return (new_node);
}

/**
 * print_str_list - prints only the str_data element of a list_t linked list
 * @head_node: pointer to the first node
 *
 * Return: size of the list
 */
size_t print_str_list(const list_t *head_node)
{
	size_t size = 0;

	while (head_node)
	{
		_puts(head_node->str_data ? head_node->str_data : "(nil)");
		_puts("\n");
		head_node = head_node->next;
		size++;
	}
	return (size);
}

/**
 * delete_node_at_pos - deletes a node at the given position
 * @list_head: pointer to the head of the list
 * @position: position of the node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_pos(list_t **list_head, unsigned int position)
{
	list_t *node, *prev_node;
	unsigned int count = 0;

	if (!list_head || !*list_head)
		return (0);

	if (!position)
	{
		node = *list_head;
		*list_head = (*list_head)->next;
		free(node->str_data);
		free(node);
		return (1);
	}

	node = *list_head;
	while (node)
	{
		if (count == position)
		{
			prev_node->next = node->next;
			free(node->str_data);
			free(node);
			return (1);
		}

		count++;
		prev_node = node;
		node = node->next;
	}

	return (0);
}

/**
 * free_string_list - frees all nodes of a list
 * @head_pointer: pointer to the head node
 *
 * Return: void
 */
void free_string_list(list_t **head_pointer)
{
	list_t *node, *next_node, *head;

	if (!head_pointer || !*head_pointer)
		return;

	head = *head_pointer;
	node = head;

	while (node)
	{
		next_node = node->next;
		free(node->str_data);
		free(node);
		node = next_node;
	}

	*head_pointer = NULL;
}

