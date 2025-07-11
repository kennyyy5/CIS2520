/*
    name: Kenny Adenuga
    student ID: 1304431
    date: 27/11/20224
    assignment name: 1304431
*/

#include "graph.h"

/* function will display the primary user interface
    This is already done for you*/
void prompt(void)
{

    printf("\nMenu:\n");
    printf("1. Display Adjacency List\n");
    printf("2. Perform Breadth-First Search (BFS)\n");
    printf("3. Perform Depth-First Search (DFS)\n");
    printf("4. Find Shortest Path using Dijkstra's Algorithm\n");
    printf("5. Exit\n");
}

/**
 * Reads a graph from a file and constructs the graph structure.
 * @param filename The name of the file containing the adjacency matrix.
 * @return Pointer to the created Graph structure, or NULL if an error occurs.
 */
Graph *readGraph(const char *filename)
{
    // Implement the function logic here
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Could not open file %s\n", filename);
        return NULL;
    }

    Graph *graph = malloc(sizeof(Graph));
    if (!graph)
    {
        printf("Memory allocation error %s\n", filename);
        fclose(file);
        return NULL;
    }

    int i = 0;
    int j = 0;
    while (fscanf(file, "%d", &graph->adjMatrix[i][j]) != EOF)
    {
        j++;
        if (j >= MAX_VERTICES)
        {
            printf("Matrix size exceeds MAX_VERTICES\n");
            fclose(file);
            free(graph);
            return NULL;
        }
        if (fgetc(file) == '\n')
        { // Move to the next row on a newline character
            i++;
            j = 0;
        }
    }
    // printf("%d", i);
    graph->numVertices = i + 1; // The number of rows is the number of vertices
    fclose(file);

    createAdjacencyList(graph);
    return graph;
}

/**
 * Creates a new node for the adjacency list.
 * @param vertex The vertex number that this node will represent.
 * @return Pointer to the newly created Node structure.
 */
Node *createNode(int vertex)
{
    // Implement the function logic here
    Node *new = malloc(sizeof(Node));
    new->vertex = vertex;
    new->next = NULL;
    return new;
}

/**
 * Displays the adjacency list of the graph.
 * @param graph Pointer to the Graph structure.
 */
void displayAdjacencyList(Graph *graph)
{
    // Implement the function logic here
    for (int i = 0; i < graph->numVertices; i++)
    {
        printf("Vertex %d: ", i + 1);
        Node *temp = graph->adjList[i];
        while (temp)
        {
            printf("(%d, %d) ", temp->vertex + 1, graph->adjMatrix[i][temp->vertex]);
            temp = temp->next;
        }
        printf("\n");
    }
}

/**
 * Converts the adjacency matrix of the graph to an adjacency list.
 * @param graph Pointer to the Graph structure.
 */
void createAdjacencyList(Graph *graph)
{
    // Implement the function logic here
    for (int i = 0; i < graph->numVertices; i++)
    {
        graph->adjList[i] = NULL;
        for (int j = 0; j < graph->numVertices; j++)
        {
            if (graph->adjMatrix[i][j] != 0)
            {
                Node *newNode = createNode(j);
                newNode->next = graph->adjList[i];
                graph->adjList[i] = newNode;
            }
        }
    }
}

/**
 * Performs Breadth-First Search (BFS) starting from a given vertex.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which BFS starts (0-based index).
 */
void bfs(Graph *graph, int startVertex)
{
    // Implement the function logic here
    bool visited[MAX_VERTICES] = {false};
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    visited[startVertex] = true;
    queue[rear++] = startVertex;

    printf("BFS: ");
    while (front != rear)
    {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex + 1);

        Node *temp = graph->adjList[currentVertex];
        while (temp)
        {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex])
            {
                queue[rear++] = adjVertex;
                visited[adjVertex] = true;
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

/**
 * Performs Depth-First Search (DFS) starting from a given vertex.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which DFS starts (0-based index).
 */
void dfs(Graph *graph, int startVertex)
{
    // Implement the function logic here
    bool visited[MAX_VERTICES] = {false};
    dfsRecursive(graph, startVertex, visited);
    printf("\n");
}

/**
 * a recursive helper function for the DFS function.
 * @param graph Pointer to the Graph structure.
 * @param vertex vertex being traversed.
 * @param visited array of vertex the function has visited
 */
void dfsRecursive(Graph *graph, int vertex, bool visited[])
{
    visited[vertex] = true;
    printf("%d ", vertex + 1);

    Node *temp = graph->adjList[vertex];
    while (temp)
    {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex])
        {
            dfsRecursive(graph, adjVertex, visited);
        }
        temp = temp->next;
    }
}

/**
 * Finds the shortest path from the start vertex to all other vertices using Dijkstra's algorithm.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which to start the algorithm (0-based index).
 */
void dijkstra(Graph *graph, int startVertex)
{
    // Implement the function logic here
    int dist[MAX_VERTICES];
    bool visited[MAX_VERTICES] = {false};

    for (int i = 0; i < graph->numVertices; i++)
    {
        dist[i] = INT_MAX;
    }
    dist[startVertex] = 0;

    for (int i = 0; i < graph->numVertices - 1; i++)
    {
        int minDist = INT_MAX, minIndex;
        for (int j = 0; j < graph->numVertices; j++)
        {
            if (!visited[j] && dist[j] <= minDist)
            {
                minDist = dist[j];
                minIndex = j;
            }
        }

        visited[minIndex] = true;

        Node *temp = graph->adjList[minIndex];
        while (temp)
        {
            int adjVertex = temp->vertex;
            int weight = graph->adjMatrix[minIndex][adjVertex];
            if (!visited[adjVertex] && dist[minIndex] != INT_MAX && dist[minIndex] + weight < dist[adjVertex])
            {
                dist[adjVertex] = dist[minIndex] + weight;
            }
            temp = temp->next;
        }
    }

    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < graph->numVertices; i++)
    {
        printf("%d\t%d\n", i + 1, dist[i]);
    }
}

/**
 * Frees the memory allocated for the graph, including the adjacency list.
 * @param graph Pointer to the Graph structure to be freed.
 */
void freeGraph(Graph *graph)
{
    // Implement the function logic here
    for (int i = 0; i < graph->numVertices; i++)
    {
        Node *temp = graph->adjList[i];
        while (temp)
        {
            Node *toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(graph);
}
