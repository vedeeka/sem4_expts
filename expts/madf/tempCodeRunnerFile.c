// #include <stdio.h>

// int n, m; // number of items and target sum
// int w[10], x[10]; // array of weights and solution array

// void printSubset() {
//     printf("Subset found: ");
//     for (int i = 1; i <= n; i++) {
//         if (x[i] == 1)
//             printf("%d ", w[i]);
//     }
//     printf("\n");
// }

// void sumOfSubsets(int s, int k, int r) {
//     x[k] = 1; // generate left child (include item k)

//     if (s + w[k] == m) {
//         printSubset();
//     } else if (s + w[k] + w[k + 1] <= m) {
//         sumOfSubsets(s + w[k], k + 1, r - w[k]);
//     }

//     // generate right child (exclude item k) and check feasibility
//     if ((s + r - w[k] >= m) && (s + w[k + 1] <= m)) {
//         x[k] = 0;
//         sumOfSubsets(s, k + 1, r - w[k]);
//     }
// }

// int main() {
//     printf("Enter number of items: ");
//     scanf("%d", &n);

//     printf("Enter the weights in non-decreasing order: ");
//     int sum = 0;
//     for (int i = 1; i <= n; i++) {
//         scanf("%d", &w[i]);
//         sum += w[i];
//     }

//     printf("Enter the target sum: ");
//     scanf("%d", &m);

//     printf("Subsets with sum %d are:\n", m);
//     sumOfSubsets(0, 1, sum);

//     return 0;
// }


#include <stdio.h>

int n, m; // number of items and target sum
int w[10], x[10]; // array of weights and solution array
int node_count = 0; // to track node IDs

// Utility function to compute remaining sum
int computeRemainingSum(int k) {
    int remaining = 0;
    for (int i = k; i <= n; i++) {
        remaining += w[i];
    }
    return remaining;
}

// Print a node in the format [value,level,remaining]
void printNode(int s, int k, int r) {
    printf("[%d,%d,%d]", s, k, r);
}

// Function to print node connections with proper indentation
void printConnection(int depth, int xk_value) {
    printf("\n");
    for (int i = 0; i < depth; i++) {
        printf("        "); // Adjust spacing for tree layout
    }
    printf("x%d=%d ", k, xk_value);
}

void printSubset() {
    printf("(");
    for (int i = 1; i <= n; i++) {
        printf("%d", x[i]);
        if (i < n) printf(",");
    }
    printf(") Solution Found!");
}

void sumOfSubsets(int s, int k, int r, int depth) {
    // Print current node
    printNode(s, k, r);
    
    // If we've assigned all items
    if (k > n) {
        if (s == m) {
            printf(" ");
            printSubset();
        }
        return;
    }
    
    // Include item k (left child)
    if (s + w[k] <= m) { // Feasibility check
        x[k] = 1;
        printConnection(depth, 1);
        sumOfSubsets(s + w[k], k + 1, r - w[k], depth + 1);
    }
    
    // Exclude item k (right child)
    if (s + r - w[k] >= m) { // Promising check
        x[k] = 0;
        printConnection(depth, 0);
        sumOfSubsets(s, k + 1, r - w[k], depth + 1);
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

    printf("\nDecision Tree for Sum of Subsets (Target = %d):\n\n", m);
    printf("[0,1,%d]", sum);  // Root node
    
    // Initialize solution array
    for (int i = 1; i <= n; i++) {
        x[i] = 0;
    }
    
    // Start the tree from level 1
    printf("\nx1=1 ");
    x[1] = 1;
    sumOfSubsets(w[1], 2, sum - w[1], 1);
    
    printf("\nx1=0 ");
    x[1] = 0;
    sumOfSubsets(0, 2, sum - w[1], 1);
    
    return 0;
}