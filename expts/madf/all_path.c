#include<stdio.h>
#include<stdlib.h>

#define INF 99999

int min(int a, int b) {
    return (a < b) ? a : b;
}

void display_matrix(int a[10][10], int p[10][10], int n, int k) {
    printf("\nA^%d = [", k);
    for (int i = 0; i < n; i++) {
        printf("\n\t");
        for (int j = 0; j < n; j++) {
            if (a[i][j] == INF)
                printf("INF ");
            else
                printf("%3d ", a[i][j]);
        }
    }
    printf("\n    ]");
    printf("\nP^%d = [", k);
    for (int i = 0; i < n; i++) {
        printf("\n\t");
        for (int j = 0; j < n; j++) {
            if (p[i][j] == -1)
                printf(" -1 ");
            else
                printf("%3d ", p[i][j] + 1);
        }
    }
    printf("\n    ]\n");
}

void display_path_table(int a[10][10], int p[10][10], int n) {
    printf("\nSource\tDestination\tLength\tPath\n");
    printf("-------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && a[i][j] != INF) {
                printf("%d\t\t%d\t\t%d\t", i + 1, j + 1, a[i][j]);
                int path[10], path_length = 0, current = j, predecessor;
                while (current != i) {
                    path[path_length++] = current;
                    predecessor = p[i][current];
                    if (predecessor == -1) {
                        path_length = 0;
                        break;
                    }
                    current = predecessor;
                }
                if (path_length > 0) {
                    printf("%d", i + 1);
                    for (int k = path_length - 1; k >= 0; k--)
                        printf(" → %d", path[k] + 1);
                    printf("\n");
                } else {
                    printf("No path\n");
                }
            }
        }
    }
}

void all_path(int cost[10][10], int a[10][10], int n) {
    int a_prev[10][10], p[10][10];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = cost[i][j];
            p[i][j] = (i == j || cost[i][j] == INF) ? -1 : i;
        }
    }
    display_matrix(a, p, n, 0);
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                a_prev[i][j] = a[i][j];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (a_prev[i][k] != INF && a_prev[k][j] != INF && a_prev[i][j] > a_prev[i][k] + a_prev[k][j]) {
                    a[i][j] = a_prev[i][k] + a_prev[k][j];
                    p[i][j] = p[k][j];
                }
            }
        }
        display_matrix(a, p, n, k + 1);
    }
    display_path_table(a, p, n);
}

int main() {
    int a[10][10], cost[10][10], n;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cost[i][j] = (i == j) ? 0 : INF;
    int i, j, k;
    printf("Enter the edges and their cost (source destination weight, use -1 -1 to end):\n");
    while (1) {
        scanf("%d %d %d", &i, &j, &k);
        if (i == -1 || j == -1)
            break;
        else if (i > 0 && i <= n && j > 0 && j <= n)
            cost[i - 1][j - 1] = k;
        else
            printf("Invalid vertex input. Vertices should be between 1 and %d or -1 to end.\n", n);
    }
    all_path(cost, a, n);
    return 0;
}
