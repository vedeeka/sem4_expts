#include <stdio.h>

int n, G[10][10], X[10];

void NEXTVALUE(int k) {
    int j;
    do {
        X[k] = (X[k] + 1) % (n + 1);
        if (X[k] == 0)
            return;
        if (G[X[k - 1]][X[k]] != 0) {
            for (j = 1; j < k; j++) {
                if (X[j] == X[k])
                    break;
            }
            if (j == k) {
                if ((k < n) || (k == n && G[X[n]][X[1]] != 0))
                    return;
            }
        }
    } while (1);
}

void HAMILTONIAN(int k) {
    do {
        NEXTVALUE(k);
        if (X[k] == 0)
            return;
        if (k == n) {
            printf("Hamiltonian Cycle: ");
            for (int i = 1; i <= n; i++)
                printf("%d ", X[i]);
            printf("%d", X[1]); // Close the cycle
            printf("\n");
        } else {
            HAMILTONIAN(k + 1);
        }
    } while (1);
}

int main() {
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &G[i][j]);
        }
    }

    for (int i = 1; i <= n; i++)
        X[i] = 0;
    X[1] = 1;

    printf("All Hamiltonian cycles are:\n");
    HAMILTONIAN(2);

    return 0;
}
