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

    // allocate memory for new node
    HSNODE *newNode = (HSNODE*)malloc(sizeof(HSNODE));

    // assign key and value to our new node
    strcpy(newNode->key, key);
    newNode->value = value;
    newNode->next = NULL;

    // return it
    return newNode;
    
}

HASHTABLE *new_hashtable(int size) {

  // allocate memory for new hashtable
  HASHTABLE *ht = (HASHTABLE*)malloc(sizeof(HASHTABLE));

  // If memory allocation fails
  if (ht == NULL) {
    return NULL;
  }

  // HNA is a pointer pointing to an array of pointers that point to HNodes
  ht->hna = (HSNODE**) malloc(size * sizeof(HSNODE*));

  // initializes all the elements within hna to null
  // each element represents a slot/bucket in the hashtable
  // the hashtable isn't empty, it has "size" # of buckets, that hold NULL
  for (int i = 0; i < size; i++)
  {
    ht->hna[i] = NULL;
  }

  // update size & count
  ht->size = size;
  ht->count = 0;

  return ht;

}

HSNODE *search(HASHTABLE *ht, char *key) {


  /**
   * 
   * 1. run key through hash function, to get an index
   * 2. access the bucket at that index in the hna
   * 3. if the bucket has more than one node, iterate through unitl match
   * 4. return node or null
   * 
  */

  // get index of the key
  int i = hash(key);

  // create a node from what is at that index
  HSNODE *curNode = ht->hna[i];

  // traverse through the linkedList at that index
  while (curNode != NULL) {

    // if the curNode key and the key we want match return the node
    if (strcmp(curNode->key, key) == 0) {
      return curNode;
    } else {
      curNode = curNode->next; // move onto next node in the array
    }
  }
  
  // key not found
  return NULL;
}

int insert(HASHTABLE *ht, HSNODE *np) {

  /**
   * Crude Steps
   * 1. Create a duplicate of the key, and generate an index for it
   * 2. create a parent and cur pointer, for what is at the index in the ht
   * 3. If index is null add the node
   * 4. Traverse through linked list until we're at appropriate position to insert
   * 5. If node exists update value
   * 
  */

  // create a duplicate of key and convert to an index
  int i = hash(strdup(np->key));

  // for traversing through the bucket
  HSNODE *cur = ht->hna[i];
  HSNODE *prev = NULL;

  // bucket is empty, insert out node
  if (cur == NULL) {
    ht->hna[i] = np;
  }

  else {

    // iterate through bucket while cur key is less than existing key vals
    while (cur && strcmp(np->key, ht->hna[i]->key) > 0) {
       prev = cur; 
       cur = cur->next;
    }

    // we are now at the position where we need to insert

    // check if a node with the same key already exists
    if (cur && strcmp(np->key, cur->key) == 0) {
      // update cur value
      cur->value = np->value;
      free(np);
      return 0;
    }

    // first node in the list
    else if (prev == NULL) {
      ht->hna[i] = np;
    }

    // insert between prev node and the cur node.
    else {
      prev->next = np;
      np->next = cur;
    }
  }
  
  // update count
  ht->count += 1;
  return 1;

}

int delete(HASHTABLE *ht, char *key) {

  /**
   * Crude Steps:
   * Calculate index of key
   * use prev and cur pointer to iterate through
   * once match is found, set parent to its child
   * and free cur
   * 
  */

  // if invalid input is passed
  if (ht == NULL || key == NULL) {
    return 0;
  }

  // generate index for key
  int i = hash(key);

  // pointers for when we iterate through the nodes in a bucket
  HSNODE *prev = NULL;
  HSNODE *cur = ht->hna[i];

  // 
  while (cur != NULL) {

    // match found, delete this node
    if (strcmp(key, cur->key) == 0) {
      
      // no parent (head of linked list)
      if (prev == NULL) {
        ht->hna[i] = cur->next;
      } 
      
      // has parent
      else {
        prev->next = cur->next;
      }

      free(cur);
      ht->count--;
      return 1; // tells main node is deleted
      
    }

  }

  // key not found
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