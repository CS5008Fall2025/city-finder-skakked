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

/**
 * Dijkstra's shortest path algorithm
 * Finds shortest path from start vertex to end vertex
 */
PathResult dijkstra_shortest_path(Graph* graph, int start, int end) {
    // Initialize result structure
    PathResult result;
    result.path = NULL;
    result.path_length = 0;
    result.total_distance = 0;
    result.found = false;
    
    int n = graph->num_vertices;
    
    // Initialize arrays for algorithm
    int* dist = (int*)malloc(sizeof(int) * n);       // Distance from start to each vertex
    bool* visited = (bool*)malloc(sizeof(bool) * n); // Whether vertex has been processed
    int* parent = (int*)malloc(sizeof(int) * n);     // Track path: parent[v] = vertex before v
    
    // Set initial values
    for (int i = 0; i < n; i++) {
        dist[i] = INFINITY_DIST;  // All vertices start with infinite distance
        visited[i] = false;        // No vertices visited yet
        parent[i] = -1;            // No parent initially
    }
    
    dist[start] = 0;  // Distance from start to itself is 0
    
    // Main algorithm loop - process each vertex
    for (int count = 0; count < n - 1; count++) {
        // Find unvisited vertex with minimum distance
        int u = min_distance(dist, visited, n);
        
        // If no vertex found or all remaining have infinite distance, stop
        if (u == -1 || dist[u] == INFINITY_DIST) break;
        
        // Mark this vertex as processed
        visited[u] = true;
        
        // Early exit optimization: if we reached destination, we're done
        if (u == end) break;
        
        // Update distances for all adjacent vertices
        EdgeNode* edge = graph->vertices[u].edges;  // Get adjacency list
        while (edge) {
            int v = edge->dest;  // Neighbor vertex
            
            // Only update unvisited vertices with finite distance
            if (!visited[v] && dist[u] != INFINITY_DIST) {
                // Calculate distance through this path: dist[start->u] + dist[u->v]
                int new_dist = dist[u] + edge->weight;
                
                // If this path is shorter, update it (relaxation step)
                if (new_dist < dist[v]) {
                    dist[v] = new_dist;  // Update distance
                    parent[v] = u;       // Record that we got to v from u
                }
            }
            edge = edge->next;  // Check next neighbor
        }
    }
    
    // Check if path was found (end vertex is reachable)
    if (dist[end] != INFINITY_DIST) {
        result.found = true;
        result.total_distance = dist[end];
        // Reconstruct the actual path using parent pointers
        result.path = reconstruct_path(parent, start, end, &result.path_length);
    }
    
    // Clean up temporary arrays
    free(dist);
    free(visited);
    free(parent);
    
    return result;
}

/**
 * Free path result memory
 */
void path_result_destroy(PathResult* result) {
    if (result && result->path) {
        free(result->path);
        result->path = NULL;
    }
}