#include <stdio.h>

int n, m; // n = number of vertices, m = number of colors
int G[10][10], x[10];

void NextValue(int k) {
    int j;
    do {
        x[k] = (x[k] + 1) % (m + 1);
        if (x[k] == 0)
            return;

        for (j = 1; j <= n; j++) {
            if (G[k][j] != 0 && x[k] == x[j])
                break;
        }

        if (j == n + 1)
            return;
    } while (1);
}

void mColoring(int k) {
    do {
        NextValue(k);
        if (x[k] == 0)
            return;

        if (k == n) {
            printf("Solution: ");
            for (int i = 1; i <= n; i++)
                printf("%d ", x[i]);
            printf("\n");
        } else {
            mColoring(k + 1);
        }
    } while (1);
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &G[i][j]);
        }
    }

    printf("Enter number of colors: ");
    scanf("%d", &m);

    for (int i = 1; i <= n; i++)
        x[i] = 0;

    printf("All possible solutions are:\n");
    mColoring(1);

    return 0;
}
