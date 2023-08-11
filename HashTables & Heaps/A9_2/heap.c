#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "heap.h"

HEAP *new_heap(int capacity)
{
    // your implementation
    HEAP *newHeap = (HEAP*)malloc(sizeof(HEAP));
    
    // match the given capacity
    newHeap->capacity = capacity;

    // Allocate memory to hold an array of HNODES
    newHeap->hna = (HNODE*) malloc(sizeof(HNODE)*capacity);

    return newHeap;

}

void insert(HEAP *heap, HNODE new_node)
{
    // your implementation

    // if the capacity is full, we will have to reallocate space
    if (heap->size == heap->capacity) {        
        // double the capacity of the heap
        heap->capacity *= 2; 

        // temporary array to hold the elements of the heap after resizing
        HNODE *temp = (HNODE*)malloc(sizeof(HNODE)*heap->capacity);

        // if temp isn't NULL
        // copy the contents of the original array into temp
        if (temp) {
            memcpy(temp, heap->hna, sizeof(HNODE) * heap->size);
            free(heap->hna);
            heap->hna = temp;
        } else {
            printf("resize failed\n");
        }
    }

    // Inseration & Heapify

    // new node is inserted into the heap at the very end of the array
    heap->hna[heap->size] = new_node; 
    
    // This is where we heapify up from
    int i = heap->size-1;
    while (i > 0) {

        int parentIndex = (i-1)/2; // calculation of parent index

        // compare the current node with its parent
        if (heap->hna[i].data > heap->hna[parentIndex].data) {

            // the swap
            HNODE swap = heap->hna[i];
            heap->hna[i] = heap->hna[parentIndex];
            heap->hna[parentIndex] = swap;

            // Move up to the parent index and continue the loop
            i = parentIndex;
        } else {
            // no need to sort already in the right order
            break;
        }


    }

    // update the size
    heap->size++;
    return;
}

HNODE extract_min(HEAP *heap)
{
    // your implementation
    HNODE minNode = heap->hna[0];
    heap->size--;
    heapify_down(heap,0);

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