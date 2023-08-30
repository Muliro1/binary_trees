#include "binary_trees.h"

/**
 * array_to_heap - Creates a max binary heap tree from an array.
 * @array: T=A pointer to the array of values.
 * @size: The length of the array.
 *
 * Return: A pointer to the max binary heap tree, otherwise NULL.
 */
heap_t *array_to_heap(int *array, size_t size)
{
	size_t n;
	heap_t *root = NULL;

	if (array != NULL)
	{
		for (n = 0; n < size; n++)
		{
			heap_insert(&root, *(array + n));
		}
	}
	return (root);
}
