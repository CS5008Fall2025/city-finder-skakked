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

// Test 2: Add Vertex
void test_add_vertices() {
    printf("\n=== Test 2: Adding Vertices ===\n");
    
    Graph* graph = graph_create(5);
    
    int idx1 = graph_add_vertex(graph, "boston");
    assert_test(idx1 == 0, "First vertex index is 0");
    
    int idx2 = graph_add_vertex(graph, "chicago");
    assert_test(idx2 == 1, "Second vertex index is 1");
    
    int idx3 = graph_add_vertex(graph, "boston");
    assert_test(idx3 == 0, "Duplicate vertex returns existing index");
    
    graph_destroy(graph);
}


 // Test 3: Finding Vertices
void test_find_vertices() {
    printf("\n=== Test 3: Finding Vertices ===\n");
    
    Graph* graph = graph_create(5);
    graph_add_vertex(graph, "boston");
    graph_add_vertex(graph, "chicago");
    
    int idx1 = graph_find_vertex(graph, "boston");
    assert_test(idx1 == 0, "Found 'boston' at index 0");
    
    int idx2 = graph_find_vertex(graph, "seattle");
    assert_test(idx2 == -1, "Non-existing vertex returns -1");
    
    graph_destroy(graph);
}





