/*
 ============================================================================
 Name        : heap.c
 Author      : Ryan Mood
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#ifndef HEAP_H
#define HEAP_H

#define MIN_CAPACITY 4

typedef int KEYTYPE;
typedef int DATA;

typedef struct heap_node { // data element ds for binary heap
  KEYTYPE key;
  DATA data;
} HEAPNODE;

typedef struct heap {
  unsigned int capacity; // the MAX length of array
  unsigned int size;     // the current heap size, i.e., heap node count
  HEAPNODE *hna;  // pointer pointing the heap node array
} HEAP;

HEAP *new_heap(int capacity);
void insert(HEAP *heap, HEAPNODE a);
HEAPNODE extract_min(HEAP *heap);
int change_key(HEAP *heap, int index, KEYTYPE new_key);
int find_data_index(HEAP *heap, DATA data);
void heap_sort(HEAPNODE *hna, int n);
int cmp(KEYTYPE a, KEYTYPE b);
void heap_swap(int *a, int *b);
int heapify_down(HEAP *source, int a);
int heapify_up(HEAP *source, int a);

#endif
