#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"


TNODE *search(TNODE *root, char *name) {
    // your implementation

    // if the root is match or a null return it
    if (root == NULL || strcmp(root->data.name, name) == 0) {
        return root;
    }

    if (strcmp(root->data.name, name) > 0) {
        return search(root->right, name);
    } else {
        return search(root->left, name);
    }

    // ---------------- Iterative approach Below ---------------- //


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

    if (!*rootp) {
        return; // If the root pointer is empty, there is no tree to delete from, so return.
    }     

    TNODE *parent = NULL;
    TNODE *current = *rootp;

    while (current) {

        if (strcmp(current->data.name, name) < 0) {
            parent = current;
            current = current->right;
        } else if (strcmp(current->data.name, name) > 0) {
            parent = current;
            current = current->left;
        } else {
            // Node to be deleted found
            break;
        }
        
    }

    if (!current) {
        return; // Node with given name not found
    }

    if (current->left == NULL && current->right == NULL) {
        if (!parent) {
            *rootp = NULL;
        } else {
            if (parent->left == current) { 
                parent->left = NULL;
            } else {
                parent->right = NULL;
            }
        }
        free(current);
        current = NULL; // Prevent dangling pointer
    } 
    
    else if ((current->left) != (current->right)) {
        TNODE *child;
        if (current->left == NULL) {
            child = current->right;
        } else {
            child = current->left;
        }
        if (!parent) {
            *rootp = child;
        } else {
            if (parent->left == current) {
                parent->left = child;
            } else {
                parent->right = child;
            }
        }
        free(current);
        current = NULL; // Prevent dangling pointer
    } 
    
    else {
        TNODE *minNode = extract_smallest_node(&(current->right));

        // If the left child is the minimum of the two 
        if (current->right == minNode) {
            minNode->left = current->left;
            minNode->right = current->right;
        } 
        
        // If the right child is the min of the two
        else {
            minNode->left = current->left;
            minNode->right = current->right;
        }

        if (!parent) {
            *rootp = minNode;
        } else {
            if (parent->left == current) {
                parent->left = minNode;
            } else {
                parent->right = minNode;
            }
        }
        free(current);
        current = NULL; // Prevent dangling pointer
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
