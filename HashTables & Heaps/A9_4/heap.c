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
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->hna = (HNODE *)realloc(heap->hna, heap->capacity * sizeof(HNODE));
    }
}

HNODE extract_min(HEAP *heap)
{
// your implementation
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