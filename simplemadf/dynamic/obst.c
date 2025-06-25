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
void OBST(float p[], float q[], int n) {
    for (int i = 0; i < n; i++) {
        w[i][i] = q[i];
        c[i][i] = 0;
        r[i][i] = 0;
        w[i][i + 1] = q[i] + q[i + 1] + p[i + 1];
        c[i][i + 1] = q[i] + q[i + 1] + p[i + 1];
        r[i][i + 1] = i + 1;
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
        }
    }

    printf("Minimum cost: %.2f\n", c[0][n]);
    printf("Total weight: %.2f\n", w[0][n]);
    printf("Root of OBST: %d\n", r[0][n]);
}
int main() {
    int n = 5;
    float p[] = {0,5, 6, 4, 3, 7};   // p[1..n]
    float q[] = {7,6,5,4,3,7}; // q[0..n]

    OBST(p, q, n);
    return 0;
}
