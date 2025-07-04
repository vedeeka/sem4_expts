#include <stdio.h>
#include <limits.h>

#define MAX 100

float c[MAX][MAX];  // Cost matrix
float w[MAX][MAX];  // Weight matrix
int r[MAX][MAX];    // Root matrix

// Function to find the best root in range
int Find(int i, int j) {
    float min = 1e9;
    int l = -1;

    for (int m = r[i][j - 1]; m <= r[i + 1][j]; m++) {
        float cost = c[i][m - 1] + c[m][j];
        if (cost < min) {
            min = cost;
            l = m;
        }
    }

    return l;
}

// OBST algorithm
void OBST(int p[], int q[], int n) {
    for (int i = 0; i < n; i++) {
        w[i][i] = q[i];
        c[i][i] = 0;
        r[i][i] = 0;
        w[i][i + 1] = q[i] + q[i + 1] + p[i + 1];
        c[i][i + 1] = q[i] + q[i + 1] + p[i + 1];
        r[i][i + 1] = i + 1;

        printf("Initial w[%d][%d] = %.2f, c[%d][%d] = %.2f, r = %d\n",
               i, i + 1, w[i][i + 1], i, i + 1, c[i][i + 1], r[i][i + 1]);
    }

    w[n][n] = q[n];
    c[n][n] = 0;
    r[n][n] = 0;

    for (int m = 2; m <= n; m++) {
        for (int i = 0; i <= n - m; i++) {
            int j = i + m;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            int k = Find(i, j);
            c[i][j] = w[i][j] + c[i][k - 1] + c[k][j];
            r[i][j] = k;


            printf("Subtree (%d,%d): w=%.2f, root=%d, cost=%.2f\n",
                   i, j, w[i][j], r[i][j], c[i][j]);
        }
    }

    printf("Minimum cost: %.2f\n", c[0][n]);
    printf("Total weight: %.2f\n", w[0][n]);
    printf("Root of OBST: %d\n", r[0][n]);
}

int main() {
    int n;
    int p[MAX], q[MAX];

    printf("Enter number of keys: ");
    scanf("%d", &n);

    printf("Enter success probabilities p[1..%d]:\n", n);
    p[0] = 0;  // dummy to align indices
    for (int i = 1; i <= n; i++) {
      
        scanf("%d", &p[i]);
    }

    printf("Enter failure probabilities q[0..%d]:\n", n);
    for (int i = 0; i <= n; i++) {
       
        scanf("%d", &q[i]);
    }

    OBST(p, q, n);
    return 0;
}
