#include <stdio.h>

#define MAX 20
#define INF 9999

void AllPaths(int cost[MAX][MAX], int A[MAX][MAX], int n) {
    int i, j, k;

    // Copy cost into A
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            A[i][j] = cost[i][j];

    // Floyd-Warshall core
    for (k = 1; k <= n; k++)
        for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)
                if (A[i][k] + A[k][j] < A[i][j])
                    A[i][j] = A[i][k] + A[k][j];
}

int main() {
    int n, i, j;
    int cost[MAX][MAX], A[MAX][MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter the cost adjacency matrix (use %d for infinity):\n", INF);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            scanf("%d", &cost[i][j]);

    AllPaths(cost, A, n);

    printf("\nShortest paths between all pairs:\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++)
            if (A[i][j] == INF)
                printf("INF ");
            else
                printf("%3d ", A[i][j]);
        printf("\n");
    }

    return 0;
}
