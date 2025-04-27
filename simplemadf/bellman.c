#include <stdio.h>

#define MAX 20
#define INF 9999  // Representation of infinity

void BellmanFord(int cost[MAX][MAX], int dist[MAX], int n, int v) {
    int i, j, k;

    // Step 1: Initialize distances
    for (i = 1; i <= n; i++) {
        dist[i] = cost[v][i];
    }

    // Step 2: Relax edges (n-2) times
    for (k = 2; k <= n - 1; k++) {
        for (int u = 1; u <= n; u++) { // For each vertex u
            for (i = 1; i <= n; i++) { // For each edge (i, u)
                if (dist[u] > dist[i] + cost[i][u]) {
                    dist[u] = dist[i] + cost[i][u];
                }
            }
        }
    }
}

int main() {
    int n, i, j, v;
    int cost[MAX][MAX], dist[MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter the cost adjacency matrix (use %d for infinity):\n", INF);
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    printf("Enter source vertex (1 to %d): ", n);
    scanf("%d", &v);

    BellmanFord(cost, dist, n, v);

    printf("\nShortest path distances from vertex %d:\n", v);
    for (i = 1; i <= n; i++) {
        if (dist[i] == INF)
            printf("Vertex %d : INF\n", i);
        else
            printf("Vertex %d : %d\n", i, dist[i]);
    }

    return 0;
}
