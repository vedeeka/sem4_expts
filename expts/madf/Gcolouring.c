

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 10
#define MAX_COLORS 10
#define MAX_SOLUTIONS 100
#define MAX_TREE_NODES 1000

int n, m; // n = number of vertices, m = number of colors
int G[MAX_VERTICES+1][MAX_VERTICES+1], x[MAX_VERTICES+1];
int solutionCount = 0;
int solutions[MAX_SOLUTIONS][MAX_VERTICES+1];

// Structure to represent a node in the state space tree
typedef struct Node {
    int vertex;         // Which vertex this node represents (1 to n)
    int color;          // Color assigned (1 to m or 0 for initial)
    int valid;          // 1 if valid assignment, 0 if invalid (pruned)
    int childCount;     // Number of children
    struct Node* children[MAX_COLORS+1]; // Children nodes
} Node;

Node* createNode(int vertex, int color) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->color = color;
    newNode->valid = 1;  // Initially valid
    newNode->childCount = 0;
    return newNode;
}

// Root of the state space tree
Node* root;

// Function to check if a color assignment is valid
int isValid(int vertex, int color) {
    for (int j = 1; j <= n; j++) {
        if (G[vertex][j] != 0 && color == x[j])
            return 0;
    }
    return 1;
}

// Build the state space tree and find solutions
void buildStateSpaceTree(Node* node, int k) {
    if (k > n) {
        // Found a solution
        for (int i = 1; i <= n; i++) {
            solutions[solutionCount][i] = x[i];
        }
        solutionCount++;
        return;
    }
    
    // Try all colors for vertex k
    for (int c = 1; c <= m; c++) {
        x[k] = c;
        
        // Create a child node for this assignment
        Node* child = createNode(k, c);
        
        if (isValid(k, c)) {
            // Valid assignment, continue building tree
            node->children[node->childCount++] = child;
            
            // Recursively build for next vertex
            buildStateSpaceTree(child, k + 1);
        } else {
            // Invalid assignment, mark as pruned
            child->valid = 0;
            node->children[node->childCount++] = child;
        }
        
        // Backtrack
        x[k] = 0;
    }
}

// Print the state space tree using ASCII art
void printTreeNode(Node* node, int depth, char* prefix, int isLast) {
    if (node == NULL) return;
    
    char newPrefix[1000];
    printf("%s", prefix);
    
    if (node->vertex == 0) {
        // Root node
        printf("Root\n");
    } else {
        if (isLast) {
            printf("└── ");
            sprintf(newPrefix, "%s    ", prefix);
        } else {
            printf("├── ");
            sprintf(newPrefix, "%s│   ", prefix);
        }
        
        if (node->valid) {
            printf("x%d=%d\n", node->vertex, node->color);
        } else {
            printf("x%d=%d (pruned - invalid)\n", node->vertex, node->color);
        }
    }
    
    // Print children
    for (int i = 0; i < node->childCount; i++) {
        printTreeNode(node->children[i], depth + 1, newPrefix, i == node->childCount - 1);
    }
}

// Print solutions in the format shown in the image
void printSolutions() {
    printf("\nSolutions (S/n):\n");
    for (int s = 0; s < solutionCount; s++) {
        printf("S%d => ", s+1);
        for (int i = 1; i <= n; i++) {
            printf("%d", solutions[s][i]);
            if (i < n) printf(" - ");
        }
        printf("\n");
    }
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    
    printf("Enter the adjacency matrix:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &G[i][j]);
        }
    }
    
    printf("Enter number of colors: ");
    scanf("%d", &m);
    
    // Initialize
    for (int i = 1; i <= n; i++) {
        x[i] = 0;
    }
    
    // Create root of state space tree
    root = createNode(0, 0);  // Root has no vertex or color
    
    // Build the tree
    buildStateSpaceTree(root, 1);
    
    // Print the state space tree
    printf("\nState Space Tree:\n");
    printTreeNode(root, 0, "", 1);
    
    // Print solutions
    printSolutions();
    
    return 0;



}
// #include <stdio.h>

// int n, m; // n = number of vertices, m = number of colors
// int G[10][10], x[10];

// void NextValue(int k) {
//     int j;
//     do {
//         x[k] = (x[k] + 1) % (m + 1);
//         if (x[k] == 0)
//             return;

//         for (j = 1; j <= n; j++) {
//             if (G[k][j] != 0 && x[k] == x[j])
//                 break;
//         }

//         if (j == n + 1)
//             return;
//     } while (1);
// }

// void mColoring(int k) {
//     do {
//         NextValue(k);
//         if (x[k] == 0)
//             return;

//         if (k == n) {
//             printf("Solution: ");
//             for (int i = 1; i <= n; i++)
//                 printf("%d ", x[i]);
//             printf("\n");
//         } else {
//             mColoring(k + 1);
//         }
//     } while (1);
// }

// int main() {
//     printf("Enter number of vertices: ");
//     scanf("%d", &n);

//     printf("Enter the adjacency matrix:\n");
//     for (int i = 1; i <= n; i++) {
//         for (int j = 1; j <= n; j++) {
//             scanf("%d", &G[i][j]);
//         }
//     }

//     printf("Enter number of colors: ");
//     scanf("%d", &m);

//     for (int i = 1; i <= n; i++)
//         x[i] = 0;

//     printf("All possible solutions are:\n");
//     mColoring(1);

//     return 0;
// }
