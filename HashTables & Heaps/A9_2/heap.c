#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

HEAP *new_heap(int capacity)
{

    // if the capacity is smaller than min
    if (capacity < MIN_CAPACITY) {
        capacity = MIN_CAPACITY;
    }

    // allocate memory
    HEAP *heap = (HEAP*)malloc(sizeof(HEAP));
    
    // set properties
    heap->capacity = capacity;
    heap->size = 0;
    heap->hna = (HNODE*)malloc(capacity*sizeof(HNODE));

}

void swap(HNODE *a, HNODE *b)
{
    HNODE temp = *a;
    *a = *b;
    *b = temp;

}

void insert(HEAP *heap, HNODE new_node)
{

}

// Auxiliry for heap, used when we insert a new element to a heap and need to maintain the properties
// of a min-heap
void heapify_up(HEAP *heap, int index)
{
    // this is the formula for retreiving the parent of the index we've been passed
    int parentIndex = (index-1)/2;

    /*
    first condition means while we haven't reached the root node
    the second condition is while the index of what we've inserted is < the parent
    */
    while (index > 0 && cmp(heap->hna[index].key, heap->hna[parentIndex].key) < 0) {

        // preform the swap 
        swap(&heap->hna[index], &heap->hna[parentIndex]);
        
        // update index
        index = parentIndex;

        // recalculate parent index
        parentIndex = (index - 1)/2;

    }

}


HNODE extract_min(HEAP *heap)
{   
    // if the size of the heap is 0 it means that it is empty
    if (heap->size == 0)
    {
        HNODE empty_node = {0, 0};
        return empty_node;
    }

    // create a min node equal to whatever is first in the heap (aka the heap array)
    HNODE min_node = heap->hna[0];

    // set the value at index 0 of the heap, to the last value in the array/node in the tree
    heap->hna[0] = heap->hna[heap->size - 1];

    // updates the size
    heap->size--;

    // to fix the order property 
    heapify_down(heap, 0);

    return min_node;
}

void heapify_down(HEAP *heap, int parent_index)
{
    int left_child_index = 2 * parent_index + 1;
    int right_child_index = 2 * parent_index + 2;
    int smallest_index = parent_index;  // Assume the parent is the smallest for now

    // Compare the value of the left child with the parent's value
    if (left_child_index < heap->size && 
        cmp(heap->hna[left_child_index].key, heap->hna[smallest_index].key) < 0)
    {
        smallest_index = left_child_index;  // Update if the left child is smaller
    }

    // Compare the value of the right child with the smallest value so far
    if (right_child_index < heap->size && 
        cmp(heap->hna[right_child_index].key, heap->hna[smallest_index].key) < 0)
    {
        smallest_index = right_child_index;  // Update if the right child is smaller
    }

    // If the smallest value is not the parent, swap and continue heapify down
    if (smallest_index != parent_index)
    {
        swap(&heap->hna[parent_index], &heap->hna[smallest_index]);

        // Continue heapifying down with the child that was swapped
        heapify_down(heap, smallest_index);
    }
}


int change_key(HEAP *heap, int index, KEYTYPE new_key)
{

}

int find_data_index(HEAP *heap, DATA data)
{

}

int cmp(KEYTYPE a, KEYTYPE b)
{

}