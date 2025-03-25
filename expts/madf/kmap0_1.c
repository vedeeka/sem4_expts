#include <stdio.h>

int n, m; // n = number of items, m = knapsack capacity
int w[10], p[10]; // arrays for weights and profits
int x[10], y[10]; 
int fp = 0, fw = 0;

float max(float a, float b) {
    return (a > b) ? a : b;
}

float Bound(int cp, int cw, int k) {
    float b = cp;
    int c = cw;
    for (int i = k + 1; i <= n; i++) {
        c += w[i];
        if (c <= m)
            b += p[i];
        else {
            b += (float)(m - c + w[i]) / w[i] * p[i];
            break;
        }
    }
    return b;
}

void Bknap(int k, int cp, int cw) {
    if (cw + w[k] <= m) {
        y[k] = 1; // Include the item
        if (k < n) {
            Bknap(k + 1, cp + p[k], cw + w[k]);
        }
        if ((cp + p[k] > fp) && (k == n)) {
            fp = cp + p[k];
            fw = cw + w[k];
            for (int j = 1; j <= n; j++) {
                x[j] = y[j];
            }
        }
    }

    // Generate right child (not including the item)
    if (Bound(cp, cw, k) >= fp) {
        y[k] = 0; // Exclude the item
        if (k < n) {
            Bknap(k + 1, cp, cw);
        }
        if ((cp > fp) && (k == n)) {
            fp = cp;
            fw = cw;
            for (int j = 1; j <= n; j++) {
                x[j] = y[j];
            }
        }
    }
}

int main() {
    printf("Enter number of items: ");
    scanf("%d", &n);
    printf("Enter capacity of knapsack: ");
    scanf("%d", &m);

    printf("Enter weight and profit of each item:\n");
    for (int i = 1; i <= n; i++) {
        printf("Item %d:\n", i);
        printf("Weight: ");
        scanf("%d", &w[i]);
        printf("Profit: ");
        scanf("%d", &p[i]);
    }

    // Initialize arrays
    for (int i = 1; i <= n; i++) {
        x[i] = 0;
        y[i] = 0;
    }

    Bknap(1, 0, 0);

    printf("\nMaximum profit = %d\n", fp);
    printf("Weight of knapsack = %d\n", fw);
    printf("Items included (1=Yes, 0=No):\n");
    for (int i = 1; i <= n; i++) {
        printf("Item %d: %d\n", i, x[i]);
    }

    return 0;
}