#include <stdio.h>
#define MAX 10
#define INF 9999

// Function to display the intermediate near[] table (Optional)
void displayTable(int n, int near[], int cost[][MAX], int step) {
    printf("\nStep %d - Near Array:\n", step);
    for (int i = 1; i <= n; i++) {
        if (near[i] != 0)
            printf("near[%d] = %d\n", i, near[i]);
        else
            printf("near[%d] = 0 (in MST)\n", i);
    }
}

// Prim’s Algorithm function
int prims(int t[MAX][2], int size, int cost[MAX][MAX], int near[MAX]) {
    int i, j, k, l, min = INF;

    // Step 1: Find the minimum cost edge
    for (i = 1; i <= size; i++) {
        for (j = i + 1; j <= size; j++) {
            if (cost[i][j] < min) {
                min = cost[i][j];
                k = i;
                l = j;
            }
        }
    }

    int mincost = cost[k][l];
    t[0][0] = k;
    t[0][1] = l;

    for (i = 1; i <= size; i++) {
        if (cost[i][l] < cost[i][k])
            near[i] = l;
        else
            near[i] = k;
    }
    near[k] = 0;
    near[l] = 0;

    for (i = 1; i < size - 1; i++) {
        int min = INF;
        int next = 0;

        for (j = 1; j <= size; j++) {
            if (near[j] != 0 && cost[j][near[j]] < min) {
                min = cost[j][near[j]];
                next = j;
            }
        }

        t[i][0] = next;
        t[i][1] = near[next];
        mincost += cost[next][near[next]];
        near[next] = 0;

        for (j = 1; j <= size; j++) {
            if (near[j] != 0 && cost[j][near[j]] > cost[j][next])
                near[j] = next;
        }

        displayTable(size, near, cost, i);
    }

    return mincost;
}

int main() {
    int n, cost[MAX][MAX], t[MAX][2], near[MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter the cost adjacency matrix (use %d for no edge):\n", INF);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &cost[i][j]);

    int totalCost = prims(t, n, cost, near);

    printf("\nMinimum Spanning Tree Edges:\n");
    for (int i = 0; i < n - 1; i++)
        printf("Edge %d: (%d, %d)\n", i + 1, t[i][0], t[i][1]);

    printf("Total cost of MST: %d\n", totalCost);

    return 0;
}
