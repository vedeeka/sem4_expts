#include <stdio.h>
#define MAX 20
#define INF 9999

// Forward approach: FGraph
void FGraph(int c[MAX][MAX], int n, int cost[MAX], int d[MAX], int p[MAX]) {
    int j, r;

    cost[n] = 0;

    for (j = n - 1; j >= 1; j--) {
        cost[j] = INF;
        for (r = j + 1; r <= n; r++) {
            if (c[j][r] != 0 && c[j][r] + cost[r] < cost[j]) {
                cost[j] = c[j][r] + cost[r];
                d[j] = r;
            }
        }
    }

    p[1] = 1;
    p[n] = n;
    for (j = 2; j < n; j++)
        p[j] = d[p[j - 1]];
}

// Backward approach: BGraph
void BGraph(int c[MAX][MAX], int n, int bcost[MAX], int d[MAX], int p[MAX]) {
    int j, r;

    bcost[1] = 0;

    for (j = 2; j <= n; j++) {
        bcost[j] = INF;
        for (r = 1; r < j; r++) {
            if (c[r][j] != 0 && bcost[r] + c[r][j] < bcost[j]) {
                bcost[j] = bcost[r] + c[r][j];
                d[j] = r;
            }
        }
    }

    p[1] = 1;
    p[n] = n;
    for (j = n - 1; j >= 2; j--)
        p[j] = d[p[j + 1]];
}

void printPath(int p[MAX], int n) {
    printf("Minimum cost path: ");
    for (int i = 1; i <= n && p[i] != 0; i++) {
        printf("%d", p[i]);
        if (p[i + 1] != 0) printf(" -> ");
    }
    printf("\n");
}

int main() {
    int c[MAX][MAX], cost[MAX], bcost[MAX], d[MAX], p[MAX];
    int n, i, j, choice;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter cost matrix (use 0 if no direct edge):\n");
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            scanf("%d", &c[i][j]);

    printf("\nChoose approach:\n1. Forward (FGraph)\n2. Backward (BGraph)\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        FGraph(c, n, cost, d, p);
        printf("Minimum cost (FGraph): %d\n", cost[1]);
    } else if (choice == 2) {
        BGraph(c, n, bcost, d, p);
        printf("Minimum cost (BGraph): %d\n", bcost[n]);
    } else {
        printf("Invalid choice.\n");
        return 1;
    }

    printPath(p, n);

    return 0;
}
