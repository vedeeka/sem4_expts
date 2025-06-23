#include <stdio.h>

#define MAX 20
#define INF 9999

void BellmanFord(int cost[MAX][MAX], int dist[MAX], int pred[MAX], int n, int v) {
    int i, j, k;

    for (i = 1; i <= n; i++) {
        dist[i] = cost[v][i];
        pred[i] = -1;
    }
    dist[v] = 0;

    for (k = 2; k <= n - 1; k++) {
        for (j = 1; j <= n; j++) {
            for (i = 1; i <= n; i++) {
                if (dist[i] != INF && cost[i][j] != INF && dist[j] > dist[i] + cost[i][j]) {
                    dist[j] = dist[i] + cost[i][j];
                    pred[j] = i;
                }
            }
        }
    }
}

void printPath(int pred[MAX], int vertex) {
    if (pred[vertex] == -1) {
        printf("%d", vertex);
        return;
    }
    printPath(pred, pred[vertex]);
    printf(" -> %d", vertex);
}

int main() {
    int n, i, j, v;
    int cost[MAX][MAX], dist[MAX], pred[MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter the cost adjacency matrix (use %d for infinity):\n", INF);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            scanf("%d", &cost[i][j]);

    printf("Enter source vertex (1 to %d): ", n);
    scanf("%d", &v);

    BellmanFord(cost, dist, pred, n, v);

    printf("\nShortest path distances and paths from vertex %d:\n", v);
    for (i = 1; i <= n; i++) {
        if (i == v) continue;
        printf("To Vertex %d: ", i);
        if (dist[i] == INF)
            printf("No path (INF)\n");
        else {
            printf("Distance = %d, Path = ", dist[i]);
            printPath(pred, i);
            printf("\n");
        }
    }

    return 0;
}
