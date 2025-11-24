/**
 * map.c
 * Interactive shortest path finder using Dijkstra's algorithm
 */

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
    printf("  path - find the shortest path between two cities\n");
    printf("  help - print this help message\n");
    printf("  exit - exit the program\n");
}

/**
 * Trim whitespaces from user input
 */
void trim_whitespace(char* str) {
    if (!str) return;
    
    // Trim front whitespace
    char* start = str;
    while (*start == ' ' || *start == '\t' || *start == '\r') {
        start++;
    }
    
    // Trim back whitespace
    char* end = start + strlen(start) - 1;
    while (end > start && (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n')) {
        end--;
    }
    
    *(end + 1) = '\0';
    if (start != str) {
        memmove(str, start, strlen(start) + 1);
    }
}

/**
 * Load vertices from file
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
        // Remove \n at the end
        line[strcspn(line, "\n")] = 0;
        
        // Trim whitespaces
        trim_whitespace(line);
        
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
        
        // Trim whitespace from city names
        trim_whitespace(city1);
        trim_whitespace(city2);
        
        // Add bidirectional edge to graph
        graph_add_edge(graph, city1, city2, distance);
    }
    
    fclose(file);
    return true;
}

/**
 * Process user command
 */
bool process_command(Graph* graph, char* input) {
    // Trim whitespaces and remove \n
    trim_whitespace(input);
    
    // Handle commands
    if (strcmp(input, "exit") == 0) {
        return false;  // Exits program
    }
    else if (strcmp(input, "help") == 0) {
        print_help();
    }
    else if (strcmp(input, "list") == 0) {
        graph_print_vertices(graph);  // Display all cities
    }
    else if (strcmp(input, "path") == 0) {
        // Prompt for city 1
        char city1[MAX_CITY_NAME];
        printf("Enter first city: ");
        if (!fgets(city1, sizeof(city1), stdin)) return true;
        trim_whitespace(city1);
        
        // Prompt for city 2
        char city2[MAX_CITY_NAME];
        printf("Enter second city: ");
        if (!fgets(city2, sizeof(city2), stdin)) return true;
        trim_whitespace(city2);
        
        // Find both cities in graph
        int start = graph_find_vertex(graph, city1);
        int end = graph_find_vertex(graph, city2);
        
        // Both cities must exist
        if (start == -1 || end == -1) {
            printf("Invalid Command\n");
            print_help();
            return true;
        }
        
        // Find shortest path using Dijkstra's algorithm
        PathResult result = dijkstra_shortest_path(graph, start, end);
        
        if (result.found) {
            // Print if path exists
            printf("Path Found...\n");
            printf("\t"); 
            
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
    else {
        printf("Invalid Command\n");
        print_help();
    }
    
    return true;  // Continue program
}

/**
 * Main function
 */
int main(int argc, char* argv[]) {
    // Check command line arguments
    if (argc != EXPECTED_ARGS) {
        fprintf(stderr, "Usage: %s <vertices> <distances>\n", argv[0]);
        return ERROR;
    }
    
    // Create graph 
    Graph* graph = graph_create(INITIAL_GRAPH_CAPACITY);
    
    // Load vertices
    if (!load_vertices(graph, argv[1])) {
        graph_destroy(graph);  // Clean up on error
        return ERROR;
    }
    
    // Load distances
    if (!load_distances(graph, argv[2])) {
        graph_destroy(graph);  // Clean up on error
        return ERROR;
    }
    
    // Print welcome message
    printf("*****Welcome to the shortest path finder!******\n");
    print_help();
    printf("*******************************************************\n");
    
    // Loop
    char input[MAX_LINE];
    bool continue_loop = true;
    
    while (continue_loop) {
        // Prompt user for input
        printf("Enter command: ");
        
        // Read line from user
        if (!fgets(input, sizeof(input), stdin)) break;  // EOF or error
        
        // Check loop
        continue_loop = process_command(graph, input);
    }
    
    // Farewell message
    printf("Goodbye!\n");
    
    // Free all memory
    graph_destroy(graph);
    
    return SUCCESS;
}
