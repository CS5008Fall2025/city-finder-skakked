# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g  # -Wall=all warnings, -Wextra=extra warnings, -g=debug symbols
TARGET = map.out

# Object files needed for final executable
OBJS = map.o graph.o dijkstra.o

# Default target - builds everything
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile map.c to map.o
# Dependencies: graph.h and dijkstra.h (if these change, recompile)
map.o: map.c graph.h dijkstra.h
	$(CC) $(CFLAGS) -c map.c

# Compile graph.c to graph.o
# Dependencies: graph.h
graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c

# Compile dijkstra.c to dijkstra.o
# Dependencies: dijkstra.h and graph.h
dijkstra.o: dijkstra.c dijkstra.h graph.h
	$(CC) $(CFLAGS) -c dijkstra.c

# Clean up build files - removes all .o files and executable
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets - not actual files, just commands
.PHONY: all clean