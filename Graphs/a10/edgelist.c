#include <stdio.h>
#include <stdlib.h> 
#include "edgelist.h"

EDGELIST *new_edgelist() {
  // your implementation

  // allocate memory
  EDGELIST *p = malloc(sizeof(EDGELIST));

  // initialize start and end pointers
  p->start = NULL;
  p->end = NULL;

  // init size is 0 (aka no edges)
  p->size = 0;

  return p;

}

void add_edge_end(EDGELIST *g, int from, int to, int weight) {
    // your implementation

    // allocate memory for a new edge
    EDGE *e = malloc(sizeof(EDGE));

    // set props
    e->to = to;
    e->from = from;
    e->weight = weight;
    e->next = NULL;

    // if our list of edges isn't empty
    if (g->end) { // because an empty list would have an end of null
      g->end->next = e;
    }

    // edgelist was empty so we add to the start, 
    else {
      g->start = e;
    }

    // update props of edge list
    g->end = e;
    g->size += 1;
}

void add_edge_start(EDGELIST *g, int from, int to, int weight) {
    
    // your implementation
    EDGE *e = malloc(sizeof(EDGE));

    // set props
    e->to = to;
    e->from = from;
    e->weight = weight;
    e->next = g->start; // inserting at start so point to cur start

    // if edgelist empty
    if (!g->start) {
      g->end = e;
    }

    // update the start of the edgelist
    g->start = e;

    // inc size
    g->size += 1;

}

int weight_edgelist(EDGELIST *g) {
    
    // your implementation
    int weight = 0;

    // create pointer to current start of edgelist
    EDGE *p = g->start;

    // iterate through edgelist
    // each iteration we grab the weight of the edge and add it to weight
    // move to next pointer
    while (p) {
      weight += p->weight;
      p = p->next;
    }
}

void clean_edgelist(EDGELIST **gp) {
  EDGELIST *g = *gp;
  EDGE *temp, *p = g->start;
  while (p) {
    temp = p;
    p = p->next;
    free(temp);
  }
  free(g);
  *gp = NULL;
}

void display_edgelist(EDGELIST *g) {
  if (g == NULL) return;
  printf("size:%d\n", g->size);
  printf("(from to weight):");
  EDGE *p = g->start;
  while (p) {
    printf("(%d %d %d) ", p->from, p->to, p->weight);
    p = p->next;
  }
}