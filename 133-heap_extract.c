#include "binary_trees.h"

/**
 * queue_item_4 - Adds an item to a queue.
 * @queue_h: A pointer to the queue's head.
 * @queue_t: A pointer to the queue's tail.
 * @n: A pointer to the queue's size value.
 * @item: The item to add to the queue.
 */
void queue_item_4(heap_t **queue_h, heap_t **queue_t,
	int *n, void *item)
{
	heap_t *new_node;

	if ((queue_h != NULL) && (queue_t != NULL))
	{
		new_node = malloc(sizeof(heap_t));
		if (new_node == NULL)
			return;
		new_node->left = *queue_t;
		new_node->right = NULL;
		new_node->n = (item != NULL ? ((heap_t *)item)->n : -1);
		new_node->parent = (heap_t *)item;
		if (*queue_h == NULL)
			*queue_h = new_node;
		if (*queue_t != NULL)
			(*queue_t)->right = new_node;
		*queue_t = new_node;
		if (n != NULL)
			(*n)++;
	}
}

/**
 * dequeue_item_4 - Removes an item from a queue.
 * @queue_h: A pointer to the queue's head.
 * @queue_t: A pointer to the queue's tail.
 * @n: A pointer to the queue's size value.
 *
 * Return: The value of the removed queue.
 */
heap_t *dequeue_item_4(heap_t **queue_h,
	heap_t **queue_t, int *n)
{
	heap_t *tmp_node_0;
	heap_t *tmp_node_1;
	heap_t *node = NULL;

	if ((queue_h != NULL) && (queue_t != NULL))
	{
		tmp_node_0 = *queue_h;
		if (tmp_node_0 != NULL)
		{
			node = tmp_node_0->parent;
			if (tmp_node_0->right != NULL)
			{
				tmp_node_1 = tmp_node_0->right;
				tmp_node_1->left = NULL;
				*queue_h = tmp_node_1;
				free(tmp_node_0);
			}
			else
			{
				free(tmp_node_0);
				*queue_h = NULL;
				*queue_t = NULL;
			}
			if (n != NULL)
				(*n)--;
		}
	}
	return (node);
}

/**
 * get_last_node - Gets the last level order node \
 * in a max binary heap tree.
 * @root: The root of the max binary heap tree.
 *
 * Return: A pointer to the last level order node, otherwise NULL.
 */
heap_t *get_last_node(const heap_t *root)
{
	heap_t *head = NULL, *tail = NULL;
	heap_t *last_node = NULL, *current = NULL;
	int n = 0;

	if (root != NULL)
	{
		queue_item_4(&head, &tail, &n, (void *)root);
		while (n > 0)
		{
			current = head;
			if (current->parent != NULL)
			{
				last_node = current->parent;
				if (current->parent->left != NULL)
				{
					queue_item_4(&head, &tail, &n, (void *)(current->parent->left));
				}
				if (current->parent->right != NULL)
				{
					queue_item_4(&head, &tail, &n, (void *)(current->parent->right));
				}
			}
			dequeue_item_4(&head, &tail, &n);
		}
		while (n > 0)
			dequeue_item_4(&head, &tail, &n);
	}
	return (last_node);
}

/**
 * swap_with_parent_1 - Swaps a node in a \
 * max binary heap tree with its parent.
 * @node: A pointer to the node's address.
 * @root: A pointer to the root of the tree.
 */
void swap_with_parent_1(heap_t **node, heap_t **root)
{
	heap_t *node_copy, *p, *tmp0, *l, *r;

	if ((node != NULL) && ((*node)->parent != NULL) && (root != NULL))
	{
		p = (*node)->parent, node_copy = *node, tmp0 = (*node)->parent->parent;
		l = (*node)->left, r = (*node)->right;
		if ((*node)->parent->left != *node) /* swap from the right */
		{
			if ((tmp0 != NULL) && (tmp0->left == (*node)->parent))
				tmp0->left = *node;
			if ((tmp0 != NULL) && (tmp0->right == (*node)->parent))
				tmp0->right = *node;
			if ((*node)->parent->left != NULL)
				(*node)->parent->left->parent = node_copy;
			(*node)->parent = tmp0, (*node)->left = p->left, (*node)->right = p;
			p->parent = node_copy, p->left = l, p->right = r;
		}
		else /* swap from the left */
		{
			if ((tmp0 != NULL) && (tmp0->left == p))
				tmp0->left = *node;
			if ((tmp0 != NULL) && (tmp0->right == p))
				tmp0->right = *node;
			if ((*node)->parent->right != NULL)
				(*node)->parent->right->parent = *node;
			(*node)->parent = tmp0, (*node)->right = p->right, (*node)->left = p;
			p->parent = node_copy, p->left = l, p->right = r;
		}
		if (l != NULL)
			l->parent = p;
		if (r != NULL)
			r->parent = p;
		if (tmp0 == NULL)
			*root = node_copy;
	}
}

/**
 * heap_extract - Extracts the root node of a max binary heap tree
 * @root: A pointer to the address of the tree's root node.
 *
 * Return: The value of the extracted node, otherwise NULL.
 */
int heap_extract(heap_t **root)
{
	heap_t *node, *node_left, *node_right, *temp, *dummy;
	int value = 0, val_l, val_r;

	if ((root != NULL) && (*root != NULL))
	{
		node = *root;
		node_left = node->left;
		node_right = node->right;
		value = node->n;
		temp = get_last_node(node);
		*root = ((temp != NULL) && (temp->parent != NULL) ? temp : NULL);
		if ((temp != NULL) && (temp->parent != NULL))
		{
			if (temp->parent->left == temp)
				temp->parent->left = NULL;
			if (temp->parent->right == temp)
				temp->parent->right = NULL;
			temp->parent = NULL;
			temp->left = (node_left != temp ? node_left : NULL);
			temp->right = (node_right != temp ? node_right : NULL);
			if ((node_left != NULL) && (node_left != temp))
				node_left->parent = temp;
			if ((node_right != NULL) && (node_right != temp))
				node_right->parent = temp;
			while (temp != NULL)
			{
				val_l = temp->left != NULL ? temp->left->n : temp->n;
				val_r = temp->right != NULL ? temp->right->n : temp->n;
				dummy = val_l > val_r ? temp->left : temp->right;
				if ((dummy != NULL) && (dummy->n > dummy->parent->n))
					swap_with_parent_1(&dummy, root);
				else
					break;
			}
		}
		free(node);
	}
	return (value);
}
