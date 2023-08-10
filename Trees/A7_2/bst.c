#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"


TNODE *search(TNODE *root, char *name) {
    // Preforming PreOrder Search // recursive search
    // edge case 1: no root, or root is the name
    if (!root || strcmp(root->data.name, name) == 0) {
        return root;
    } 
    
    else {
        if (strcmp(root->data.name, name) > 0) {
            return search(root->left, name);
        } 
        
        else if (strcmp(root->data.name, name) < 0) {
            return search(root->right, name);
        } 
        
        else {
            return root;
        }
    }

    // Iterative Appraoch

    // while root is not NULL
    while (root) {




    }



}


void insert(TNODE **rootp, char *name, float score) {
    
}

void delete(TNODE **rootp, char *name) {

}

TNODE *extract_smallest_node(TNODE **rootp) {
  TNODE *p = *rootp, *parent = NULL;
  if (p) {
    while (p->left) {
      parent = p;
      p = p->left;
    }
    
    if (parent == NULL)
      *rootp = p->right;
    else
      parent->left = p->right;
    
    p->left = NULL;
    p->right = NULL;
  }
  
  return p;
}

TNODE *new_node(char *name, float score) {
  TNODE *np = (TNODE *) malloc(sizeof(TNODE));
  if (np) {
    strcpy(np->data.name, name);
    np->data.score = score;
    np->left = NULL;
    np->right = NULL;
  }
  return np;
}

void clean_tree(TNODE **rootp) {
  TNODE *root = *rootp;
  if (root) {
    if (root->left)
      clean_tree(&root->left);
    if (root->right)
      clean_tree(&root->right);
    free(root);
  }
  *rootp = NULL;
}
