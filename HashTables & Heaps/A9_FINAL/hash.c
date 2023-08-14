#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "hash.h"

extern int htsize;

int hash(char* word) {
  unsigned int hash = 0, i;
  for (i = 0; word[i] != '\0'; i++) {
    hash = 31 * hash + word[i];
  }
  return hash % htsize;
}

HSNODE *new_hashnode(char *key, int value) {
    
    // your implementation
    HSNODE *node = (HSNODE*) malloc(sizeof(HSNODE));

    strcpy(node->key, key);
    node->value = value;
    node->next = NULL;

    return node;

}

HASHTABLE *new_hashtable(int size) {
    
    // your implementation
    HASHTABLE *ht = (HASHTABLE*)malloc(sizeof(HASHTABLE));
    ht->hna = (HSNODE**)malloc(size*sizeof(HSNODE*));

    for (int i = 0; i < size; i++)
    {
        ht->hna[i] = NULL;
    }

    ht->size = size;
    ht->count = 0;
    
}

HSNODE *search(HASHTABLE *ht, char *key) { 
    // your implementation

    // Crude Steps
    // 1. Convert key into index
    // 2. create a node with the index
    // 3. iterate through the bucket while not null.

    // hashing
    int i = hash(key);

    // node
    HSNODE *cur = ht->hna[i];


    // iterate
    while (cur) {

        if (strcmp(cur->key, key) == 0) {
            return cur;
        }
        cur = cur->next;
    }   

    return NULL;

}

int insert(HASHTABLE *ht, HSNODE *np) {
    
    // Your implementation

    // Hashing
    int i = hash(np->key);

    // Node
    HSNODE *prev = NULL;
    HSNODE *cur = ht->hna[i];

    // Edge case
    if (cur == NULL) {
        return;
    }

    else {
        // Iterate
        while (cur && strcmp(np->key, cur->key) > 0) {
            prev = cur;
            cur = cur->next;
        }

        // check

        // no parent (aka want to insert at beg)
        if (prev == NULL) {
            np->next = cur;
        }
        
        // node already exists
        else if (cur && strcmp(np->key, cur->key) == 0) {
            cur->value = np->value;
        }

        // insert in between
        else {
            prev->next = np;
            np->next = cur;
        }

        ht->count += 1;
    }

    return NULL;

}

int delete(HASHTABLE *ht, char *key) {
    
    // hashing
    int i = hash(key);

    // pointers to track
    HSNODE *prev = NULL;
    HSNODE *cur = ht->hna[i];

    while (cur != NULL) {  // Fix the loop condition

        if (strcmp(cur->key, key) == 0) {

            if (prev == NULL) {
                ht->hna[i] = cur->next;
            } else {
                prev->next = cur->next;
                free(cur);
            }

            ht->count--;  // Decrement the count of elements
            return 1;
        }

        prev = cur;
        cur = cur->next;
    }

    return 0;  // Return 0 if the key was not found
}



void clean_hash(HASHTABLE **htp) {
  if (*htp == NULL) return;
  HASHTABLE *ht = *htp;
  HSNODE *sp = ht->hna[0], *p, *temp;
  int i;
  for (i = 0; i < ht->size; i++) {
    p = ht->hna[i];
    while (p) {
      temp = p;  
      p = p->next;
      free(temp);
    }
    ht->hna[i] = NULL;
  }
  free(ht->hna);
  ht->hna = NULL;
  *htp = NULL;
}