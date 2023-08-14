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
    /**
     * Crude Steps:
     * 1. Allocate memory
     * 2. Update properties
     * 3. Return
    */

    HSNODE *new = (HSNODE*) malloc(sizeof(HSNODE));

    strcpy(new->key, key);
    new->value = value;
    new->next = NULL;

    return new;
}

HASHTABLE *new_hashtable(int size) {
    // your implementation
    /**
     * Crude Steps:
     * 1. Allocate memory for a new HT
     * 2. Update size
     * 3. run for loop through hna, initializing each bucket to NULL
    */

    // initlaize ht
    HASHTABLE *ht = (HASHTABLE*) malloc(sizeof(HASHTABLE));
    
    // allocate memory for an array of pointers to Hash Nodes Structs, 
    // HNA holds pointers to the individual hash nodes in the table
    ht->hna = (HSNODE**) malloc(size * sizeof(HSNODE*));

    for (int i = 0; i < size; i++)
    {
        ht->hna[i] = NULL;
    }
    
    // update size and count
    ht->size = size;
    ht->count = 0;

    return ht;

}

HSNODE *search(HASHTABLE *ht, char *key) { 
    
    // your implementation

    /**
     * Crude Steps:
     * 1. convert key into an index
     * 2. create a node out of the key
     * 3. iterate through the bucket 
    */

    int index = hash(key);

    // initialize a node setting it to the first index of the bucket
    HSNODE *cur = ht->hna[index];

    while (cur) {

        if (strcmp(cur->key, key) == 0) {
            return cur;
        }
        cur = cur->next;
    }

    // not found
    return NULL;
}

int insert(HASHTABLE *ht, HSNODE *np) {
    // your implementation
    
    /**
     * Crude Steps:
     * 1. convert key into an index
     * 2. create a node out of the key
     * 3. creat a parent as well
     * 4. iterate through the bucket while key is less than value at that 
     * 5. insert into parent and set parent to the cur node
    */

    int i = hash(np->key);

    HSNODE *prev = NULL;
    HSNODE *cur = ht->hna[i];

    if (cur == NULL) {
        ht->hna[i] = np;
    }

    else {

        // while cur is not null and the node we want to insert is greater in val than the cur keep iterating
        while (cur && strcmp(np->key, cur->key) > 0) { 
            prev = cur;
            cur = cur->next;
        }

        // if the node already exists
        if (cur && strcmp(np->key, cur->key) == 0) {
            cur->value = np->value;
            free(np);
            return 0;
        }

        if (prev == NULL) {
            ht->hna[i] = np;
        }

        else {
            prev->next = np;
            np->next = cur;
        }

    }

    ht->count+=1;
    return 1;

}

int delete(HASHTABLE *ht, char *key) {
    
    // your implementation

    /**
     * Crude Steps:
     * 1. hash the key
     * 2. create a node with it
     * 3. iterate through
    */

    int i = hash(key);

    HSNODE *prev = NULL;
    HSNODE *cur = ht->hna[i];

    while (!cur) {

        // key found time to delete
        if (strcmp(cur->key, key) == 0) {

            if (prev == NULL) {
                ht->hna[0] = cur->next;
            } else {
                prev->next = cur->next;
            }

            free(cur);
            ht->count--;
            return 1;
        }

        prev = cur;
        cur = cur->next;

    }

    return 0;

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