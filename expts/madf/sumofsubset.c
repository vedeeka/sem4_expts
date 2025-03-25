#include <stdio.h>

int n, m; // number of items and target sum
int w[10], x[10]; // array of weights and solution array

void printSubset() {
    printf("Subset found: ");
    for (int i = 1; i <= n; i++) {
        if (x[i] == 1)
            printf("%d ", w[i]);
    }
    printf("\n");
}

void sumOfSubsets(int s, int k, int r) {
    x[k] = 1; // generate left child (include item k)

    if (s + w[k] == m) {
        printSubset();
    } else if (s + w[k] + w[k + 1] <= m) {
        sumOfSubsets(s + w[k], k + 1, r - w[k]);
    }

    // generate right child (exclude item k) and check feasibility
    if ((s + r - w[k] >= m) && (s + w[k + 1] <= m)) {
        x[k] = 0;
        sumOfSubsets(s, k + 1, r - w[k]);
    }
}

int main() {
    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter the weights in non-decreasing order: ");
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w[i]);
        sum += w[i];
    }

    printf("Enter the target sum: ");
    scanf("%d", &m);

    printf("Subsets with sum %d are:\n", m);
    sumOfSubsets(0, 1, sum);

    return 0;
}