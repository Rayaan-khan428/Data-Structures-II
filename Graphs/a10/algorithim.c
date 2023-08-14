#include <stdio.h>
#include <stdlib.h> 
#include "heap.h"
#include "algorithm.h"

EDGELIST *mst_prim(GRAPH *g, int start) {
    // your implementation

    // ensure input graph is not empty
    if (g == NULL) {
        return NULL;
    }

    int index;
    int n = g->order;
    int T[n]; 
    int parent[n];
    
    for (int i=0; i<n; i+=1) {
        T[i] = 0; // mark all verticies as not in our MST
    }

    for (int i=0; i<n; i+= 1) {
        parent[i] = -1; // initialize parent array w -1 to indicate no parent
    }

}

EDGELIST *spt_dijkstra(GRAPH *g, int start) {
    // your implementation
}

EDGELIST *sp_dijkstra(GRAPH *g, int start, int end) {
    // your implementation
}