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

    // g->nodes is an array og gnodes, allocating memory for them
    g->nodes = malloc(order * sizeof(GNODE*));

    // for each vertex aka gnode in the list
    for (int i = 0; i < order; i++)
    {   
        // allocate memory for a node
        g->nodes[i] = malloc(sizeof(GNODE));

        // set neighbour to null
        g->nodes[i]->neighbor = NULL;

        // node id = i, this is nodes unique identifier
        g->nodes[i]->nid = i;
    }
    
    return g;
}

/**
 * given the graph, as well as the two nodes we want to connect, we make an edge
 * and assign it the weight passed to us
*/
void add_edge(GRAPH *g, int from, int to, int weight) {
    // your implementation

    // to keep track if the edge already exists
    int found = 0;

    // get the neighbour list of the starting vertex
    ADJNODE *p = g->nodes[from]->neighbor;

    // if the list of neighbouring nodes is not empty
    if (p) {

        // then iterate through the neighboring nodes
        while (p->next) {

            // if the node id is equal to the node we want to create an edge to
            if (p->nid == to) {
                found = 1; 
                break; // break out
            }
            p = p->next;
        }

        // this code below runs if no neighbour is found
        
        // checks the last node in the neighbour list;
        if (p->nid == to) {
            found = 1;
        }

        if (found == 1) {
            // if the edge list already exists, update its weight
            p->weight = weight;
        } else {
            // since we cannot find anything, we will create a new AdjNode 
            ADJNODE *n = malloc(sizeof(ADJNODE));
            n->next = NULL;
            n->nid = to;
            n->weight = weight;
            g->nodes[from]->neighbor = n;
        }

        g->size = g->size + 1;

    }

}

void breadthFirstTraversal(GRAPH *graph, int startVertex) {
    // Create a queue to store vertices to visit in breadth-first order
    QUEUE vertexQueue = {0};

    // Variables to keep track of the current vertex and its neighbors
    GNODE *currentVertex = NULL;
    ADJNODE *neighborNode = NULL;

    // Check if the graph is NULL, and if so, return (nothing to display)
    if (graph == NULL) {
        return;
    }

    // Initialize an array to track visited vertices
    int totalVertices = graph->order;
    int visitedVertices[totalVertices];
    for (int i = 0; i < totalVertices; i += 1) {
        visitedVertices[i] = 0;  // Mark all vertices as unvisited
    }

    // Enqueue the starting vertex into the queue
    enqueue(&vertexQueue, graph->nodes[startVertex]);

    // Mark the starting vertex as visited
    visitedVertices[startVertex] = 1;

    // Perform breadth-first traversal using the queue
    while (vertexQueue.front) {
        currentVertex = (GNODE*)dequeue(&vertexQueue);  // Dequeue a vertex from the queue
        printf("%d ", currentVertex->nid);  // Print the current vertex's ID

        // Explore neighbors (adjacent vertices) of the current vertex
        ADJNODE *neighbor = currentVertex->neighbor;

        while (neighbor) {
            if (!visitedVertices[neighbor->nid]) {
                enqueue(&vertexQueue, graph->nodes[neighbor->nid]);  // Enqueue unvisited neighbor
                visitedVertices[neighbor->nid] = 1;  // Mark neighbor as visited
            }
            neighbor = neighbor->next;  // Move to the next neighbor in the linked list
        }
    }

    // Clean up the queue after traversal
    clean_queue(&vertexQueue);
}


void display_dforder(GRAPH *g, int start) {
    
    // your implementation
    STACK stack = {0};

    // variables for iteration through the graph when preforming dft
    GNODE *currentVertex = NULL;
    ADJNODE *neighborNode = NULL;

    // ensure graph isn't empty
    if (g==NULL) {
        return;
    }

    // Initialize an array to track visited vertices
    int totalVertices = g->order;
    int visitedVertices[totalVertices];
    for (int i = 0; i < totalVertices; i += 1) {
        visitedVertices[i] = 0;  // Mark all vertices as unvisited
    }

    // Perform depth-first traversal
    while (stack.top) {

        // pop off the stack and preform dft
        currentVertex = (GNODE*) pop(&stack);
        printf("%d", currentVertex->nid);

        // explore the neighbors of the current vertex
        ADJNODE *neighbor = currentVertex->neighbor;

        // while neighbor isn't empty
        while (neighbor) {
            if (!visitedVertices[neighbor->nid]) {
                push(&stack, g->nodes[neighbor->nid]);
                visitedVertices[neighbor->nid] = 1;
            }
            neighbor = neighbor->next;
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