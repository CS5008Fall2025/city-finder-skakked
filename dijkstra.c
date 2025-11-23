/**
 * Name: Siddharth Kakked
 * Semester: Fall 2025
 * CS 5008
 * Dijkstra's algorithm implementation 
 */

#include "dijkstra.h" // Include the header file
#include <stdlib.h> 
#include <limits.h>
#include <stdbool.h>

#define INFINITY_DIST INT_MAX // Define infinity as maximum integer value

/**
 * Find vertex with minimum distance that hasn't been visited
 * This is the key selection step in Dijkstra's algorithm
 */
static int min_distance(int* dist, bool* visited, int n) {
    int min = INFINITY_DIST;  // Start with infinity
    int min_idx = -1;          // -1 means no valid vertex found
    
    // Check all vertices
    for (int i = 0; i < n; i++) {
        // Consider only unvisited vertices with finite distance
        if (!visited[i] && dist[i] < min) {
            min = dist[i];      // Update minimum distance
            min_idx = i;        // Update minimum index
        }
    }
    
    return min_idx;  // Return vertex with smallest distance
}

/**
 * Reconstruct path from start to end using parent array
 * Parent array stores which vertex we came from to reach each vertex
 */
static int* reconstruct_path(int* parent, int start, int end, int* length) {
    // Count path length by following parent pointers backwards
    int count = 0;
    int current = end;
    while (current != -1) {  // -1 means we've reached the start (no parent)
        count++;
        current = parent[current];  // Move to parent
    }
    
    // Allocate array to hold the path
    int* path = (int*)malloc(sizeof(int) * count);
    *length = count;  // Return length to caller
    
    // Fill path in reverse order (from end to start)
    current = end;
    for (int i = count - 1; i >= 0; i--) {
        path[i] = current;          // Store current vertex
        current = parent[current];   // Move to parent
    }
    
    return path;  // Path is now in correct order: start -> ... -> end
}
