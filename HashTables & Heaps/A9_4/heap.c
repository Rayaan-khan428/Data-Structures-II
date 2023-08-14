#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "heap.h"

HEAP *new_heap(int capacity)
{
    // your implementation

    if (capacity < MIN_CAPACITY) {
        capacity = MIN_CAPACITY;
    }

    HEAP *heap = (HEAP*)malloc(sizeof(HEAP));

    heap->capacity = capacity;
    heap->size = 0;
    heap->hna = (HNODE *)malloc(capacity * sizeof(HNODE));

    return heap;

}

void swap(HNODE *a, HNODE *b)
{
    HNODE temp = *a;
    *a = *b;
    *b = temp;
}

void insert(HEAP *heap, HNODE new_node)
{
    // your implementation
    
    // update space
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->hna = (HNODE *)realloc(heap->hna, heap->capacity * sizeof(HNODE));
    }

    // insert at the very last index
    heap->hna[heap->size] = new_node;
    heap->size++;
    heapify_up(heap, heap->size-1);

}

void heapify_up(HEAP *heap, int index)
{
    // restore order and structure of the heap
    int parent = (index-1)/2;

    while (index > 0 && cmp(heap->hna[index].key, heap->hna[parent].key)) {
        
        swap(&heap->hna[index], &heap->hna[parent]);
        index = parent;
        parent = (index - 1) / 2;

    }

}

HNODE extract_min(HEAP *heap)
{
    // your implementation
    if (heap->size == 0) {
        HNODE empty_node = {0,0};
        return empty_node;
    }

    HNODE minNode = heap->hna[0];

    heap->hna[0] = heap->hna[heap->size-1];
    heap->size--;
    heapiy_down(heap, 0);

    return minNode;
}

void heapiy_down(HEAP *heap, int index)
{
    int left_child = 2 * index + 1;
    int right_child = 2 * index + 2;
    int smallest = index;

    if (left_child < heap->size && cmp(heap->hna[left_child].key, heap->hna[smallest].key) < 0)
        smallest = left_child;

    if (right_child < heap->size && cmp(heap->hna[right_child].key, heap->hna[smallest].key) < 0)
        smallest = right_child;

    if (smallest != index)
    {
        swap(&heap->hna[index], &heap->hna[smallest]);
        heapify_down(heap, smallest);
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