#include<stdio.h>
#include<stdlib.h>

#define INF 99999 
int min(int a, int b) {
    return (a < b) ? a : b;
}

void display(int a[10][10], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] == INF) {
                printf("INF ");
            } else {
                printf("%d ", a[i][j]);
            }
        }
        printf("\n");
    }
}

void all_path(int cost[10][10], int a[10][10], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = cost[i][j];
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (a[i][k] != INF && a[k][j] != INF) {
                    a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
                }
            }
        }
    }

    display(a, n);
}

int main() {
    int a[10][10], cost[10][10], n;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

   
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                cost[i][j] = 0; 
            } else {
                cost[i][j] = INF; 
            }
        }
    }

    int i, j, k;
    printf("Enter the edges and their cost (use -1 -1 to end):\n");
    while (1) {
        scanf("%d %d %d", &i, &j, &k);
        if (i == -1 || j == -1) {
            break;
        } else {
            cost[i][j] = k;
        }
    }

    all_path(cost, a, n);

    return 0;
}
