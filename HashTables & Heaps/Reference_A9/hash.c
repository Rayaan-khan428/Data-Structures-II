/*
 ============================================================================
 Name        : hash.c
 Author      : Ryan Mood
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

extern int htsize;

int hash(char *name) {
  unsigned int value = 0, i;
  char *p = name;
  while (*p) {
    value = 31 * value + *p;
    p++;
  }
  return value % htsize;
}

HASHNODE *new_hashnode(char *name, int value) {

	HASHNODE *hn = (HASHNODE*) malloc(sizeof(HASHNODE));

	strcpy(hn->name, name);
	hn->value = value;
	hn->next = NULL;

	return hn;
}

HASHTABLE *new_hashtable(int size) {

	HASHTABLE *ht = (HASHTABLE*) malloc(sizeof(HASHTABLE));

	ht->size = size;
	ht->count = 0;

	for(int x = 0; x < size; x += 1){
		*(ht->hna + x) = NULL;
	}


	return ht;

}

HASHNODE *search(HASHTABLE *ht, char *name) {

	int x = hash(name);
	HASHNODE *p = ht->hna[x];

	if(p->name != NULL && strcmp(p->name, name) == 0){
		return p;
	}
	else{
		return NULL;
	}


}

int insert(HASHTABLE *ht, HASHNODE *np) {

	int x = hash(np->name);
	HASHNODE *p = ht->hna[x];
	HASHNODE *prev = NULL;

	if (p == NULL){
		ht->hna[x] = np;
	}
	else{
		while(p && strcmp(np->name, p->name) > 0){
			prev = p;
			p = p->next;

		}

		if (p && strcmp(np->name, p->name) == 0){
			p->value = np->value;
			np = NULL;
			free(np);

			return 0;
		}

		else{
			prev->next = p;

		}
		np->next = p;

	}
	ht->count +=1;

	return 1;

}

int delete(HASHTABLE *ht, char *name) {

	int x = hash(name);
	HASHNODE *p;
	HASHNODE *prev;

	p = ht->hna[x];
	prev = NULL;

	if(p != NULL){
		while(p && strcmp(name, p->name) > 0){
			prev = p;
			p = p->next;

		}

		if(p && strcmp(name, p->name) == 0){
			if(prev != NULL){
				prev->next = p->next;

			}
			else{
				ht->hna[x] = ht->hna[x]->next;
			}

			free(p);
			ht->count -= 1;

			return 1;
		}
	}

	return 0;
}


void clean_hash(HASHTABLE **htp) {
  if (*htp == NULL) return;
  HASHTABLE *ht = *htp;
  HASHNODE *sp = ht->hna[0], *p, *temp;
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
