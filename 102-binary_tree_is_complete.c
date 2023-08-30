#include "binary_trees.h"
/**
 * new_node - Function that creates a new_node in a linked_list
 * @node: Type pointer of node to be created
 * Return: the node created
 */
link_t *new_node(binary_tree_t *node)
{
	link_t *newnode;

	newnode =  malloc(sizeof(link_t));
	if (newnode == NULL)
	{
		return (NULL);
	}
	newnode->node = node;
	newnode->next = NULL;

	return (newnode);
}
/**
 * free_q - Function that free the nodes at the linked list
 * @head: Node of the linked_list
 */
void free_q(link_t *head)
{
	link_t *temp;

	while (head)
	{
		temp = head->next;
		free(head);
		head = temp;
	}
}
/**
 * _push - Function that pushes a node into the stack
 * @node: Type pointer of node of the tree
 * @head: Type head node of in the stack
 * @tail: Type tail node of in the stack
 */
void _push(binary_tree_t *node, link_t *head, link_t **tail)
{
	link_t *newnode;

	newnode = new_node(node);
	if (newnode == NULL)
	{
		free_q(head);
		exit(1);
	}
	(*tail)->next = newnode;
	*tail = newnode;
}
/**
 * _pop - Function that pops a node into the stack
 * @head: Type head node of in the stack
 */
void _pop(link_t **head)
{
	link_t *temp;

	temp = (*head)->next;
	free(*head);
	*head = temp;
}
/**
 * binary_tree_is_complete - Function that checks if a binary tree is complete
 * @tree: Type pointer of node of the tree
 * Return: 1 if is complete 0 if it is not
 */
int binary_tree_is_complete(const binary_tree_t *tree)
{
	link_t *head, *tail;
	int flag = 0;

	if (tree == NULL)
	{
		return (0);
	}
	head = tail = new_node((binary_tree_t *)tree);
	if (head == NULL)
	{
		exit(1);
	}
	while (head != NULL)
	{
		if (head->node->left != NULL)
		{
			if (flag == 1)
			{
				free_q(head);
				return (0);
			}
			_push(head->node->left, head, &tail);
		}
		else
			flag = 1;
		if (head->node->right != NULL)
		{
			if (flag == 1)
			{
				free_q(head);
				return (0);
			}
			_push(head->node->right, head, &tail);
		}
		else
			flag = 1;
		_pop(&head);
	}
	return (1);
}
