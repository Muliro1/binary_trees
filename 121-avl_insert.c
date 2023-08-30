#include "binary_trees.h"

/**
 * r_insert_node - node value instertion in a AVL.
 * @tree: type **pointer of root node of the AVL tree struct.
 * @parent: parent node of struct AVL.
 * @new: type**pointer left or right insertion.
 * @nvalue: insertion value of the AVL.
 * Return: pointer to the new root after insertion otherwise NULL
 */
avl_t *r_insert_node(avl_t **tree, avl_t *parent, avl_t **new, int nvalue)
{
	int bvalue;

	if (*tree == NULL)
		return (*new = binary_tree_node(parent, nvalue));
	if ((*tree)->n > nvalue)
	{
		(*tree)->left = r_insert_node(&(*tree)->left, *tree, new, nvalue);
		if ((*tree)->left == NULL)
			return (NULL);
	}
	else if ((*tree)->n < nvalue)
	{
		(*tree)->right = r_insert_node(&(*tree)->right, *tree, new, nvalue);
		if ((*tree)->right == NULL)
			return (NULL);
	}
	else
	{
		return (*tree);
	}
	bvalue = binary_tree_balance(*tree);
	if (bvalue > 1 && (*tree)->left->n > nvalue)
	{
		*tree = binary_tree_rotate_right(*tree);
	}
	else if (bvalue > 1 && (*tree)->left->n < nvalue)
	{
		(*tree)->left = binary_tree_rotate_left((*tree)->left);
		*tree = binary_tree_rotate_right(*tree);
	}
	else if (bvalue < -1 && (*tree)->right->n < nvalue)
	{
		*tree = binary_tree_rotate_left(*tree);
	}
	else if (bvalue < -1 && (*tree)->right->n > nvalue)
	{
		(*tree)->right = binary_tree_rotate_right((*tree)->right);
		*tree = binary_tree_rotate_left(*tree);
	}
	return (*tree);
}
/**
 * avl_insert - inserts a value into an AVL tree.
 * @tree: type **pointer to the root node of the AVL tree to insert into.
 * @value: value to store in the node to be inserted
 * Return: inserted node, or NULL if fails.
 */
avl_t *avl_insert(avl_t **tree, int value)
{
	avl_t *newnode = NULL;

	if (*tree == NULL)
	{
		*tree = binary_tree_node(NULL, value);
		return (*tree);
	}
	r_insert_node(tree, *tree, &newnode, value);
	return (newnode);
}
