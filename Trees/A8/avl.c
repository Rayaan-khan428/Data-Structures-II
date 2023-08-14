#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[100];
    float score;
} DATA;

typedef struct TNODE {
    DATA data;
    int height;
    struct TNODE *left;
    struct TNODE *right;
} TNODE;

TNODE *extract_smallest_node(TNODE **rootp);
int max(int a, int b);

int height(TNODE *np) {
    if (np == NULL) {
        return -1;
    }
    
    int left_height = height(np->left);
    int right_height = height(np->right);
    
    return 1 + (left_height > right_height ? left_height : right_height);
}

int balance_factor(TNODE* node) {
    if (node == NULL) {
        return 0;
    }
    
    int left_subtree_height = height(node->left);
    int right_subtree_height = height(node->right);
    
    return left_subtree_height - right_subtree_height;
}

int is_avl(TNODE *root) {
    if (root == NULL) {
        return 1;
    }
    int bf = balance_factor(root);
    if (abs(bf) >= 2 || is_avl(root->left) == 0 || is_avl(root->right) == 0) {
        return 0;
    }
    return 1;
}

TNODE *rotate_right(TNODE *y) {
    TNODE *x = y->left;
    TNODE *temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x; // New root of the rotated subtree
}

TNODE *rotate_left(TNODE *x) {
    TNODE *y = x->right;
    TNODE *temp = y->left;

    y->left = x;
    x->right = temp;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y; // New root of the rotated subtree
}

// Other functions (insert, delete, etc.) need to be completed.

int max(int a, int b) {
    return (a > b) ? a : b;
}

TNODE *extract_smallest_node(TNODE **rootp) {
  TNODE *tnp = *rootp;
  TNODE *parent = NULL;
  if (tnp == NULL) {
    return NULL;
  } else {
    while (tnp->left) {
      parent = tnp;
      tnp = tnp->left;
    }
    if (parent == NULL)
      *rootp = tnp->right;
    else
      parent->left = tnp->right;
    tnp->left = NULL;
    tnp->right = NULL;
    return tnp;
  }
}

// the following functions are from A7
TNODE *search(TNODE *root, char *name) {
  TNODE *tp = root;
  while (tp) {
    if (strcmp(name, tp->data.name) == 0) {
       return tp;
    } else if (strcmp(name, tp->data.name) < 0) 
      tp = tp->left;
     else 
      tp = tp->right;
  }    
  return NULL;
}

void clean_tree(TNODE **rootp) {
  if (*rootp) {
    TNODE *np = *rootp;
    if (np->left)
      clean_tree(&np->left);
    if (np->right)
      clean_tree(&np->right);
    free(np);
  }
  *rootp = NULL; ;
}
