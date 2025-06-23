#include <stdio.h>
#include <string.h>

#define MAX 100

int n;                 // Number of items
int m;                 // Maximum capacity
int p[MAX], w[MAX];    // Profits and Weights
int x[MAX], y[MAX];    // Final and Temporary solution
int fp = 0, fw = 0;    // Final profit and final weight

// Calculate upper bound
float Bound(int cp, int cw, int k) {
    float b = cp;
    int c = cw;
    for (int i = k + 1; i <= n; i++) {
        c += w[i];
        if (c <= m) {
            b += p[i];
        } else {
            b += (1 - (float)(c - m) / w[i]) * p[i];
            return b;
        }
    }
    return b;
}

// Branch and bound (no visualization)
void BKnap(int k, int cp, int cw) {
    if (k > n) {
        if (cp > fp) {
            fp = cp;
            fw = cw;
            for (int j = 1; j <= n; j++)
                x[j] = y[j];
        }
        return;
    }

    // Include item k
    if (cw + w[k] <= m) {
        y[k] = 1;
        BKnap(k + 1, cp + p[k], cw + w[k]);
    }

    // Exclude item k if promising
    if (Bound(cp, cw, k) > fp) {
        y[k] = 0;
        BKnap(k + 1, cp, cw);
    }
}

// Print final solution
void printSolution() {
    printf("Optimal profit: %d\n", fp);
    printf("Optimal weight: %d\n", fw);
    printf("Solution vector:\n");
    for (int i = 1; i <= n; i++)
        printf("%d ", x[i]);
    printf("\n");
}

int main() {
    for (int i = 0; i < MAX; i++) {
        x[i] = 0;
        y[i] = 0;
        p[i] = 0;
        w[i] = 0;
    }

    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter max capacity of knapsack: ");
    scanf("%d", &m);

    printf("Enter profits:\n");
    for (int i = 1; i <= n; i++)
        scanf("%d", &p[i]);

    printf("Enter weights:\n");
    for (int i = 1; i <= n; i++)
        scanf("%d", &w[i]);

    BKnap(1, 0, 0);

    printSolution();

    return 0;
}
