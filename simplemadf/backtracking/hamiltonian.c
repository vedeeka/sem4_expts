#include <stdio.h>

int G[10][10];  
int x[10];     
int n;         

void NextValue(int k) {
    int j;
    while (1) {
        x[k] = (x[k] + 1) % (n + 1); 
        if (x[k] == 0)
            return;

        if (G[x[k - 1]][x[k]] != 0) { 
            for (j = 1; j < k; j++) {
                if (x[j] == x[k])   
                    break;
            }

            if (j == k) { 
                if ((k < n) || (k == n && G[x[n]][x[1]] != 0))
                    return;
            }
        }
    }
}

void Hamiltonian(int k) {
    while (1) {
        NextValue(k);
        if (x[k] == 0)
            return;

        if (k == n) {
            for (int i = 1; i <= n; i++)
                printf("%d ", x[i]);
            printf("%d\n", x[1]); 
        } else {
            Hamiltonian(k + 1);
        }
    }
}

int main() {
    int i, j, edges, u, v;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

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

    for (i = 1; i <= n; i++)
        x[i] = 0;

    x[1] = 1; // Start from vertex 1

    printf("Hamiltonian cycles:\n");
    Hamiltonian(2);

    return 0;
}
