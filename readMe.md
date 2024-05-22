# Ancestors’ Tree and Roadmap Generator

This C program generates ancestral trees and roadmaps between cities. It implements both depth-first search (DFS) and breadth-first search (BFS) algorithms to traverse the trees and create roadmaps.

## Description

The program starts with a predefined model size: SMALL, MEDIUM, or LARGE, which determines the complexity of the generated ancestral tree and roadmap.

## Ancestors’ Tree

The ancestral tree represents the lineage of individuals across different generations. Each node in the tree contains information about the individual's parents and the city they are associated with.

### DFS Traversal
The program performs a depth-first search traversal to generate the ancestral tree. It prints the names of individuals along with their parents' names and the associated city.

### BFS Traversal
Similarly, the program also performs a breadth-first search traversal to generate the ancestral tree. It prints the names of individuals along with their parents' names and the associated city.

## Roadmap Generation

The program generates a roadmap that connects cities based on the ancestral tree. It calculates the shortest path between each pair of cities using a heuristic function.

### Partial Roadmap
The program prints the partial roadmap, which shows the sequence of cities visited during the traversal. It includes the names of cities and the total cost of the route.

### Total Roadmap
The total roadmap includes the complete sequence of cities visited during the traversal, along with the total cost of the route.

## Usage

1. Compile the program.
2. Run the compiled executable.
3. The program will generate the ancestral tree using both DFS and BFS traversal methods.
4. It will then generate the partial and total roadmaps based on the ancestral tree.
5. The roadmaps will be printed, along with their associated costs.

## Model Configuration

The program's behavior can be configured by setting the `MODEL` macro to one of the following values: `SMALL`, `MEDIUM`, or `LARGE`. Each model represents a different complexity level for the ancestral tree and roadmap generation.

## Dependencies

The program relies on the standard C libraries `stdio.h`, `string.h`, and `stdlib.h`.

## Note

This program is a demonstration of tree traversal algorithms and roadmap generation. It can be extended and adapted for various applications involving hierarchical data structures and route planning.