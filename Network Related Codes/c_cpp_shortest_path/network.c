#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define V 10 // Number of nodes

// Structure for adjacency list nodes
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Structure for adjacency list
typedef struct {
    Node* head;
} AdjList;

// Graph structure
typedef struct {
    AdjList* array;
} Graph;

// Function to create a new node
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize the graph
Graph* createGraph() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));
    for (int i = 0; i < V; i++) {
        graph->array[i].head = NULL;
    }
    return graph;
}

// Function to add an edge to the graph
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    
    newNode = createNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// BFS to find shortest path in terms of hops
void dijkstra(Graph* graph, int src, int target, int parent[], int dist[]) {
    int queue[V], front = 0, rear = 0;
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }
    
    dist[src] = 0;
    queue[rear++] = src;
    
    while (front < rear) {
        int node = queue[front++];
        Node* temp = graph->array[node].head;
        while (temp) {
            int neighbor = temp->vertex;
            if (dist[node] + 1 < dist[neighbor]) {
                dist[neighbor] = dist[node] + 1;
                parent[neighbor] = node;
                queue[rear++] = neighbor;
            }
            temp = temp->next;
        }
    }
}

// Function to print the shortest path
void printPath(int target, int parent[]) {
    int path[V], index = 0;
    for (int v = target; v != -1; v = parent[v]) {
        path[index++] = v;
    }
    
    printf("Shortest path: ");
    for (int i = index - 1; i >= 0; i--) {
        printf("%d", path[i]);
        if (i > 0) printf(" -> ");
    }
    printf("\n");
}

int main() {
    Graph* graph = createGraph();
    
    // Creating the bidirectional graph
    int edges[][2] = {
        {0, 1}, {1, 2}, {2, 3}, {2, 6}, {3, 4},
        {4, 5}, {6, 7}, {6, 8}, {6, 9}
    };
    int numEdges = sizeof(edges) / sizeof(edges[0]);
    
    for (int i = 0; i < numEdges; i++) {
        addEdge(graph, edges[i][0], edges[i][1]);
    }
    
    int src = 0;
    int target = 8;
    int parent[V], dist[V];
    
    dijkstra(graph, src, target, parent, dist);
    
    printf("Shortest hop count from %d to %d: %d\n", src, target, dist[target]);
    printPath(target, parent);
    
    return 0;
}
