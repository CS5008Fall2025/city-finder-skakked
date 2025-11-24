/**
 * Name: Siddharth Kakked
 * Semester: Fall 2025
 * CS 5008
 * Unit tests for shortest path finder
 */

 // Project Headers
#include "graph.h" 
#include "dijkstra.h"

// Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Test counters
static int tests_run = 0;
static int tests_passed = 0;
static int tests_failed = 0;

// Assertion function to validate test cases
void assert_test(bool condition, const char* test_name) {
    tests_run++;
    if (condition) {
        tests_passed++;
        printf("[PASS] %s\n", test_name);
    } else {
        tests_failed++;
        printf("[FAIL] %s\n", test_name);
    }
}

// Test 1: Graph Creation
void test_graph_creation() {
    printf("\n=== Test 1: Graph Creation ===\n");
    
    Graph* graph = graph_create(10);
    assert_test(graph != NULL, "Graph created successfully");
    assert_test(graph->num_vertices == 0, "Initial vertex count is 0");
    assert_test(graph->capacity == 10, "Initial capacity is 10");
    
    graph_destroy(graph);
}






