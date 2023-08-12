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
    
  // allocate the memory
  HSNODE *newNode = (HSNODE*)(malloc(sizeof(HSNODE)));

  // assign key nad value to the node
  strcpy(newNode->key, key);
  newNode->value = value;
  newNode->next = NULL;

}

HASHTABLE *new_hashtable(int size) {

  // allocate memory
  HASHTABLE *ht = (HASHTABLE*)malloc(sizeof(HASHTABLE));

  if (ht == NULL) {
    return NULL;
  }

  // HNA is a pointer pointing to an array of pointers that point to HNOdes
  ht->hna = (HSNODE**) malloc(size * sizeof(HSNODE*));

  // inititlizes all the elements within hna to NULL
  // each element represents a slot/bucket
  // the ht isn't empty its all defined just to NULL
  for (int i = 0; i < size; i++)
  {
    ht->hna[i] = NULL;
  }

  ht->size = size;
  ht->count = 0;

  return ht;
}

HSNODE *search(HASHTABLE *ht, char *key) {

  /**
   * Crude Steps:
   * 1. run key through hash function
   * 2. acess bucket at that index
   * 3. if bucket has more than one node, iterate until match
   * 4. return node/null
  */

  // 1.
  int i = hash(key);

  // 2.
  HSNODE *curNode = ht->hna[i];

  // 3.
  while (curNode != NULL) {

    if (strcmp(curNode->key, key)) {
      return curNode; 
    } else {
      curNode = curNode->next;
    }
  }

  return NULL;

}

int insert(HASHTABLE *ht, HSNODE *np) {
  
  /**
   * Crude Steps:
   * 1. run key through hash function
   * 2. acess bucket at that index
   * 3. if bucket has more than one node, iterate until in appropriate position
   * 4. return
  */

  // convert to index
  int i = hash(strdup(np->key));
  
  // for traversing
  HSNODE *prev = NULL;
  HSNODE *cur = ht->hna[i];

  // edge case: bucket is empty
  if (cur == NULL) {
    ht->hna[i] = np;
  }

  else {
    // loop through linkedlist in bucket while cur kep is greater
    while (cur && strcmp(np->key, ht->hna[i]->key) > 0) {
      prev = cur;
      cur = cur->next;
    }

    
    if (cur && strcmp(np->key, cur->key) == 0) {
      cur->value = np->value;
      free(np);
      return 0;
    }

    else if (prev == NULL) {
      ht->hna[i] = np;
    }

    else {
      prev->next = np;
      np->next = cur;
    }

  }

  ht->count += 1;
  return 1;

}

int delete(HASHTABLE *ht, char *key) {

  // convert to index
  int i = hash(key);
  
  // for traversing
  HSNODE *prev = NULL;
  HSNODE *cur = ht->hna[i];

  while (cur != NULL) {

    // match found, delete this node
    if (strcmp(key, cur->key) == 0) {
      
      // match with no parent
      if (prev == NULL) {
        ht->hna[i] = cur->next;
      } else {
        prev->next = cur->next;
      }

      free(cur);
      ht->count--;
      return 1; // tells main node is deleted
    }
  }
  return;
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