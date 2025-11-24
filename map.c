/**
 * Name: Siddharth Kakked
 * Semester: Fall 2025
 * CS 5008
 * Shortest path finder using Dijkstra's algorithm
 */

#include "graph.h" // Include graph structure and related functions
#include "dijkstra.h" // Include Dijkstra's algorithm implementation
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants for program configuration
#define MAX_LINE 256               // Maximum line length for file reading
#define MAX_CITY_NAME 100          // Maximum length for city name
#define INITIAL_GRAPH_CAPACITY 50  // Starting capacity for graph
#define SUCCESS 0                  // Return code for success
#define ERROR 1                    // Return code for error
#define EXPECTED_ARGS 3            // Expected command line arguments

/**
 * CLI help message
 */
void print_help() {
    printf("Commands:\n");
    printf("  list - list all cities\n");
    printf("  <city1> <city2> - find the shortest path between two cities\n");
    printf("  help - print this help message\n");
    printf("  exit - exit the program\n");
}

/**
 * Load vertices from file
 * Each line in file is a city name
 */
bool load_vertices(Graph* graph, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return false;
    }
    
    char line[MAX_LINE];
    // Read file line by line
    while (fgets(line, sizeof(line), file)) {
        // Remove newline character at end
        line[strcspn(line, "\n")] = 0;
        
        // Skip empty lines
        if (strlen(line) == 0) continue;
        
        // Add city to graph
        graph_add_vertex(graph, line);
    }
    
    fclose(file);
    return true;
}

/**
 * Load distances from file
 * Each line format: city1 city2 distance
 */
bool load_distances(Graph* graph, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return false;
    }
    char line[MAX_LINE];
    // Read file line by line
    while (fgets(line, sizeof(line), file)) {
        char city1[MAX_CITY_NAME], city2[MAX_CITY_NAME];
        int distance;
        
        // Parse line: city1 city2 distance
        // sscanf returns number of items successfully parsed
        int parsed = sscanf(line, "%s %s %d", city1, city2, &distance);
        
        // Skip malformed lines (including empty lines)
        if (parsed != 3) continue;
        
        // Add bidirectional edge to graph
        graph_add_edge(graph, city1, city2, distance);
    }
    
    fclose(file);
    return true;
}



