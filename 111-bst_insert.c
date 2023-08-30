#include "binary_trees.h"
/**
 * bst_insert - insert nodes in order to create a BST tree
 * @tree: tree to create with type BST
 * @value: value of node to insert
 * Return: BST tree
 */
bst_t *bst_insert(bst_t **tree, int value)
{
	bst_t *newnode, *tempnode;
	binary_tree_t *auxnode;

	if (tree == NULL)
		return (NULL);

	if (*tree == NULL)
	{
		auxnode = binary_tree_node((binary_tree_t *)(*tree), value);
		newnode = (bst_t *)auxnode;
		*tree = newnode;
	}
	else
	{
		tempnode = *tree;
		if (value < tempnode->n)
		{
			if (tempnode->left)
				newnode = bst_insert(&tempnode->left, value);
			else
			{
				auxnode = binary_tree_node((binary_tree_t *)tempnode, value);
				newnode = tempnode->left = (bst_t *)auxnode;
			}
		}
		else if (value > tempnode->n)
		{
			if (tempnode->right)
				newnode = bst_insert(&tempnode->right, value);
			else
			{
				auxnode = binary_tree_node((binary_tree_t *)tempnode, value);
				newnode = tempnode->right = auxnode;
			}
		}
		else
			return (NULL);
	}
	return (newnode);
}
