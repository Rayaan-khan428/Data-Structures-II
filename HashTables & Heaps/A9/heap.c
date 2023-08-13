#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

HEAP *new_heap(int capacity)
{
    if (capacity < MIN_CAPACITY)
        capacity = MIN_CAPACITY;

    HEAP *heap = (HEAP *)malloc(sizeof(HEAP));
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

void heapify_up(HEAP *heap, int index)
{
    int parent_index = (index - 1) / 2;
    while (index > 0 && cmp(heap->hna[index].key, heap->hna[parent_index].key) < 0)
    {
        swap(&heap->hna[index], &heap->hna[parent_index]);
        index = parent_index;
        parent_index = (index - 1) / 2;
    }
}

void heapify_down(HEAP *heap, int index)
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

void insert(HEAP *heap, HNODE new_node)
{
    if (heap->size == heap->capacity)
    {
        heap->capacity *= 2;
        heap->hna = (HNODE *)realloc(heap->hna, heap->capacity * sizeof(HNODE));
    }

    heap->hna[heap->size] = new_node;
    heap->size++;
    heapify_up(heap, heap->size - 1);
}

HNODE extract_min(HEAP *heap)
{
    if (heap->size == 0)
    {
        HNODE empty_node = {0, 0};
        return empty_node;
    }

    HNODE min_node = heap->hna[0];
    heap->hna[0] = heap->hna[heap->size - 1];
    heap->size--;
    heapify_down(heap, 0);

    return min_node;
}

int change_key(HEAP *heap, int index, KEYTYPE new_key)
{
    if (index < 0 || index >= heap->size)
        return 0;

    if (cmp(new_key, heap->hna[index].key) > 0)
    {
        heap->hna[index].key = new_key;
        heapify_down(heap, index);
    }
    else if (cmp(new_key, heap->hna[index].key) < 0)
    {
        heap->hna[index].key = new_key;
        heapify_up(heap, index);
    }

    return 1;
}

int find_data_index(HEAP *heap, DATA data)
{
    for (int i = 0; i < heap->size; i++)
    {
        if (heap->hna[i].data == data)
            return i;
    }
    return -1;
}

int cmp(KEYTYPE a, KEYTYPE b)
{
    if (a == b)
        return 0;
    return a < b ? -1 : 1;
}