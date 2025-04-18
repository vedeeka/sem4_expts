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
#include <string.h>

#define MAX_ITEMS 20
#define MAX_PREFIX 1024
#define MAX_SOLUTIONS 100

int n, m;                      // number of items and target sum
int w[MAX_ITEMS];              // array of weights
int x[MAX_ITEMS];              // solution vector
int sol_count = 0;             // solution counter
char sol_labels[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// To store all solutions for printing later
int solutions[MAX_SOLUTIONS][MAX_ITEMS];
int solution_weights[MAX_SOLUTIONS][MAX_ITEMS];
int solution_items[MAX_SOLUTIONS];

// Function to format node information
void formatNode(char* buffer, int s, int k, int r) {
    sprintf(buffer, "[%d,%d,%d]", s, k, r);
    
    // Mark solution nodes
    if (s == m) {
        char solution_mark[10];
        sprintf(solution_mark, " (%c)", sol_labels[sol_count]);
        strcat(buffer, solution_mark);
        
        // Store this solution
        for (int i = 1; i <= n; i++) {
            solutions[sol_count][i] = x[i];
            if (x[i] == 1) {
                solution_weights[sol_count][solution_items[sol_count]] = w[i];
                solution_items[sol_count]++;
            }
        }
        sol_count++;
    }
}

// Function to print tree structure horizontally
void sumOfSubsetsTree(int s, int k, int r, char* prefix) {
    char node_info[64];
    char new_prefix[MAX_PREFIX];
    char branch_prefix[MAX_PREFIX];
    
    // Format current node
    formatNode(node_info, s, k, r);
    
    // Print current node with prefix
    printf("%s%s\n", prefix, node_info);
    
    // Termination or pruning conditions
    if (k > n || s > m || s + r < m) {
        return;
    }
    
    // Calculate prefix for branches
    sprintf(branch_prefix, "%s│", prefix);
    
    // Left branch (include item k)
    if (s + w[k] <= m) {
        // Prepare prefix for child node description
        printf("%s├── x%d=1\n", prefix, k);
        
        // Prepare prefix for next level
        sprintf(new_prefix, "%s│   ", prefix);
        
        // Recursive call for left branch
        x[k] = 1;
        sumOfSubsetsTree(s + w[k], k + 1, r - w[k], new_prefix);
    }
    
    // Right branch (exclude item k)
    if (s + r - w[k] >= m) {
        // Prepare prefix for child node description
        if (s + w[k] <= m) {
            printf("%s└── x%d=0\n", prefix, k);
            sprintf(new_prefix, "%s    ", prefix);
        } else {
            printf("%s├── x%d=0\n", prefix, k);
            sprintf(new_prefix, "%s│   ", prefix);
        }
        
        // Recursive call for right branch
        x[k] = 0;
        sumOfSubsetsTree(s, k + 1, r - w[k], new_prefix);
    }
}

// Function to print all solutions
void printAllSolutions() {
    printf("\n\nFinal Solutions:\n");
    printf("=================\n");
    
    if (sol_count == 0) {
        printf("No solutions found for target sum %d\n", m);
        return;
    }
    
    for (int i = 0; i < sol_count; i++) {
        printf("Solution %c: {", sol_labels[i]);
        int first = 1;
        
        for (int j = 1; j <= n; j++) {
            if (solutions[i][j] == 1) {
                if (!first) {
                    printf(", ");
                }
                printf("%d", w[j]);
                first = 0;
            }
        }
        
        printf("} = %d\n", m);
    }
}

int main() {
    // Initialize solution counts and arrays
    sol_count = 0;
    for (int i = 0; i < MAX_SOLUTIONS; i++) {
        solution_items[i] = 0;
        for (int j = 0; j < MAX_ITEMS; j++) {
            solutions[i][j] = 0;
            solution_weights[i][j] = 0;
        }
    }
    
    printf("Enter number of items: ");
    scanf("%d", &n);
    
    printf("Enter the weights: ");
    int total = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w[i]);
        total += w[i];
    }
    
    printf("Enter the target sum: ");
    scanf("%d", &m);
    
    printf("\nSum of Subsets Tree (Target = %d):\n\n", m);
    
    // Initialize solution array
    for (int i = 1; i <= n; i++) {
        x[i] = 0;
    }
    
    // Start with root node
    char root_info[64];
    formatNode(root_info, 0, 1, total);
    printf("%s\n", root_info);
    
    // Left branch from root (include first item)
    if (w[1] <= m) {
        printf("├── x1=1\n");
        x[1] = 1;
        sumOfSubsetsTree(w[1], 2, total - w[1], "│   ");
    }
    
    // Right branch from root (exclude first item)
    printf("└── x1=0\n");
    x[1] = 0;
    sumOfSubsetsTree(0, 2, total - w[1], "    ");
    
    // Print all solutions at the end
    printAllSolutions();
    
    return 0;
}