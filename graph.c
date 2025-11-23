/**
 * Name: Siddharth Kakked
 * Semester: Fall 2025
 * CS 5008\
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
 * Free all memory associated with graph
 */
void graph_destroy(Graph* graph) {
    if (!graph) return;  // Safety check for NULL pointer
    
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