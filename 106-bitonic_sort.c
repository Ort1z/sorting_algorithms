#include <stdio.h>

/**
 * swap - Swaps two integers
 * @a: First integer
 * @b: Second integer
 */
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    printf("Swapping %d and %d\n", temp, *a);
}

/**
 * compare_and_swap - Compares and swaps elements based on direction
 * @array: Array to be sorted
 * @i: First index
 * @j: Second index
 * @dir: Direction (1 for ascending, 0 for descending)
 */
void compare_and_swap(int *array, int i, int j, int dir)
{
    if ((array[i] > array[j]) == dir)
        swap(&array[i], &array[j]);
}

/**
 * bitonic_merge - Recursively sorts a subarray in ascending or descending order
 * @array: Array to be sorted
 * @low: Starting index of the subarray
 * @cnt: Number of elements in the subarray
 * @dir: Direction (1 for ascending, 0 for descending)
 */
void bitonic_merge(int *array, int low, int cnt, int dir)
{
    if (cnt > 1)
    {
        int k = cnt / 2;

        for (int i = low; i < low + k; i++)
            compare_and_swap(array, i, i + k, dir);

        bitonic_merge(array, low, k, dir);
        bitonic_merge(array, low + k, k, dir);
    }
}

/**
 * bitonic_sort - Sorts an array using the Bitonic sort algorithm
 * @array: Array to be sorted
 * @size: Size of the array
 */
void bitonic_sort(int *array, size_t   
 size)
{
    int n = size;
    int k = 1;

    while (k < n)
    {
        for (int i = 0; i < n - k; i++)
        {
            int dir = (i & k) == k ? 1 : 0;
            bitonic_merge(&array[i], k, k, dir);
        }
        k = k * 2;
    }
}
