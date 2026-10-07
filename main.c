#include <stdio.h>

#define MAX 20
#define INF 99999

// Find the vertex with minimum distance
int findMinDistance(int distance[], int visited[], int n)
{
    int min = INF;
    int minIndex = -1;

    for (int i = 0; i < n; i++)
    {
        if (!visited[i] && distance[i] < min)
        {
            min = distance[i];
            minIndex = i;
        }
    }

    return minIndex;
}

// Print the shortest path
void printPath(int parent[], int vertex)
{
    if (parent[vertex] == -1)
    {
        printf("%d", vertex + 1);
        return;
    }

    printPath(parent, parent[vertex]);
    printf(" -> %d", vertex + 1);
}

// Dijkstra's Algorithm
void dijkstra(int graph[MAX][MAX], int n, int source, int destination)
{
    int distance[MAX];
    int visited[MAX];
    int parent[MAX];

    // Initialization
    for (int i = 0; i < n; i++)
    {
        distance[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    distance[source] = 0;

    // Find shortest paths
    for (int count = 0; count < n - 1; count++)
    {
        int u = findMinDistance(distance, visited, n);

        if (u == -1)
            break;

        visited[u] = 1;

        for (int v = 0; v < n; v++)
        {
            if (!visited[v] &&
                graph[u][v] != 0 &&
                distance[u] != INF &&
                distance[u] + graph[u][v] < distance[v])
            {
                distance[v] = distance[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    // Display result
    if (distance[destination] == INF)
    {
        printf("\nNo route is available.\n");
    }
    else
    {
        printf("\nEmergency Vehicle Route\n");
        printf("-------------------------\n");

        printf("Shortest Distance : %d minutes\n", distance[destination]);

        printf("Route             : ");
        printPath(parent, destination);
        printf("\n");
    }
}

int main()
{
    int n;
    int graph[MAX][MAX];
    int source, destination;

    printf("====================================\n");
    printf("   EMERGENCY VEHICLE ROUTE PLANNER\n");
    printf("====================================\n");

    printf("\nEnter number of locations: ");
    scanf("%d", &n);

    printf("\nEnter travel time between locations\n");
    printf("(Enter 0 if there is no direct road)\n\n");

    // Input graph
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                graph[i][j] = 0;
            }
            else
            {
                printf("Travel time from Location %d to Location %d: ",
                       i + 1, j + 1);

                scanf("%d", &graph[i][j]);
            }
        }
    }

    printf("\nEnter emergency vehicle starting location: ");
    scanf("%d", &source);

    printf("Enter hospital/destination location: ");
    scanf("%d", &destination);

    // Convert to zero-based indexing
    source--;
    destination--;

    if (source < 0 || source >= n ||
        destination < 0 || destination >= n)
    {
        printf("\nInvalid location!\n");
        return 1;
    }

    dijkstra(graph, n, source, destination);

    return 0;
}