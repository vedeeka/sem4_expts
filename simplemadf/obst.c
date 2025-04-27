#include <stdio.h>
#include <limits.h>

#define MAX 20  // maximum number of keys

void OptimalBST(float p[], float q[], int n, float e[MAX][MAX], int root[MAX][MAX]) {
    float w[MAX][MAX];
    int i, j, l, r;
    float t;

    for (i = 1; i <= n+1; i++) {
        e[i][i-1] = q[i-1];
        w[i][i-1] = q[i-1];
    }

    for (l = 1; l <= n; l++) { // l = length of chain
        for (i = 1; i <= n - l + 1; i++) {
            j = i + l - 1;
            e[i][j] = INT_MAX;
            w[i][j] = w[i][j-1] + p[j] + q[j];
            for (r = i; r <= j; r++) {
                t = e[i][r-1] + e[r+1][j] + w[i][j];
                if (t < e[i][j]) {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }
}

void printOBST(int root[MAX][MAX], int i, int j, int parent, char *direction) {
    if (i > j)
        return;

    int r = root[i][j];
    if (parent == -1)
        printf("Root is key %d\n", r);
    else
        printf("Key %d is %s child of key %d\n", r, direction, parent);

    printOBST(root, i, r-1, r, "left");
    printOBST(root, r+1, j, r, "right");
}

int main() {
    int n, i;
    float p[MAX], q[MAX];
    float e[MAX][MAX];
    int root[MAX][MAX];

    printf("Enter number of keys: ");
    scanf("%d", &n);

    printf("Enter probabilities of successful searches (p[1] to p[%d]):\n", n);
    for (i = 1; i <= n; i++)
        scanf("%f", &p[i]);

    printf("Enter probabilities of unsuccessful searches (q[0] to q[%d]):\n", n);
    for (i = 0; i <= n; i++)
        scanf("%f", &q[i]);

    OptimalBST(p, q, n, e, root);

    printf("\nCost of Optimal BST = %.2f\n", e[1][n]);

    printf("\nStructure of Optimal BST:\n");
    printOBST(root, 1, n, -1, "");

    return 0;
}
