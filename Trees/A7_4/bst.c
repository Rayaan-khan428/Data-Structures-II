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
    
    TNODE *node = new_node(name, score); // Create a new node with the given name and score

    if (!*rootp) { // If the root pointer is empty, i.e., the tree is empty
        *rootp = node; // Set the root pointer to the new node
        return; // Exit the function
    }

    TNODE *current = *rootp; // Start from the root of the tree

    while (current) { // Traverse the tree until a suitable position is found
        
        // if name is alphabetically less than node move to left subtree
        if (strcmp(name, current->data.name) < 0) { 
            
            // if current does not contain a left child, insert new node here
            if (!current->left) { 
                current->left = node; 
                return; // Exit the function
            }
            current = current->left; // Move to the left child
        } 
        
        // if name is alphabetically less than node move to left subtree
        else if (strcmp(name, current->data.name) > 0) { // If the name is greater than the current node's name
            
            // if current does not contain a right child, insert new node here
            if (!current->right) { 
                current->right = node; // Set the right child to the new node
                return; // Exit the function
            }
            current = current->right; // Move to the right child
        } 
        
        
        else { // If the names are equal
            current->data.score = score; // Update the score of the current node
            return; // Exit the function
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

      // if name is larger. move to right sub-tree
      if (strcmp(name, cur->data.name) > 0) {
        parent = cur;
        cur = cur->right;
        continue;
      }

      // if name is smaller. move to left sub-tree
      else if (strcmp(name, cur->data.name) < 0) { 
        parent = cur;
        cur = cur->left;
        continue;
      }

      // match found
      else {

        // scenario 1: match has no children
        if (cur->left == NULL && cur->right == NULL) {
          
          // if no parent (means tree only has one node)
          if (!parent) {
            *rootp = NULL;
          }

          // has parents but no children
          else {

            if (parent->left == cur) {
              parent->left = NULL;
            } else {
              parent->right = NULL;
            }
          }

        // scenario 2: match has one child
        } else if ((cur->left) != (cur->right)) {

          // determine the child node
          TNODE *child;
          if (cur->left == NULL) {
            child = cur->right;
          } else {
            child = cur->left;
          }

          // if it has no parent
          if (!parent) {
            *rootp = child;
          }

          // has a parent and one child
          else {

            if (parent->left == cur) {
              parent->left = child;
            } else {
              parent->right = child;
            }
            free(cur);
          }

        }

        // scenario 3: has two children
        TNODE *minNode = extract_smallest_node(&cur);

        // if the left child is the minimum of the two
        if (cur->right == minNode) {
          minNode->left = cur->left;
          minNode->right = cur->right;
        }

        // if the right hcild is the minimum of thw two
        else {
          minNode->left = cur->left;
          minNode->right = cur->right;
        }

        // no parent
        if (!parent) {
          *rootp = minNode;
        } else {
            if (parent->left == cur) {
                parent->left = minNode;
            } else {
                parent->right = minNode;
            }
        }
        free(cur);
        cur = NULL; // Prevent dangling pointer


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
