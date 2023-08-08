/*
 * your program signature
 */ 
 
#include <stdio.h>
#include <stdlib.h>
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
    props.height = 1 + max(left_props.height, right_props.height);
    
    // Calculate the total number of nodes in the current subtree by adding the number of nodes in its left
    // and right subtrees, and adding 1 for the current node.
    props.order = 1 + left_props.order + right_props.order;

    // Return the computed properties for the current subtree.
    return props;
}


/* this displays the node data of the tree in pre-order. */
void display_preorder(TNODE *root) {
    
    // your implementation
    if (root) {
      printf("%d", root->data);
      display_preorder(root->left);
      display_postorder(root->right);
    }

}

/* this displays the node data of the tree in in-order. */
void display_inorder(TNODE *root) {

    // your implementation
    if (root) {

      display_inorder(root->left);
      printf("%d", root->data);
      display_inorder(root->right);

    }

}

/* this displays the node data of the tree in post-order. */
void display_postorder(TNODE *root) {

    // your implementation
    if (root) {

      display_postorder(root->left);
      display_postorder(root->right);
      printf("%d", root->data);

    }

}

/* this displays the tree in breadth-first-order using an auxiliary queue. */ 
/* use auxiliary queue data structure for the algorithm  */
void display_bforder(TNODE *root) {

    // your implementation
    QUEUE q = {0};

    // step 1: Add the original node to the queue
    enqueue(&q, root);

    // while there is 1 item in the queue
    while (q.front) {
      // Create a new node with the node you just dequeued from the queue
      TNODE *node = (TNODE *) dequeue(&q);

      // Add the left and right children of the node to the queue
      enqueue(&q, node->left);
      enqueue(&q, node->right);

      // print the data
      pritf("%c ", node->data);

    }

}

/* this does the breadth-first-search using an auxiliary queue. */
/* use auxiliary queue data structure for the algorithm  */
TNODE *iterative_bfs(TNODE *root, int val) {
    
    // your implementation

    QUEUE q =  {0}; // initialize an empty queue obj
    enqueue(&q, root);

    while (q.front) { // while there is more than one item
      
      
      TNODE *node = (TNODE *) dequeue(&q); // dequeue and store in node
      enqueue(&q, node->left); // queue left child
      enqueue(&q, node->right); // queue right child

      // if match then return the node, if not, loop again
      if (node->data == val) {
        return node;
      }

    }

}

/* this does the depth-first-search using an auxiliary stack */
TNODE *iterative_dfs(TNODE *root, int val) {

  // your implementation
  STACK s = {0};

  // add the root
  push(&s, root);

  // as long as stack isn't empty
  while (s.top) {
    TNODE *node = (TNODE *) pop(&s); // pop top item of off stack
    push(&s, node->left);
    push(&s, node->right);
    if (node->data == val) {
      return node;
    }
  }
  return NULL;
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