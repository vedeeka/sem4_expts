#include <stdio.h>

int G[10][10];  // Adjacency matrix
int x[10];      // Color assignments
int n, m;       // n = number of vertices, m = current number of colors
int found = 0;  // Flag to indicate valid coloring found




void NextValue(int k) {
    int j;
    while (1) {
        x[k] = (x[k] + 1) % (m + 1); // Try next color
        if (x[k] == 0)               // No more colors
            return;
        for (j = 1; j <= n; j++) {
            if (G[k][j] && x[k] == x[j]) // Adjacent vertex same color
                break;
        }
        if (j == n + 1) // Found valid color
            return;
    }
}

// Recursive backtracking function
void mColoring(int k) {
    while (1) {
        NextValue(k); // Try assigning color
        if (x[k] == 0) // No valid color
            return;

        if (k == n) {  // All vertices colored
            found = 1;
            for (int i = 1; i <= n; i++)
                printf("%d ", x[i]);
            printf("\n");
        } else {
            mColoring(k + 1); // Recur for next vertex
        }
    }
}

// Driver code
int main() {
    int i, j, edges, u, v;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    // Initialize graph
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            G[i][j] = 0;

    printf("Enter number of edges: ");
    scanf("%d", &edges);
    printf("Enter edges (u v):\n");
    for (i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        G[u][v] = G[v][u] = 1;
    }

    // Try coloring with increasing number of colors
    for (m = 1; m <= n; m++) {
        for (i = 1; i <= n; i++)
            x[i] = 0; // Reset color assignments

        found = 0;
        printf("\nTrying with %d color(s):\n", m);
        mColoring(1);

        if (found) {
            printf("✅ Chromatic number is: %d\n", m);
            break;
        }
    }

    return 0;
}
