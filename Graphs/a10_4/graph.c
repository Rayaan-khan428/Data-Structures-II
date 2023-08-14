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

    for (int i = 0; i < num_vertices; i++) {
      visited[i] = 0;
    }

    // init queue
    QUEUE q = {0};
    enqueue(&q, graph->nodes[start]);
    visited[start] = 1;

    while (q.front) {

      GNODE *cur = (GNODE*) dequeue(&q);

      ADJNODE *neighbours = (ADJNODE*) cur->neighbor;

      while (neighbours) {
        // if the node is not is not in visited
        int neighbours_id = neighbours->nid;
        if (!visited[neighbours_id]) {
          enqueue(&q, graph->nodes[neighbours_id]); // add it to the queue to visit later on
          visited[neighbours_id] = 1; // mark it as visited
        }
      }




    }  

}

void display_dforder(GRAPH *g, int start) {

  if (g == NULL) {
    return;
  }

  int num_vertices = g->order;
  int visited[num_vertices];

  for (int i=0; i<num_vertices; i++) {
    visited[i] = 0;
  }
  
  // init stack
  STACK s = {0};

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