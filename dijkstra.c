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

