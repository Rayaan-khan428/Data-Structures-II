#include <stdio.h>
#include <stdlib.h> 
#include "heap.h"
#include "algorithm.h"

EDGELIST *mst_prim(GRAPH *graph, int start_vertex) {
    
    // your implementation
    if (graph == NULL) {
        return NULL;
    }

    int vertex_count = graph->order; 
    int vertex_indices[vertex_count]; // keep track of vertex inclusion in MST
    int parent[vertex_count]; // store parent of each vertex in the MST

    for (int i=0; i<vertex_count; i++) {
        vertex_indices[i] = 0;
        parent[i] = -1;
    }

    HNODE heap_node;
    HEAP *heap = new_heap(4);
    ADJNODE *neighbor = graph->nodes[start_vertex]->neighbor;

    vertex_indices[start_vertex] = 1; // mark the startin vertex as included

    while(neighbor) {
        heap_node.key = neighbor->weight;
        heap_node.data = neighbor->nid;

        // insert the neighbor node into the heap along with its weight as the key
    }
    

}

EDGELIST *spt_dijkstra(GRAPH *g, int start) {
    // your implementation
}

EDGELIST *sp_dijkstra(GRAPH *g, int start, int end) {
    // your implementation
}