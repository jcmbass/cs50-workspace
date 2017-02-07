/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool BinarySearch(int value, int values[], int min, int max)
{
    //TODO: implemet a binary-search recursive function
    int mid = (min + max)/2;
    if (min <= max)
    {
        if(value == values[mid])
            return true;
        else if (value < values[mid])
            return BinarySearch(value, values, min, mid - 1);
        else if (value > values[mid])
            return BinarySearch(value, values, mid + 1, max);
    }
    return false;
}
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    return BinarySearch(value, values, 0, n);
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    int min, placeholder, p;
    for (int i = 0; i < n; i++)
    {
        min = values[i];
        p = i;
        for (int j = i +1; j <= n; j++)
        {
            if (values[j] < min)
                {
                    min = values[j];
                    p = j;
                }
        }
        placeholder = values[i];
        values[i] = min;
        values[p] = placeholder;
    }
    return;
}