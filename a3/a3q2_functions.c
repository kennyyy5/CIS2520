#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "a3q2_header.h"

/*
 * The downHeap function performs the downheap algorithm.
 * The key at the passed position is swapped with the key of it's child with the smallest value.
 * If the key is smaller, than both of it's children's keys then no swap happens.
 * After swap, the downHeap is called again to the new position of the swapped key and it terminates when it's value is smaller than both children.
 */
void downHeap(int key[20], int pos, int array[20][10])
{
    while (isParent(pos))
    {
        int leftChild = 2 * pos + 1;
        int rightChild = 2 * pos + 2;
        int largest = pos;

        // Find the largest of parent and children
        if (leftChild < 20 && key[leftChild] > key[largest])
        {
            largest = leftChild;
        }
        if (rightChild < 20 && key[rightChild] > key[largest])
        {
            largest = rightChild;
        }

        if (largest != pos)
        {
            swap(pos, largest, key, array);
            pos = largest; // Continue downHeap for the swapped child
        }
        else
        {
            break;
        }
    }
}

// The isParent function returns true if the passed position has a child or false if there's no child
bool isParent(int keyPos)
{
    return (2 * keyPos + 1) < 20;
}

// The swap function swaps 2 rows in the 2D array and the key array. It receives the position of the 2 rows to be swapped, the key array, and the 2D array in its arguements.
void swap(int key1Pos, int key2Pos, int key[20], int array[20][10])
{
    int tempKey = key[key1Pos];
    key[key1Pos] = key[key2Pos];
    key[key2Pos] = tempKey;

    for (int j = 0; j < 10; j++)
    {
        int temp = array[key1Pos][j];
        array[key1Pos][j] = array[key2Pos][j];
        array[key2Pos][j] = temp;
    }
}
