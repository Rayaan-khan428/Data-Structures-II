#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"


TNODE *search(TNODE *root, char *name) {
    
    // your implementation | Binary Search Option, recursive

    // recursive method
    // check if the root is a match
    if (strcmp(root->data.name,name) == 0) { 
      return root;
    } 

    else if (strcmp(root->data.name,name) < 0) {
      return search(root->left, name);
    } else {
      return search(root->right, name);
    }

}

void insert(TNODE **rootp, char *name, float score) {

  // create new node with the data given
  TNODE *node = new_node(name, score);

  // if root is empty, set the node equal to root and return
  if (!*rootp) {
    *rootp = node;
    return;
  }

  TNODE *cur = *rootp;

  // while current is not null
  while (cur) {

    if (strcmp(name, cur->data.name) < 0) {
      cur = cur->left;
    }

    else if (strcmp(name, cur->data.name) > 0) {
      cur = cur->right;
    }

    else {
      // update the current score
      cur->data.score = score;
      return;
    }
  }
}

void delete(TNODE **rootp, char *name) {
    
    // nothing to delete
    if (!*rootp) {
      return;
    }

    // keep track of the parent and cur node
    TNODE *parent = NULL;
    TNODE *cur = *rootp;

    while (cur) {

      // if name is larger, move right sub-tree
      if (strcmp(name, cur->data.name) > 0) {
        parent = cur;
        cur = cur->right;
        continue;
      }

      // if name is smaller, move left sub-tree
      else if(strcmp(name, cur->data.name) < 0) {
        parent = cur;
        cur = cur->left;
        continue;        
      }

      // match found
      else {

        // scenario 1: No Children
        if (cur->left == NULL && cur->right == NULL) {

          // no children and no parent (means the root node is the one we want to delete)
          if(!parent) {
            *rootp = NULL;
          }

          // has parent but no children
          else {
            
            if (parent->left = cur) {
              parent->left = NULL;
            } else {
              parent->right = NULL;
            }
            free(cur);
          }
        }

        // scenario 2: One Child Found
        else if ((cur->left) != (cur->right)) {

          // determine the child node
          TNODE *child;
          if (cur->left = NULL) {
            child = cur->right;
          } else {
            child = cur->left;
          }

          // if cur has no parent, and only one child means it is the root
          if (!parent) {
            *rootp = child;
          } 
          
          // has a parent and one child
          else {

            if (parent->left = cur) {
              parent->left = child;
            } else {
              parent->right = child;
            }
            free(cur);

          }

        }

        // situation 3: has two children
        else {

          TNODE *sucessorParent = cur;
          TNODE *sucessorChild = cur->right;

          TNODE *smallestNode = extract_smallest_node(cur);

          

        }

      }
    }
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
