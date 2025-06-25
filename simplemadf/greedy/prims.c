#include <stdio.h>
#define MAX 20
#define INF 9999

int cost[MAX][MAX], t[MAX][2], near[MAX];

int Prim(int n) {
    int mincost = INF;
    int k = 1, l = 1;


    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j && cost[i][j] < mincost) {
                mincost = cost[i][j];
                k = i;
                l = j;
            }
        }
    }

    t[1][0] = k;
    t[1][1] = l;
    mincost = cost[k][l];

    for (int i = 1; i <= n; i++) {
        if (cost[i][l] < cost[i][k])
            near[i] = l;
        else
            near[i] = k;
    }

    near[k] = 0;
    near[l] = 0;


    int edgeCount = 1; // already added 1 edge
    for (int i = 2; i <= n - 1; i++) {
        int min = INF;
        int j = -1;

        for (int m = 1; m <= n; m++) {
            if (near[m] != 0 && cost[m][near[m]] < min) {
                min = cost[m][near[m]];
                j = m;
            }
        }

        if (j == -1) {
            // No valid vertex to connect → graph is disconnected
            printf("\nGraph is disconnected. MST not possible for all vertices.\n");
            return mincost;
        }

        t[++edgeCount][0] = j;
        t[edgeCount][1] = near[j];
        mincost += cost[j][near[j]];
        near[j] = 0;

        for (int k = 1; k <= n; k++) {
            if (near[k] != 0 && cost[k][near[k]] > cost[k][j])
                near[k] = j;
        }
    }

    return mincost;
}

int main() {
    int n;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the cost adjacency matrix (%d for INF):\n", INF);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            scanf("%d", &cost[i][j]);
            if (i != j && cost[i][j] == 0)
                cost[i][j] = INF;
        }

    int totalCost = Prim(n);

    printf("\nMinimum Cost Spanning Tree Edges:\n");
    for (int i = 1; i <= n - 1 && t[i][0] != 0 && t[i][1] != 0; i++) {
        printf("Edge %d: (%d, %d)\n", i, t[i][0], t[i][1]);
    }

    printf("Total cost = %d\n", totalCost);
    return 0;
}
