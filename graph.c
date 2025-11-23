/**
 * Name: Siddharth Kakked
 * Semester: Fall 2025
 * CS 5008
 * Implementation of graph data structure using adjacency list representation
 */
 
#include "graph.h" // Include the corresponding header file
#include <stdio.h> // For printf
#include <stdlib.h> // For malloc, free
#include <string.h> // For strcpy, strcmp

/**
 * Create a new graph
 */
Graph* graph_create(int initial_capacity) {
    // Allocate memory for the graph structure itself
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    
    // Allocate array to hold vertices
    graph->vertices = (Vertex*)malloc(sizeof(Vertex) * initial_capacity);
    graph->num_vertices = 0;  // Start with no vertices
    graph->capacity = initial_capacity;
    
    // Initialize all vertex slots to NULL (empty)
    for (int i = 0; i < initial_capacity; i++) {
        graph->vertices[i].name = NULL;
        graph->vertices[i].edges = NULL;
    }
    
    return graph;
}

/**
 * Free all memory allocated to graph
 */
void graph_destroy(Graph* graph) {
    if (!graph) return;  // Check for NULL pointer
    
    // Free each vertex and its edges
    for (int i = 0; i < graph->num_vertices; i++) {
        // Free the city name string
        free(graph->vertices[i].name);
        
        // Free all edges in the linked list
        EdgeNode* edge = graph->vertices[i].edges;
        while (edge) {
            EdgeNode* temp = edge;  // Save current edge
            edge = edge->next;       // Move to next edge
            free(temp);              // Free the saved edge
        }
    }
    
    // Free the vertices array itself
    free(graph->vertices);
    // Free the graph structure
    free(graph);
}

/**
 * Add a vertex to the graph
 * Returns the index of the vertex
 */
int graph_add_vertex(Graph* graph, const char* name) {
    // Check if vertex already exists - avoid duplicates
    int idx = graph_find_vertex(graph, name);
    if (idx != -1) return idx;  // Return existing index
    
    // Expand capacity if needed (dynamic array growth)
    if (graph->num_vertices >= graph->capacity) {
        graph->capacity *= 2;  // Double the capacity
        graph->vertices = (Vertex*)realloc(graph->vertices, 
                                          sizeof(Vertex) * graph->capacity);
    }
    
    // Add new vertex at the end
    idx = graph->num_vertices;
    
    // Allocate and copy the city name
    graph->vertices[idx].name = (char*)malloc(strlen(name) + 1);  // +1 for null terminator
    strcpy(graph->vertices[idx].name, name);
    
    // Initialize with no edges yet
    graph->vertices[idx].edges = NULL;
    
    // Increment count
    graph->num_vertices++;
    
    return idx;
}

/**
 * Find vertex by name
 * Returns index or -1 if not found
 */
int graph_find_vertex(Graph* graph, const char* name) {
    // Linear search through all vertices
    for (int i = 0; i < graph->num_vertices; i++) {
        if (strcmp(graph->vertices[i].name, name) == 0) {
            return i;  // Found - return index
        }
    }
    return -1;  // Not found
}

/**
 * Add an edge between two vertices (undirected)
 */
bool graph_add_edge(Graph* graph, const char* from, const char* to, int weight) {
    // Find indices of both cities
    int from_idx = graph_find_vertex(graph, from);
    int to_idx = graph_find_vertex(graph, to);
    
    // Both cities must exist in the graph
    if (from_idx == -1 || to_idx == -1) return false;
    
    // Add edge from -> to
    // Create new edge node
    EdgeNode* new_edge = (EdgeNode*)malloc(sizeof(EdgeNode));
    new_edge->dest = to_idx;      // Where this edge goes
    new_edge->weight = weight;    // Distance/cost
    new_edge->next = graph->vertices[from_idx].edges;  // Insert at head of list
    graph->vertices[from_idx].edges = new_edge;        // Update head pointer
    
    // Add edge to -> from (undirected graph = bidirectional edges)
    new_edge = (EdgeNode*)malloc(sizeof(EdgeNode));
    new_edge->dest = from_idx;    // Reverse direction
    new_edge->weight = weight;    // Same distance
    new_edge->next = graph->vertices[to_idx].edges;    // Insert at head
    graph->vertices[to_idx].edges = new_edge;          // Update head pointer
    
    return true;
}

/**
 * Print all vertices in the graph
 */

 void graph_print_vertices(Graph* graph) {
    for (int i = 0; i < graph->num_vertices; i++) {
        printf("%s\n", graph->vertices[i].name);
    }
}
