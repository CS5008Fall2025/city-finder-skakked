/**
 * Name: Siddharth Kakked
 * Semester: Fall 2025
 * CS 5008
 * Graph data structure using adjacency list representation
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Edge node in adjacency list represents a connection to another city
typedef struct EdgeNode {
    int dest;              // Index of destination vertex in vertices array
    int weight;            // Distance/cost to reach destination
    struct EdgeNode* next; // Pointer to next edge
} EdgeNode;

// Vertex in the graph - represents a city
typedef struct Vertex {
    char* name;        // City name 
    EdgeNode* edges;   // Linked list of edges to other cities
} Vertex;

// Graph structure - holds all cities and their connections
typedef struct Graph {
    Vertex* vertices;   // Dynamic array of vertices
    int num_vertices;   // Current number of vertices in graph
    int capacity;       // Maximum capacity before reallocation
} Graph;

// Graph operations
Graph* graph_create(int initial_capacity);
void graph_destroy(Graph* graph);
int graph_add_vertex(Graph* graph, const char* name);
int graph_find_vertex(Graph* graph, const char* name);
bool graph_add_edge(Graph* graph, const char* from, const char* to, int weight);
void graph_print_vertices(Graph* graph);

#endif
