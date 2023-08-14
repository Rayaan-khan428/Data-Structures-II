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
    HASHTABLE *ht = (HASHTABLE*) malloc(sizeof(HASHTABLE));
    ht->hna = (HSNODE**)malloc(size * sizeof(HSNODE));

    for (int i=0; i<size; i++) {
      ht->hna[i] = NULL;
    }

    ht->size = size;
    ht->count = 0;

    return ht;

}

HSNODE *search(HASHTABLE *ht, char *key) { 
    // your implementation

    // Crude Steps
    // 1. Convert key into index
    // 2. create a node with the index
    // 3. iterate through the bucket (node is the bucket) while not null.

    int i = hash(key);
    HSNODE *node = ht->hna[i];

    while (node) {

      if (strcmp(node->key, key) == 0) {
        return node;
      }
      node = node->next;
    }

    return NULL;
}

int insert(HASHTABLE *ht, HSNODE *np) {
    
    // Your implementation

    int i = hash(np->key);

    // takes us to first node in the bucket
    HSNODE *pre = NULL;
    HSNODE *cur = ht->hna[i];

    // edge case
    if (cur == NULL) {
      ht->hna[i] = np;
      return 1;
    }

    else {

      while (cur && strcmp(np->key, cur->key) > 0) {
        pre = cur;
        cur = cur->next;
      }

      // no parent means we insert at the beg
      if (pre == NULL) {
        np->next = cur;
      }

      // node already exists
      else if (strcmp(cur->key,np->key) == 0) {
        cur->value = np->value;
      }

      // else we insert between pre and cur
      else {
        pre->next = np;
        np->next = cur;
      }

  
    }
}

int delete(HASHTABLE *ht, char *key) {
    
    // hashing  
    int i = hash(key);

    // pointers for tracking
    HSNODE *prev = NULL;
    HSNODE *cur = ht->hna[i];

    while (cur != NULL) {

      if (strcmp(cur->key, key) == 0) {

        if (prev == NULL) {
          ht->hna[i] = cur->next;
        } else {
          prev->next = cur->next;
          free(cur);
        }

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