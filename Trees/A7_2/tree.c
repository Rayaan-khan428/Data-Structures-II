/*
 * your program signature
 */ 
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "queue_stack.h"
#include "tree.h"

TNODE *new_node(int value) {
  TNODE *np = (TNODE *) malloc(sizeof(TNODE));
  if (np != NULL) {
    np->data = value;
    np->left = NULL;
    np->right = NULL;
  }
  return np;
}

/* This function computes and returns a structure TPROPS containing the number of nodes and height
 * of the tree passed by root address.
 */
TPROPS get_props(TNODE *root) {
    
    // Create a TPROPS structure to store the height and order (number of nodes) of the tree.
    TPROPS props = {0};

    // If the root is NULL (empty tree), return the initialized props structure.
    if (!root) {
        return props;
    }

    // Recursively compute the properties of the left subtree.
    TPROPS left_props = get_props(root->left);
    
    // Recursively compute the properties of the right subtree.
    TPROPS right_props = get_props(root->right);

    // Calculate the height of the current subtree by taking the maximum height of its left and right subtrees,
    // and adding 1 for the current node.
    props.height = 1 + (left_props.height > right_props.height ? left_props.height : right_props.height);
    
    // Calculate the total number of nodes in the current subtree by adding the number of nodes in its left
    // and right subtrees, and adding 1 for the current node.
    props.order = 1 + left_props.order + right_props.order;

    // Return the computed properties for the current subtree.
    return props;
}


/* this displays the node data of the tree in pre-order. */
void display_preorder(TNODE *root) {

  if (root) {

    // root -> left child -> right child
    printf("%c ", root->data);
    display_preorder(root->left);
    display_preorder(root->right);

  }

}

/* this displays the node data of the tree in in-order. */
void display_inorder(TNODE *root) {

  if (root == NULL) {
    return;
  } else {

    display_inorder(root->left);
    printf("%c ", root->data);
    display_inorder(root->right);

  }

}

/* this displays the node data of the tree in post-order. */
void display_postorder(TNODE *root) {

  if (root) {
    display_preorder(root->left);
    display_preorder(root->right);
    printf("%c ", root->data);
  }

}

/* this displays the tree in breadth-first-order using an auxiliary queue. */ 
/* use auxiliary queue data structure for the algorithm  */
void display_bforder(TNODE *root) {

  // only iterative  
  // edge case 1
  if (!root) {
    return;
  }

  else {

    QUEUE q = {0}; // initialize a q
    enqueue(&q, root); //add root to the queue

    // while the queue is not empty
    while (q.front) {

      TNODE *cur = (TNODE*) dequeue(&q); // dequeue whatever is in the queue
      
      // add its children to the queue
      enqueue(&q, cur->left); 
      enqueue(&q, cur->right);

      // print the current root
      printf("%c ",cur->data);

    }

  }

}

/* this does the breadth-first-search using an auxiliary queue. */
/* use auxiliary queue data structure for the algorithm  */
TNODE *iterative_bfs(TNODE *root, int val) {

  QUEUE q = {0}; // initialize a q
  enqueue(&q, root); //add root to the queue

  while (q.front) {

    TNODE *node = (TNODE*) dequeue(&q);
    
    enqueue(&q, node->left);
    enqueue(&q, node->right); 

    if (node->data == val) {
      return node;
    } 

  }
  return NULL;
}

/* this does the depth-first-search using an auxiliary stack */
TNODE *iterative_dfs(TNODE *root, int val) {

  // utilize a LIFO system
  STACK s = {0};
  push(&s, root);

  // while stack has something inside
  while(s.top) {

    // get the node at top of stack
    TNODE *node = (TNODE*) pop(&s); 

    // add nodes children to the stack
    push(&s, node->left);
    push(&s, node->right);

    if (node->data == val) {
      return node;
    }

  }
  return NULL;

  // Recursive method below
}

// the following functions are given, need to add to your program.
void clean_tree(TNODE **rootp) {
  TNODE *p = *rootp;
  if (p) {
    if (p->left)
      clean_tree(&p->left);
    if (p->right)
      clean_tree(&p->right);
    free(p);
  }
  *rootp = NULL;
}

void insert_complete(TNODE **rootp, int val){
  if( *rootp == NULL) { 
    *rootp = new_node(val);
  } else {
    QUEUE queue = {0};
    TNODE *p;
    enqueue(&queue, *rootp);
    while(queue.front){
      p = dequeue(&queue);
      if(p->left == NULL){
        p->left = new_node(val);
        break;
      } else {
        enqueue(&queue, p->left);
      }
      
      if(p->right == NULL){
        p->right = new_node(val);
        break;
      } else  {
        enqueue(&queue, p->right);
      }
    }
  }
}