#include <stdio.h>
#include <stdlib.h>
#include "queue_stack.h" 
#include "graph.h"

/**
 * order: number of verticies
*/
GRAPH *new_graph(int order) {
    
    // your implementation

    // allocate mem for new graph
    GRAPH *g = malloc(sizeof(GRAPH));

    // define props
    g->order = order;
    g->size = 0;

    g->nodes = malloc(order * sizeof(GNODE*));

    for (int i=0; i<order; i++) {

      // allocate mem for a node
      g->nodes[i] = malloc(sizeof(GNODE));

      // set neighbor to null
      g->nodes[i]->neighbor = NULL;
      g->nodes[i]->nid = i;

    }
    

}

/**
 * given the graph, as well as the two nodes we want to connect, we make an edge
 * and assign it the weight passed to us
*/
void add_edge(GRAPH *g, int from, int to, int weight) {
   
    // your implementation
    int found = 0;

    // the graph nodes contains a list called neighbor
    // that contains a linkedlist containing adjnodes
    ADJNODE *p = g->nodes[from]->neighbor;

    // if p is not null
    if (p) {

      // while p is pointing to another pointer (aka more than one neighbour)
      while (p->next) {

        // check if the adjnode identifier is equal to the identifier of the node we want to add an edge to
        if (p->nid == to) {
          found = 1; // that means we found where we want the edge
          break;
        }
        // iterate to the next neighbor in the linked list
        p = p->next;

      }
    }

    // in case while loop finishes we have to still check the last node
    if (p->nid == to) {
      found = 1;
    }

    if (found == 1) {
      p->weight = weight;
    } else {

      // as we didn't find anything, we will create a new AdjNOde
      ADJNODE *n = malloc(sizeof(ADJNODE));
      n->next = NULL;
      n->nid = to;
      n->weight = weight;
      g->nodes[from]->neighbor = n;

    }

    g->size = g->size+1;

}

void breadthFirstTraversal(GRAPH *graph, int startVertex) {
    
    // queue
    QUEUE vertexQueue = {0};

    // variables to keep track of the current vertex and its neighbors
    GNODE *currentVertex = NULL;
    ADJNODE *neighborNode = NULL;

    // check if the graph is NULL, and if so return nothign
    if (graph == NULL) {
      return;
    }

    // total number of nodes in the graph
    int totalVerticies = graph->order;
    int visitedVertices[totalVerticies]; // initialize a static array
    
    // for each index set it equal to null, mark it as unvisited
    for(int i=0; i<totalVerticies; i+=1) {
      visitedVertices[i] = 0;
    }

    // Enqueue the starting vertex into the queue
    enqueue(&vertexQueue, graph->nodes[startVertex]);

    // Mark it as visited
    visitedVertices[startVertex] = 1;

    while (vertexQueue.front) {
      currentVertex = (GNODE*)dequeue(&vertexQueue);
      printf("%d",currentVertex->nid);

      // now we explore its neighbors we set our node equal to the neighbor
      neighborNode = currentVertex->neighbor;

      // while its neighbors are not null
      while(neighborNode) {
        
        // if the neighboring node is not in our listed of visited nodes
        if (!visitedVertices[neighborNode->nid]) {
          enqueue(&vertexQueue, graph->nodes[neighborNode->nid]); // enqueue unvisited neighbor
          visitedVertices[neighborNode->nid] = 1;
        }
        neighborNode = neighborNode->next;

      }


    }

}

void display_dforder(GRAPH *g, int start) {
    
    // your implementation
    STACK s = {0};

    // for iterating
    GNODE *currentVertex = NULL;
    ADJNODE *neighboringVerticies = NULL;

    if (g==NULL) {
      return;
    }

    // inititalize an array to the size of how many vertices there is
    int totalVertices = g->order;
    int visitedVertices[totalVertices]; 
    for (int i=0; i<totalVertices; i++) {
      visitedVertices[i] = 0;
    }

    // push onto stack the first node
    push(&s, g->nodes[start]);

    while (stack.top) {

      currentVertex = (GNODE*) pop(&s);
      printf("%d", currentVertex->nid);

      neighboringVerticies = currentVertex->neighbor;

      while (neighboringVerticies != NULL) {

        if (!visited[neighboringVerticies->nid]) {
          push(&stack, g->nodes[neighboringVerticies->nid]);
          visited[neighboringVerticies->nid] = 1; // mark as visited
        }

        neighboringVerticies = neighboringVerticies->next;

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