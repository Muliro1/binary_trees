#include "binary_trees.h"

/**
 * reallocate - Reallocates a memory block
 * @ptr: The pointer to the previous memory block
 * @old_size: The size of the old memory block
 * @new_size: The size of the new memory block
 *
 * Return: The pointer to the new memory block otherwise NULL
 */
void *reallocate(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new_pointer;
	unsigned int min_size = old_size < new_size ? old_size : new_size;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);
	if (ptr != NULL)
	{
		if (new_size == 0)
		{
			free(ptr);
			return (NULL);
		}
		new_pointer = malloc(new_size);
		if (new_pointer != NULL)
		{
			for (i = 0; i < min_size; i++)
				*((char *)new_pointer + i) = *((char *)ptr + i);
			free(ptr);
			return (new_pointer);
		}
		free(ptr);
		return (NULL);
	}
	else
	{
		new_pointer = malloc(new_size);
		return (new_pointer);
	}
}

/**
 * heap_to_sorted_array - Creates a sorted array from a max binary heap tree.
 * @heap: A pointer to the max binary heap.
 * @size: A pointer to the resulting array's size value.
 *
 * Return: A pointer to the array, otherwise NULL.
 */
int *heap_to_sorted_array(heap_t *heap, size_t *size)
{
	int *array = NULL;
	heap_t *rootnode;
	int val;
	size_t n = 0;

	if (heap != NULL)
	{
		rootnode = heap;
		while (rootnode != NULL)
		{
			val = heap_extract(&rootnode);
			array = reallocate(array, sizeof(int) * n, sizeof(int) * (n + 1));
			*(array + n) = val;
			n++;
		}
	}
	if (size != NULL)
		*size = n;
	return (array);
}
