#include "graph.h"
#include "dijkstra.h"
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
 * Print help message
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

/**
 * Process user command
 * Returns false if user wants to exit, true to continue
 */
bool process_command(Graph* graph, char* input) {
    // Trim input and tokenize
    char* token1 = strtok(input, " \t\n\r");
    if (!token1) return true;  // Empty input, continue
    
    // Handle commands
    if (strcmp(token1, "exit") == 0) {
        return false;  // Signal to exit program
    }
    else if (strcmp(token1, "help") == 0) {
        print_help();
    }
    else if (strcmp(token1, "list") == 0) {
        graph_print_vertices(graph);  // Display all cities
    }
    else {
        // Try to parse as two cities: "<city1> <city2>"
        char* token2 = strtok(NULL, " \t\n\r");  // Get second token
        
        // If no second token, invalid command
        if (!token2) {
            printf("Invalid Command\n");
            print_help();
            return true;
        }
        
        // Find both cities in graph
        int start = graph_find_vertex(graph, token1);
        int end = graph_find_vertex(graph, token2);
        
        // Both cities must exist
        if (start == -1 || end == -1) {
            printf("Invalid Command\n");
            print_help();
            return true;
        }
        
        // Find shortest path using Dijkstra's algorithm
        PathResult result = dijkstra_shortest_path(graph, start, end);
        
        if (result.found) {
            // Path exists - print it
            printf("Path Found...\n");
            printf("\t");  // Tab character as specified
            
            // Print each city in path
            for (int i = 0; i < result.path_length; i++) {
                printf("%s", graph->vertices[result.path[i]].name);
                if (i < result.path_length - 1) printf(" ");  // Space between cities
            }
            printf("\n");
            
            // Print total distance
            printf("\tTotal Distance: %d\n", result.total_distance);
        } else {
            // No path exists between cities
            printf("Path Not Found...\n");
        }
        
        // Free path memory
        path_result_destroy(&result);
    }
    
    return true;  // Continue program
}

/**
 * Main function
 */
int main(int argc, char* argv[]) {
    // Check command line arguments: program expects exactly 2 files
    if (argc != EXPECTED_ARGS) {
        fprintf(stderr, "Usage: %s <vertices> <distances>\n", argv[0]);
        return ERROR;
    }
    
    // Create graph with initial capacity
    Graph* graph = graph_create(INITIAL_GRAPH_CAPACITY);
    
    // Load vertices (cities) from first file
    if (!load_vertices(graph, argv[1])) {
        graph_destroy(graph);  // Clean up on error
        return ERROR;
    }
    
    // Load distances (edges) from second file
    if (!load_distances(graph, argv[2])) {
        graph_destroy(graph);  // Clean up on error
        return ERROR;
    }
    
    // Print welcome message as specified
    printf("*****Welcome to the shortest path finder!******\n");
    print_help();
    printf("*******************************************************\n");
    
    // Interactive loop - keep asking for commands
    char input[MAX_LINE];
    bool continue_loop = true;
    
    while (continue_loop) {
        // Prompt user for input
        printf("Where do you want to go today? ");
        
        // Read line from user
        if (!fgets(input, sizeof(input), stdin)) break;  // EOF or error
        
        // Process command and check if we should continue
        continue_loop = process_command(graph, input);
    }
    
    // Farewell message
    printf("Goodbye!\n");
    
    // Free all memory
    graph_destroy(graph);
    
    return SUCCESS;
}