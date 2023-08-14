#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "heap.h"

HEAP *new_heap(int capacity)
{
    // your implementation
    if (capacity < MIN_CAPACITY)
        capacity = MIN_CAPACITY;

    HEAP *heap = (HEAP*) malloc(sizeof(HEAP));

    heap->capacity = capacity;
    heap->size = 0;
    heap->hna = (HNODE*)(capacity*sizeof(HNODE));

    return heap;

}

void insert(HEAP *heap, HNODE new_node)
{
    // your implementation

    /**
     * Crude Steps:
     * 1. Check if the size of heap, is > capacity and double if it is
     * 2. if not then simply insert at the end of the hna array
     * 3. call heapify up that ensures the new node is in the right position
     *    to satisfy the structure/order property
    */

    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->hna = (HNODE*)realloc(heap->hna, heap->capacity*sizeof(HNODE));
    }

    // add the new node to the last index in the array
    heap->hna[heap->size] = new_node;
    heap->size++;

    // restore order
    heapify_up(heap, heap->size-1);

}

void heapify_up(HEAP *heap, int index) {

    /**
     * Crude Steps:
     * 1. calculate parent index (index-1)/2
     * 2. create a while loop, while index is greater than 0
     *    and the key at the parent is larger than key at the cur index
     *    swap the two.
     * 3. update the index to the parent index, and recalculate the parent index
     * 4. repeat
    */
    int parent_index = (index-1)/2; 
    while (index > 0 && strcmp(heap->hna[index].key, heap->hna[parent_index].key) < 0) {
        swap(&heap->hna[index], &heap->hna[parent_index]);
        index = parent_index;
        parent_index = (index-1)/2;
    }
}

void swap (HNODE *a, HNODE *b) {

    HNODE temp = *a;
    *a = *b;
    *b = temp;

}

HNODE extract_min(HEAP *heap)
{
    // your implementation

    /**
     * Crude Steps:
     * 1. extract the min from the very top
     * 2. take the last element in the hna array and add it to the the beg
     * 3. update the size
     * 4. call heapify down that restores the order propery
    */

    // if the size is 0 aka empty
    if (heap->size == 0) {
        HNODE empty_node = {0,0};
        return empty_node;
    }

    // store the min into a variable
    HNODE min = heap->hna[0]; 

    // take the last element and put it where we took out the min from
    heap->hna[0] = heap->hna[heap->size-1];
    heap->size--;

    // restore the order property and shit
    heapify_down(heap, 0);

    return min;

}

void heapify_down(HEAP *heap, int index) {

    /**
     * Crude Steps:
     * Calculate left child and right child
     * Store the index of the smallest node, which right now is the root.
     * Check if the current index is bigger than either the left or right child
     * if it is swap, and continue (recursively)
    */
    int left_child = 2*index+1;
    int right_child = 2*index+2;
    int smallest = index;

    // if the left child is less than the heap size (we aren't exceeding the heap size)
    // & when comparing the two values if the left child is less than the the root
    if (left_child < heap->size && cmp(heap->hna[left_child].key, heap->hna[smallest].key) < 0) {
        // we update the smallest to the left child
        smallest = left_child;
    }

    if (right_child < heap->size && cmp(heap->hna[right_child].key, heap->hna[smallest].key) < 0) {
        // we update the smallest to the right child
        smallest = right_child;
    }

    // if these two values are not equal we now know that 
    // whatever was at the initial index is not actually the smallest
    if (smallest != index) {

        // so we swap whatever was at the root index, with what is at the smallest index we found
        swap(&heap->hna[index], &heap->hna[smallest]);

        // this is continually repeated recursively
        heapify_down(heap,smallest);
    }
}

void change_key(HEAP *heap, int index, KEYTYPE new_key)
{
    // your implementation
}

int find_data_index(HEAP *heap, DATA data) {
    // your implementation
}

int cmp(KEYTYPE a, KEYTYPE b) {
    // your implementation
}