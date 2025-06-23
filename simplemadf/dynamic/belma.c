#include <stdio.h>
#include <limits.h>

#define MAX 100
#define INF 99999

typedef struct {
    int src, dest, cost;
} Edge;


void printPath(int parent[], int vertex) {
    if (parent[vertex] == -1) {
        printf("%d", vertex);
        return;
    }
    printPath(parent, parent[vertex]);
    printf(" -> %d", vertex);
}


void BellmanFord(int v, Edge edge[], int dist[], int parent[], int n, int e) {

    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[v] = 0;

    for (int k = 1; k < n; k++) {
        for (int i = 0; i < e; i++) {
            int u = edge[i].src;
            int w = edge[i].dest;
            int cost = edge[i].cost;

            if (dist[u] != INF && dist[w] > dist[u] + cost) {
                dist[w] = dist[u] + cost;
                parent[w] = u;
            }
        }
    }

    printf("\nShortest distances and paths from vertex %d:\n", v);
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INF) {
            printf("Vertex %d: INF (No path)\n", i);
        } else {
            printf("Vertex %d: %d | Path: ", i, dist[i]);
            printPath(parent, i);
            printf("\n");
        }
    }
}

int main() {
    int n, e, v;
    Edge edge[MAX];
    int dist[MAX];
    int parent[MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &e);

    printf("Enter source vertex: ");
    scanf("%d", &v);

    printf("Enter edges (src dest cost) including negative costs:\n");
    for (int i = 0; i < e; i++) {
        scanf("%d %d %d", &edge[i].src, &edge[i].dest, &edge[i].cost);
    }

    BellmanFord(v, edge, dist, parent, n, e);

    return 0;
}
