// #include <stdio.h>

// int n, G[10][10], X[10];

// void NEXTVALUE(int k) {
//     int j;
//     do {
//         X[k] = (X[k] + 1) % (n + 1);
//         if (X[k] == 0)
//             return;
//         if (G[X[k - 1]][X[k]] != 0) {
//             for (j = 1; j < k; j++) {
//                 if (X[j] == X[k])
//                     break;
//             }
//             if (j == k) {
//                 if ((k < n) || (k == n && G[X[n]][X[1]] != 0))
//                     return;
//             }
//         }
//     } while (1);
// }

// void HAMILTONIAN(int k) {
//     do {
//         NEXTVALUE(k);
//         if (X[k] == 0)
//             return;
//         if (k == n) {
//             printf("Hamiltonian Cycle: ");
//             for (int i = 1; i <= n; i++)
//                 printf("%d ", X[i]);
//             printf("%d", X[1]); // Close the cycle
//             printf("\n");
//         } else {
//             HAMILTONIAN(k + 1);
//         }
//     } while (1);
// }

// int main() {
//     printf("Enter the number of vertices: ");
//     scanf("%d", &n);

//     printf("Enter the adjacency matrix:\n");
//     for (int i = 1; i <= n; i++) {
//         for (int j = 1; j <= n; j++) {
//             scanf("%d", &G[i][j]);
//         }
//     }

//     for (int i = 1; i <= n; i++)
//         X[i] = 0;
//     X[1] = 1;

//     printf("All Hamiltonian cycles are:\n");
//     HAMILTONIAN(2);

//     return 0;
// }
#include <stdio.h>
#include <string.h>

#define MAX_VERTICES 10
#define MAX_PREFIX 1024
#define MAX_CYCLES 100

int n, G[10][10], X[10];
int cycle_count = 0;
char cycle_labels[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// To store all cycles for printing later
int cycles[MAX_CYCLES][MAX_VERTICES+1];

// Print the current state of the path as a node
void printNode(char* buffer, int k) {
    buffer[0] = '[';
    int len = 1;

    for (int i = 1; i <= k; i++) {
        len += sprintf(buffer + len, "%d", X[i]);
        if (i < k) {
            buffer[len++] = ',';
        }
    }

    buffer[len++] = ']';

    // Mark solution nodes
    if (k == n && G[X[n]][X[1]] != 0) {
        sprintf(buffer + len, " (%c)", cycle_labels[cycle_count]);
    } else {
        buffer[len] = '\0';
    }
}

// Original NEXTVALUE function
void NEXTVALUE(int k) {
    int j;
    do {
        X[k] = (X[k] + 1) % (n + 1);
        if (X[k] == 0)
            return;
        if (G[X[k - 1]][X[k]] != 0) {
            for (j = 1; j < k; j++) {
                if (X[j] == X[k])
                    break;
            }
            if (j == k) {
                if ((k < n) || (k == n && G[X[n]][X[1]] != 0))
                    return;
            }
        }
    } while (1);
}

// Modified HAMILTONIAN function to print tree structure
void HAMILTONIAN(int k, char* prefix) {
    char node_info[64];
    char new_prefix[MAX_PREFIX];

    do {
        NEXTVALUE(k);
        if (X[k] == 0)
            return;

        if (k < n) {
            printf("%s├── v%d=%d\n", prefix, k, X[k]);
            sprintf(new_prefix, "%s│   ", prefix);
        } else {
            printf("%s└── v%d=%d\n", prefix, k, X[k]);
            sprintf(new_prefix, "%s    ", prefix);
        }

        // Print the current node
        printNode(node_info, k);
        printf("%s%s\n", new_prefix, node_info);

        if (k == n && G[X[n]][X[1]] != 0) {
            // This is a solution, store it for final output
            for (int i = 1; i <= n; i++) {
                cycles[cycle_count][i] = X[i];
            }
            cycles[cycle_count][n+1] = X[1]; // Close the cycle
            cycle_count++;
        } else {
            // Continue building the path
            HAMILTONIAN(k + 1, new_prefix);
        }
    } while (1);
}

// Function to print all cycles
void printAllCycles() {
    printf("\n\nFinal Hamiltonian Cycles:\n");
    printf("=========================\n");

    if (cycle_count == 0) {
        printf("No Hamiltonian cycles found\n");
        return;
    }

    for (int i = 0; i < cycle_count; i++) {
        printf("Hamiltonian Cycle %c: ", cycle_labels[i]);
        for (int j = 1; j <= n; j++) {
            printf("%d ", cycles[i][j]);
        }
        printf("%d", cycles[i][1]); // Close the cycle
        printf("\n");
    }
}

int main() {
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &G[i][j]);
        }
    }

    // Initialize solution vector
    for (int i = 1; i <= n; i++)
        X[i] = 0;
    X[1] = 1; // Start with vertex 1

    printf("\nHamiltonian Cycle Search Tree:\n\n");

    // Start with root node
    char root_info[64];
    printNode(root_info, 1);
    printf("%s\n", root_info);

    // Build tree from vertex 2 onwards
    HAMILTONIAN(2, "");

    // Print all cycles at the end
    printAllCycles();

    return 0;
}
