#include <stdio.h>
#include <stdlib.h>
#include "queue_stack.h" 
#include "graph.h"

/**
 * order: number of verticies
*/
GRAPH *new_graph(int order) {
    
    

}

/**
 * given the graph, as well as the two nodes we want to connect, we make an edge
 * and assign it the weight passed to us
*/
void add_edge(GRAPH *g, int from, int to, int weight) {
   
}

void breadthFirstTraversal(GRAPH *graph, int start) {
    
    if (graph == NULL) {
      return;
    }

    int num_vertices = graph->order;
    int visited[num_vertices];

    // mark each element as 0 so it is processed as unvisited
    for (int i=0; i < num_vertices; i++) {
      visited[i] = 0;
    }

    // initialize our QUEUE
    QUEUE q = {0};
    enqueue(&q, graph->nodes[start]);
    visited[start] = 1;

    while (q.front) {

      // create a graph node and store the dequeued node in it
      GNODE *cur_vertex = (GNODE*)dequeue(&q);
      printf("%d ", cur_vertex->nid);

      // create an adj node now and store the adj nodes of the cur vertex in it
      ADJNODE *neighbors = cur_vertex->neighbor;

      // while we have neighbors
      while (neighbors) {

        // store the id
        int neighbor_id = neighbors->nid;

        // if that node has not been visited (aka not in our visited list)
        if (!visited[neighbor_id]) {
          enqueue(&q, graph->nodes[neighbor_id]); //  add it to the queue to visit later on
          visited[neighbor_id] = 1; // mark it as visited
        }

        // after the if, we simply move to the next neighbour
        neighbors = neighbors->next;
      }

    }

}

void display_dforder(GRAPH *g, int start) {

  // edge case
  if (g == NULL) {
    return;
  }

  // variables to store the cur vertex and its neighbors
  GNODE *cur_vertex = NULL;
  ADJNODE *cur_neighbor = NULL;

  // grab the number of verticies and initialize a list to it
  int num_vertices = g->order;
  int visited[num_vertices];

  // mark all the verticies as unvisited
  for (int i=0; i < num_vertices; i++) {
    visited[i] = 0;
  }

  // initialize an empty stack
  STACK s = {0};
  push(&s, g->nodes[start]);
  visited[start] = 1;

  // while the stack has an element
  while (s.top) {

    // create a node by popping off the element from the stack
    cur_vertex = (GNODE*)pop(&s);
    printf("%d ", cur_vertex->nid);

    // Explore the neighbors of the cur vertex
    cur_neighbor = cur_vertex->neighbor;

    while (cur_neighbor) {

      int neighbor_id = cur_neighbor->nid;

      // if the neighbour has not been visited
      // then push it to our stack
      if (!visited[neighbor_id]) {
        push(&s, g->nodes[neighbor_id]); // add it to s
        visited[neighbor_id] = 1; // mark it as visited
      }

      // after the if we simply move to the next neighbor
      cur_neighbor = cur_neighbor->next;

    }

  }

}

int get_weight(GRAPH *g, int from, int to) {
  ADJNODE *p = g->nodes[from]->neighbor;
  int result = INFINITY;
  while (p) {
    if (p->nid == to) {
        result = p->weight;
        break;
    }
    p = p->next;
  }
  return result;
}

void clean_graph(GRAPH **gp) {
  int i;
  GRAPH *g = *gp;
  ADJNODE *temp, *ptr;
  for (i = 0; i < g->order; i++) {
    ptr = g->nodes[i]->neighbor;
    while (ptr != NULL) {
      temp = ptr;
      ptr = ptr->next;
      free(temp);
    }
    free(g->nodes[i]);
  }
  free(g->nodes);
  free(g);
  *gp = NULL;
}

void display_graph(GRAPH *g) {
  if (g == NULL) return;
  printf("order:%d\n", g->order);
  printf("size:%d\n", g->size);
  printf("from:(to weight)");
  int i;
  ADJNODE *ptr;
  for (i = 0; i < g->order; i++) {
    printf("\n%d:", g->nodes[i]->nid);
    ptr = g->nodes[i]->neighbor;
    while (ptr != NULL) {
      printf("(%d %d) ", ptr->nid, ptr->weight);
      ptr = ptr->next;
    }
  }
}