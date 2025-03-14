#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int order[MAX], x[MAX];

// Function to sort items by profit/weight ratio
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

// Function to find all subsets of items that fit in the knapsack
void knapsack_all_solutions(int index, int n, int weight[], int profit[], int capacity, int current_weight, int current_profit) {
    if (current_weight <= capacity) {
        printf("\nSolution: ");
        for (int i = 0; i < n; i++) printf("%d ", x[i]);
        printf("\nTotal Profit: %d\n", current_profit);
    }
    if (index == n) return;
    
    // Include current item if it fits
    if (current_weight + weight[index] <= capacity) {
        x[index] = 1;
        knapsack_all_solutions(index + 1, n, weight, profit, capacity, current_weight + weight[index], current_profit + profit[index]);
        x[index] = 0;
    }

    // Exclude current item and move to next
    knapsack_all_solutions(index + 1, n, weight, profit, capacity, current_weight, current_profit);
}

// Function to find all subsets that sum to target (Subset Sum Problem)
void subset_sum(int index, int sum, int n, int w[], int target) {
    if (sum == target) {
        printf("\nSubset Sum Solution: ");
        for (int i = 0; i < n; i++) printf("%d ", x[i]);
        printf("\n");
        return;
    }
    if (index == n || sum > target) return;
    
    x[index] = 1;
    subset_sum(index + 1, sum + w[index], n, w, target);
    x[index] = 0;
    subset_sum(index + 1, sum, n, w, target);
}

int main() {
    int n, capacity, profit[MAX], weight[MAX], target;

    // Knapsack Problem
    printf("Enter number of items: "); scanf("%d", &n);
    printf("Enter knapsack capacity: "); scanf("%d", &capacity);
    printf("Enter profits: "); for (int i = 0; i < n; i++) scanf("%d", &profit[i]);
    printf("Enter weights: "); for (int i = 0; i < n; i++) scanf("%d", &weight[i]);

    printf("\nAll Knapsack Solutions:\n");
    knapsack_all_solutions(0, n, weight, profit, capacity, 0, 0);

    // Subset Sum Problem
    printf("\nEnter number of elements: "); scanf("%d", &n);
    printf("Enter elements: "); for (int i = 0; i < n; i++) scanf("%d", &weight[i]);
    printf("Enter target sum: "); scanf("%d", &target);

    printf("\nAll Subset Sum Solutions:\n");
    subset_sum(0, 0, n, weight, target);

    return 0;
}
