#include <stdio.h>

#define MAX 20
#define INF 9999  // Representation of infinity

void AllPairsShortestPaths(int A[MAX][MAX], int n) {
    int i, j, k;

    for (k = 1; k <= n; k++) {
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= n; j++) {
                if (A[i][k] + A[k][j] < A[i][j]) {
                    A[i][j] = A[i][k] + A[k][j];
                }
            }
        }
    }
}

int main() {
    int n, i, j;
    int A[MAX][MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix (use %d for infinity):\n", INF);
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    AllPairsShortestPaths(A, n);

    printf("\nShortest paths matrix:\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (A[i][j] == INF)
                printf("INF ");
            else
                printf("%3d ", A[i][j]);
        }
        printf("\n");
    }

    return 0;
}
