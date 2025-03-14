#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int order[MAX];

void sort_pw(int n, int profit[], int weight[]) {
    float pw[n];
    for (int i = 0; i < n; i++) {
        order[i] = i;
        pw[i] = (float)profit[i] / weight[i];
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (pw[j] < pw[j + 1]) {
                float temp = pw[j]; pw[j] = pw[j + 1]; pw[j + 1] = temp;
                int t = order[j]; order[j] = order[j + 1]; order[j + 1] = t;
            }
        }
    }
}

void knapsack(int n, int weight[], int profit[], int capacity) {
    float x[MAX] = {0.0}, total_profit = 0.0;
    int u = capacity;

    sort_pw(n, profit, weight);
    printf("Solution: ");
    for (int i = 0; i < n && weight[order[i]] <= u; i++) {
        x[order[i]] = 1.0;
        total_profit += profit[order[i]];
        u -= weight[order[i]];
    }
    if (u > 0) {
        int i = 0;
        while (i < n && weight[order[i]] <= u) i++;
        if (i < n) {
            x[order[i]] = (float)u / weight[order[i]];
            total_profit += profit[order[i]] * x[order[i]];
        }
    }
    for (int i = 0; i < n; i++) printf("%.2f ", x[i]);
    printf("\nTotal Profit: %.2f\n", total_profit);
}

void subset_sum(int index, int sum, int n, int w[], int target, int x[]) {
    if (sum == target) {
        printf("Solution: ");
        for (int i = 0; i < n; i++) printf("%d ", x[i]);
        printf("\n");
        return;
    }
    if (index == n || sum > target) return;
    x[index] = 1;
    subset_sum(index + 1, sum + w[index], n, w, target, x);
    x[index] = 0;
    subset_sum(index + 1, sum, n, w, target, x);
}

int main() {
    int n, capacity, choice, profit[MAX], weight[MAX], target, x[MAX] = {0};
    while (1) {
        printf("\n1. Knapsack Problem\n2. Subset Sum Problem\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);
        if (choice == 3) break;
        if (choice == 1) {
            printf("Enter number of items: "); scanf("%d", &n);
            printf("Enter knapsack capacity: "); scanf("%d", &capacity);
            printf("Enter profits: "); for (int i = 0; i < n; i++) scanf("%d", &profit[i]);
            printf("Enter weights: "); for (int i = 0; i < n; i++) scanf("%d", &weight[i]);
            knapsack(n, weight, profit, capacity);
            subset_sum(0, 0, n, weight, target, x);
        }  else {
            printf("Invalid choice!\n");
        }
    }
    return 0;
}
