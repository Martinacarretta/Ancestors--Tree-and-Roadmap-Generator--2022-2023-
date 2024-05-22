#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SMALL 0
#define MEDIUM 1
#define LARGE 2

#define MODEL SMALL

#if MODEL == SMALL
    #include "small.h"
    char str[] = "This is a small case of the program";
#elif MODEL == MEDIUM
    #include "medium.h"
    char str[] = "This is a medium case of the program";
#elif MODEL == LARGE
    #include "large.h"
    char str[] = "This is a large case of the program";
#endif

//---------------------------------------------------------------------------------------------------------------------------------------
// We will have the path which will be used for all partial roads
// And a head for the main road map. 
struct RoadMap * head = NULL; // For the total road map
struct RoadMap * path = NULL; // For partial road map
struct RoadMap * last = NULL; // For partial road map
struct FamilyTreeNode * headtree = NULL; // For the trees
int array [NUMBER_CITIES] = {0}; // Will be used for the partial roads


// PATHS --------------------------------------------------------------------------------------------------------------------------------
int smallestNonZero (int adjacency_matrix[NUMBER_CITIES][NUMBER_CITIES], int a, int visited[]) { // Function to find the city id of the cheapest connection with city i
    int snz = -1; // Smallest non zero weight
    int id = -1; // City id with snz weight
    for (int i = 0; i < NUMBER_CITIES; i++) { // Check for all cities
        if (visited[i] == 0 && adjacency_matrix[a][i] > 0){// Check for all CONNECTED and unvisited cities
            if (snz == -1 || adjacency_matrix[a][i] < snz) { // In case we don't have any minimum cost
                snz = adjacency_matrix[a][i];
                id = i;
            }
        }
    }
    return id;
}

void heuristic(int adjacency_matrix[NUMBER_CITIES][NUMBER_CITIES], int a, int b, int visited[], int current_weight) {
    // Create city and add it to list
    struct RoadMap * city = malloc(sizeof(struct RoadMap));
    city -> city_id = a;
    city -> total_cost = current_weight;
    city -> next = NULL;
    if (path == NULL){ // In case no city is in the partial roadMap
        path = last = city;
    }
    else{
        (last) -> next = city;
        last = city;
    }
    visited[a] = 1;  // Mark the current node as visited

    if (adjacency_matrix[a][b] != 0) { // Direct case
        struct RoadMap * city = malloc(sizeof(struct RoadMap));
        city -> city_id = b;
        city -> total_cost = current_weight + adjacency_matrix[a][b]; // Adding the cost we already have plus the connection one
        city -> next = NULL;
        last -> next = city;
        last = city;
        visited[a] = 1;  // Mark the current node as visited
        return;
    }
    else { // General case
        // Look for the smallest cost
        int c = smallestNonZero(adjacency_matrix, a, visited);
        while (c == -1) { // In case no id is returned, search for another
            visited[c] = 1; // Mark as visited because we don't want that city
            c = smallestNonZero(adjacency_matrix, a, visited);  
        }
        heuristic(adjacency_matrix, c, b, visited, current_weight + adjacency_matrix[a][c]);
    }
}

void findShortestPath(int adjacency_matrix[NUMBER_CITIES][NUMBER_CITIES], int a, int b) { // ACABADA
    int visited[NUMBER_CITIES] = {0};  // Array to track visited nodes

    heuristic (adjacency_matrix, a, b, visited, 0);
    //printf("%d", path->city_id);
}

void addToRoadMap() { // ACABADA
    // Function to add a partial path to the total one
    struct RoadMap * current = head; // Pointer to traverse the list
    if (head == NULL) { // No items in list
        head = path; // Passing the path to the main road map
    }
    else {
        while (current -> next != NULL) { // Traverse the main map to get to last position
            current = current -> next;
        }
        current -> next = path; // Passing the path to the main road map 
        // so it will already be added
    }
    path = last = NULL; // Prepare it to NULL for next partial map
}

int printPartialMap() {
    int Total_price = 0; // Initialize Total_price
    struct RoadMap* current = head; // Pointer to traverse the list

    if (head != NULL) { // Items in list
        while (current != NULL && current->next != NULL) { // To do each partial road map
            while (current->next != NULL && current->city_id != current->next->city_id) { // To stop when the next partial begins
                printf("%s - ", citiesInfo[current->city_id].city_name); // Prints name of city
                current = current->next;
            }
            printf("%s - %d\n", citiesInfo[current->city_id].city_name, current->total_cost); // Print last city of partial
            Total_price += current->total_cost;
            current = current->next;
        }
        return Total_price; // This should return the total price of the whole road map
    }
    return 0;
}

void printMap() {
    struct RoadMap * current = head; // Pointer to traverse the list
    while (current -> next != NULL) { // To do each partial road map
        if (current -> city_id != current -> next -> city_id) { // To avoid consequent repeated cities
            printf("%s - ", citiesInfo[current -> city_id].city_name); // Prints name of city
        }
        current = current -> next;
    }
    printf("%s\n", citiesInfo[current -> city_id].city_name);
}

void deleteAllRoadMap (){ // Eliminate when all cities of list //REVISAR
    struct RoadMap * current = head; // Used to traverse the list
    struct RoadMap * next;
    while (current != NULL) {
        next = current -> next; // Hold the second node
        free(current); // Free the first one
        current = next; // put current to be the next
    }
    head = NULL;

    current = path; // Used to traverse the list
    while (current != NULL) {
        next = current -> next; // Hold the second node
        free(current); // Free the first one
        current = next; // put current to be the next
    }
    path = NULL;
}

// TREES --------------------------------------------------------------------------------------------------------------------

struct FamilyTreeNode * DFStree (int city) {
    // City is the city id of origin
    // Create node
    int i = 0;
    while (array[i] != -1) { // Traverse list
        i++;
    }
    array[i] = city; // Add to the array the cities we have to get to IN DFS order
    
    struct FamilyTreeNode * node = malloc(sizeof(struct FamilyTreeNode)); // Create a node to add
    strcpy(node -> motherName, citiesInfo[city].mother_name); // Copy the name of citiesInfo
    strcpy(node -> fatherName, citiesInfo[city].father_name); // Use strcpy because they are character arrays
    node -> city_id = city;
    node -> mother_parents = NULL;
    node -> father_parents = NULL;
    int citym = citiesInfo[city].mother_parents_city_id; // ID of the mother's city
    int cityf = citiesInfo[city].father_parents_city_id; // ID of the father's city

    if (citym != -1) { // If it's not the last node on the mother side
        node -> mother_parents = DFStree(citym);
        node -> father_parents = DFStree(cityf);
    }
    return node;
}

void BFStree (struct FamilyTreeNode* headtree) {
    if (headtree == NULL) {
        return;
    }
    else {
        struct FamilyTreeNode* queue[NUMBER_CITIES]; // Array that will hold nodes to do
        int start = 0; // These will keep track of the nodes we have to do and the ones we have done
        int end = 0;
        // To control the level
        int level = 0;
        int done = 0;
        int x;
        // Add headtree to queue
        queue[0] = headtree;
        end++; // Add 1 because there is one node more to do

        while (start < end) { // We still have nodes to print
            // Create a node (first one in queue)
            struct FamilyTreeNode* node = queue[start];
            for (int i = 0; i < level; i++){
                printf("--> ");
            }
            printf("%s and %s (%s)\n", node -> motherName, node -> fatherName, citiesInfo[node -> city_id].city_name); // Print
            start++; // Update
            done++;
            // Add city to road map
            int i = 0;
            while (array[i] != -1) { // Traverse list
                i++;
            }
            array[i] = node -> city_id; // Add to the array the cities we have to get to IN DFS order

            // Add to queue the parents of node
            if (node -> mother_parents != NULL) { // Branch not finished
                queue[end] = node -> mother_parents;
                end++;
                queue[end] = node -> father_parents;
                end++;
            }
            // update of level and reset done:
            x = 1;
            for (int i = 0; i < level; i++) {
                x = x * 2;
            }
            if (x == done){
                level++;
                done = 0;
                
            }
        }
    }
}

void printTree (struct FamilyTreeNode *current, int level) { // ACABADA
    if (current == NULL) {
       return;
    }
    else {
        for (int i = 0; i < level; i++) {
            printf("--> ");
        }

        printf("%s and %s (%s)\n", current -> motherName, current -> fatherName, citiesInfo[current -> city_id].city_name);

        printTree(current -> mother_parents, level + 1);
        printTree(current -> father_parents, level + 1);
    }
}

// MAIN --------------------------------------------------------------------------------------------------------------------

void main() {
    // Do DFS:     
    for (int i = 0; i < NUMBER_CITIES; i++) { // Adding city to array
        array[i] = -1; // Changing to -1, because 0 is a city
    }
    printf("%s", str);
    printf("\nAncestors’ tree:\n\nDFS -> Names: \n");
    headtree = DFStree(0); // We start in Barcelona
    printTree(headtree, 0);
    printf("\nPartial road map: \n");
    int i = 0;
    while (array[i] != -1 && array[i+1]!=-1) { 
        findShortestPath(adjacency_matrix, array[i], array[i+1]);
        addToRoadMap();
        i++;
    }
    int Total_price = printPartialMap ();
    printf("\nTotal road map: \n");
    printMap();
    printf("\nTotal cost: %d\n", Total_price);
    printf("\n-----------------------------------------------------------------------\n");

    deleteAllRoadMap ();
    printf("BFS -> Names: \n");
    // Do BFS:
    for (int i = 0; i < NUMBER_CITIES; i++) { // Resetting to -1
        array[i] = -1; // Changing to -1, because 0 is a city
    }
    BFStree(headtree);
    printf("\nPartial road map: \n");
    i = 0;
    while (array[i] != -1 && array[i+1]!=-1) { 
        findShortestPath(adjacency_matrix, array[i], array[i+1]);
        addToRoadMap();
        i++;
    }
    Total_price = printPartialMap ();
    printf("\nTotal road map: \n");
    printMap();
    printf("\nTotal cost: %d\n", Total_price);
    deleteAllRoadMap ();

}