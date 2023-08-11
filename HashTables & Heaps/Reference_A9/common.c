/*--------------------------------------------------
Project: cp264-a6
File:    common.c
Description: implementation of common.h
Author:  HBF  
Version: 2023-02-16
--------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include "common.h"

NODE *new_node(int data, int type) {
  NODE *p = (NODE *) malloc(sizeof(NODE));
  if (p) {
    p->data = data;
    p->type = type;
    p->next = NULL;
  }
  return p;
}

void clean(NODE **startp) {
  if (startp==NULL) return;
  NODE *temp, *p = *startp;
  while (p) {
    temp = p;
    p = p->next;
    free(temp);
  }
  *startp = NULL;
}

void display(NODE *start) {
  NODE *p = start;	
  while (p) {
    if (p->type == 0) 
      printf("%d", p->data);
    else 
      printf("%c", p->data);      
    
     p = p->next;
    
    if (p) printf(" ");
  }
}