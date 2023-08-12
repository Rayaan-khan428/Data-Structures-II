#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <graph_adj_mat.h>

struct mygraph {
    int numNodes;
    bool **edges; // array
};

graph *create_graph(int numNodes) {
    
    // allocate memory for a graph
    graph *g = malloc(sizeof(*g));
    if (g == NULL) {
        return NULL;
    }
    g->numNodes = numNodes;
    
    // allocate our matrix
    g->edges = calloc(sizeof(bool*), g->numNodes);

    // cleanup
    if (g->edges == NULL) {
        free(g);
        return NULL;
    }

    for (int i = 0; i < g->numNodes; i++)
    {
        g->edges[i] = calloc(sizeof(bool), g->numNodes);
        if (g->edges[i] == NULL) {
            // cleanup again
            destroy_graph(g);
            return NULL;
        }
    }
    return g;
}

void destroy_graph(graph *g) {
    
}

void print_graph(graph *g) {

}

bool add_edge(graph *g, unsigned int from_node, unsigned int to_node) {

}

bool has_edge(graph *g, unsigned int from_node, unsigned int to_node) {

}