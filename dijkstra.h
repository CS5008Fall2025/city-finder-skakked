/**
 * Name: Siddharth Kakked
 * Semester: Fall 2025
 * CS 5008
 * Dijkstra's algorithm header file
 */

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h" // Include the graph data structure
#include <stdbool.h> // For bool type
#include <limits.h> // For INT_MAX

// Result structure for shortest path
typedef struct PathResult {
    int* path;           // Array of vertex indices from start to end
    int path_length;     // Number of vertices in path
    int total_distance;  // Sum of all edge weights in path
    bool found;          // True if path exists, false otherwise
} PathResult;

// Find shortest path between two vertices
PathResult dijkstra_shortest_path(Graph* graph, int start, int end);

// Free path result
void path_result_destroy(PathResult* result);

#endif

