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

    HSNODE *newNode = (HSNODE*)malloc(sizeof(HSNODE)); // allocate memory for the new node

    strcpy(newNode->key, key); // store the key into the node
    newNode->value = value; // store the value
    newNode->next = NULL; // set to NULL

    return newNode
}

HASHTABLE *new_hashtable(int size) {
    
    // your implementation

    HASHTABLE *ht = (HASHTABLE*)malloc(sizeof(HASHTABLE)); // allocate memory for a new hashtable

    // if memory allocation fails
    if (ht == NULL) {
        return NULL;
    }

    // allocate memory for an array of pointers to Hash Nodes Structs, 
    // HNA holds pointers to the individual hash nodes in the table
    ht->hna = (HSNODE**) malloc(size * sizeof(HSNODE*));

    // initializes all elements of the 'hna' array to NULL.
    // each element of the array represents a slot/bucket in the hash table.
    // At this point the hash table is empty, so all slots are initialized to hold NULL
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

    // Converts the key into a numerical value
    // The index where the key value pair is stored
    int index = hash(key);

    // create a Hash node using the data at the given index
    HSNODE *current_node = ht->hna[index]; 

    // to traverse through the linked list of hash nodes at a specific hash table index
    // since one index can contain multiple nodes
    while (current_node != NULL) {

        if (strcmp(current_node->key, key) == 0) {
            // the key is found at the current node
            return current_node;
        }
        current_node = current_node->next;
    }
    // key not found
    return NULL; 
}

int insert(HASHTABLE *ht, HSNODE *np) {
    // your implementation

    // create a duplicate of the key and run it through the hash function to give it an index
    int i = hash(strdup(np->key));

    // create a pointer pointing to the content of what is at the index in the hash table
    HSNODE *p = ht->hna[i];
    HSNODE *pp = NULL; 

    // if the index is empty then we add the hashnode we want to insert there
    if (p == NULL) {
        ht->hna[i] = np; // set new node as the leading node
    } 

    else {

        // traverses till we are at the appropriate position to insert the element
        while (p && strcmp(np->key, p->key) > 0) {
            pp = p; // save the prev node (the one right before the pointer)
            p = p->next; // set p to the next node in the linked list
        }

        // node already exists in the list
        if (p && strcmp(np->key, p->key) == 0) {     
            // update the exisitng nodes value 
            p->value = np->value;
            free(np); 
            return 0;
        }

        // inserting the node into the first position of the list
        if (pp = NULL) {
            ht->hna[i] = np;
        }

        // insert the new node between pp and p
        else {
            pp->next = np;
            np->next = p;
        }

    }

    ht->count+=1;
    return 1;
}

int delete(HASHTABLE *ht, char *key) {
    if (ht == NULL || key == NULL) {
        return 0; // Invalid input parameters
    }

    int index = hash(key); // Calculate the hash value of the key to get the index

    HSNODE *prev_node = NULL;
    HSNODE *current_node = ht->hna[index];

    while (current_node != NULL) {
        if (strcmp(current_node->key, key) == 0) {
            // Key found, delete the node
            if (prev_node == NULL) {
                // If the node to be deleted is the head of the linked list
                ht->hna[index] = current_node->next;
            } else {
                prev_node->next = current_node->next;
            }

            free(current_node);
            ht->count--;
            return 1; // Successfully deleted the node
        }

        prev_node = current_node;
        current_node = current_node->next;
    }

    // Key not found in the hash table
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