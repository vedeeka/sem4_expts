#include <stdio.h>

#define MAX 20
#define INF 9999

int cost[MAX][MAX];
int dist[MAX];
int path[MAX];
int n;

void MultistageGraph() {
    int i, j;
    
    dist[n] = 0; // Distance from destination to destination is 0

    for (i = n - 1; i >= 1; i--) {
        dist[i] = INF;
        for (j = i + 1; j <= n; j++) {
            if (cost[i][j] != INF && cost[i][j] + dist[j] < dist[i]) {
                dist[i] = cost[i][j] + dist[j];
                path[i] = j;
            }
        }
    }
}

void printPath() {
    int i = 1;
    printf("\nShortest Path: %d", i);

    while (i != n) {
        i = path[i];
        printf(" -> %d", i);
    }
    printf("\n");
}

int main() {
    int i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter cost adjacency matrix (use %d for infinity):\n", INF);
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    MultistageGraph();

    printf("\nMinimum cost from 1 to %d = %d\n", n, dist[1]);
    printPath();

    return 0;
}
