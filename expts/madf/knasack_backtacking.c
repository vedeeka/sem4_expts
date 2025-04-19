// #include <stdio.h>

// #define MAX 100

// int n;                 // Number of items
// int m;                 // Maximum capacity
// int p[MAX], w[MAX];    // Profits and Weights
// int x[MAX], y[MAX];    // Final and Temporary solution
// int fp = 0, fw = 0;    // Final profit and final weight

// float Bound(int cp, int cw, int k) {
//     float b = cp;
//     int c = cw;
//     for (int i = k + 1; i <= n; i++) {
//         c += w[i];
//         if (c <= m) {
//             b += p[i];
//         } else {
//             b += (1 - (float)(c - m) / w[i]) * p[i];
//             return b;
//         }
//     }
//     return b;
// }

// void BKnap(int k, int cp, int cw) {
//     if (cw + w[k] <= m) {
//         y[k] = 1;
//         if (k < n)
//             BKnap(k + 1, cp + p[k], cw + w[k]);
//         else if (cp + p[k] > fp) {
//             fp = cp + p[k];
//             fw = cw + w[k];
//             for (int j = 1; j <= n; j++)
//                 x[j] = y[j];
//         }
//     }

//     if (Bound(cp, cw, k) > fp) {
//         y[k] = 0;
//         if (k < n)
//             BKnap(k + 1, cp, cw);
//         else if (cp > fp) {
//             fp = cp;
//             fw = cw;
//             for (int j = 1; j <= n; j++)
//                 x[j] = y[j];
//         }
//     }
// }

// int main() {
//     printf("Enter number of items: ");
//     scanf("%d", &n);

//     printf("Enter max capacity of knapsack: ");
//     scanf("%d", &m);

//     printf("Enter profits:\n");
//     for (int i = 1; i <= n; i++)
//         scanf("%d", &p[i]);

//     printf("Enter weights:\n");
//     for (int i = 1; i <= n; i++)
//         scanf("%d", &w[i]);

//     BKnap(1, 0, 0);

//     printf("\nOptimal profit: %d\n", fp);
//     printf("Optimal weight: %d\n", fw);
//     printf("Solution vector (0 = exclude, 1 = include):\n");
//     for (int i = 1; i <= n; i++)
//         printf("%d ", x[i]);
//     printf("\n");

//     return 0;
// }
#include <stdio.h>
#include <string.h>

#define MAX 100
#define MAX_PREFIX 1024

int n;                 // Number of items
int m;                 // Maximum capacity
int p[MAX], w[MAX];    // Profits and Weights
int x[MAX], y[MAX];    // Final and Temporary solution
int fp = 0, fw = 0;    // Final profit and final weight
int solution_found = 0;

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

// Function to print node information
void formatNode(char* buffer, int k, int cp, int cw, float bound) {
    sprintf(buffer, "[k=%d, p=%d, w=%d, bound=%.2f]", k, cp, cw, bound);
    
    // Mark solution nodes
    if (k > n && cp > fp) {
        strcat(buffer, " (*)");
    }
}

// Branch and bound with tree visualization
void BKnap(int k, int cp, int cw, char* prefix) {
    char node_info[128];
    char new_prefix[MAX_PREFIX];
    float bound = Bound(cp, cw, k);
    
    // Format and print current node
    formatNode(node_info, k, cp, cw, bound);
    printf("%s%s\n", prefix, node_info);
    
    // Base case - reached beyond last item
    if (k > n) {
        if (cp > fp) {
            fp = cp;
            fw = cw;
            for (int j = 1; j <= n; j++)
                x[j] = y[j];
            solution_found = 1;
        }
        return;
    }
    
    // Try including the item if possible
    if (cw + w[k] <= m) {
        printf("%s├── x%d=1 (%d)\n", prefix, k, k);
        y[k] = 1;
        sprintf(new_prefix, "%s│   ", prefix);
        BKnap(k + 1, cp + p[k], cw + w[k], new_prefix);
    }
    
    // Try excluding the item (if promising)
    if (Bound(cp, cw, k) > fp) {
        if (cw + w[k] <= m) {
            printf("%s└── x%d=0 (%d)\n", prefix, k, k);
            sprintf(new_prefix, "%s    ", prefix);
        } else {
            printf("%s├── x%d=0 (%d)\n", prefix, k, k);
            sprintf(new_prefix, "%s│   ", prefix);
        }
        
        y[k] = 0;
        BKnap(k + 1, cp, cw, new_prefix);
    } else {
        printf("%s└── Pruned: bound %.2f <= current best %d\n", prefix, bound, fp);
    }
}

// Print final solution
void printSolution() {
    printf("\n=================================\n");
    printf("Final Knapsack Solution:\n");
    printf("=================================\n");
    
    if (!solution_found) {
        printf("No valid solution found.\n");
        return;
    }
    
    printf("Optimal profit: %d\n", fp);
    printf("Optimal weight: %d\n", fw);
    printf("Solution vector (0 = exclude, 1 = include):\n");
    for (int i = 1; i <= n; i++)
        printf("%d ", x[i]);
    printf("\n\n");
    


}

int main() {
    // Initialize all values
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
    
    printf("\nBranch and Bound Knapsack Search Tree:\n\n");
    
    // Start with root node
    printf("[k=1, p=0, w=0, bound=%.2f]\n", Bound(0, 0, 1));
    
    // Start the branch and bound algorithm with visualization
    BKnap(1, 0, 0, "");
    
    // Print final solution
    printSolution();
    
    return 0;
}