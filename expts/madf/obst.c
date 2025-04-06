#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 100
#define INF 99999
#define STR_LEN 50

char a[MAX][STR_LEN];

struct treeNode {
    char key[STR_LEN];
    struct treeNode *left;
    struct treeNode *right;
};

struct treeNode *createN(const char *key) {
    struct treeNode *node = (struct treeNode*)malloc(sizeof(struct treeNode));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed in createN\n");
        exit(EXIT_FAILURE);
    }
    strcpy(node->key, key);
    node->left = node->right = NULL;
    return node;
}

// Improved tree construction - Corrected for proper OBST structure
struct treeNode *constructT(int r[MAX][MAX], int i, int j) {
    if (i > j) return NULL;

    int rootIdx = r[i+1][j]; // r matrix is 1-based indexed for keys
    if (rootIdx <= 0 || rootIdx > j) return NULL; // Safety check

    // Create node with proper key - now using rootIdx-1 to access 'a' array
    struct treeNode* root = createN(a[rootIdx-1]);

    // Recursively build left and right subtrees
    root->left = constructT(r, i, rootIdx-1);
    root->right = constructT(r, rootIdx+1, j);

    return root;
}


// Better tree printing function using preorder traversal
void printTree(struct treeNode* root, int level, char prefix[], int isLeft) {
    if (root == NULL) return;
    
    // Print current node with proper indentation and branch symbols
    printf("%s", prefix);
    
    // Show branch connector
    if (level > 0) {
        printf(isLeft ? "├── " : "└── ");
    }
    
    // Print the node value
    printf("%s\n", root->key);
    
    // Prepare prefix for children
    char newPrefix[256]; // Adjust size as needed
    strcpy(newPrefix, prefix);
    
    if (level > 0) {
        // Add vertical line for left child if this is left child
        strcat(newPrefix, isLeft ? "│   " : "    ");
    }
    
    // Process children
    printTree(root->left, level + 1, newPrefix, 1);
    printTree(root->right, level + 1, newPrefix, 0);
}

// Wrapper function for easier use
void displayTree(struct treeNode* root) {
    char initialPrefix[1] = "";
    printTree(root, 0, initialPrefix, 0);
}

// Visualize the tree in a more reliable way
void visualizeTree(int n, int r[MAX][MAX]) {
    printf("\nOptimal Binary Search Tree (Preorder Traversal):\n");
    struct treeNode* root = constructT(r, 0, n); // Pass 0 and n for full range
    char initialPrefix[1] = "";
    printTree(root, 0, initialPrefix, 0);
}


int Find(int c[MAX][MAX], int i, int j) {
    int min = INF;
    int kmin = i + 1;

    for (int k = i + 1; k <= j; k++) {
        int cost = c[i][k-1] + c[k][j];
        if (cost < min) {
            min = cost;
            kmin = k;
        }
    }
    return kmin;
}

void OBST(int p[], int q[], int n) {
    int w[MAX][MAX], c[MAX][MAX], r[MAX][MAX];

    // Initialize for trees with single node
    for (int i = 0; i <= n; i++) {
        w[i][i] = q[i];
        c[i][i] = 0;
        r[i][i] = 0;
    }

    // Initialize for trees with two nodes
    for (int i = 0; i < n; i++) {
        int j = i + 1;
        w[i][j] = w[i][j-1] + p[j] + q[j]; // Correct weight calculation
        c[i][j] = w[i][j] + c[i][i] + c[j][j]; // Correct cost calculation for m=1 (j-i=1)
        r[i][j] = j;
    }

    // Print initial values
    printf("\n\t\t");
    for (int k = 0; k <= n; k++) {
        printf(" k = %-4d  ", k);
    }
    printf("\n-----------------------------------------------------------------------\n");

    // Print j-i = 0 values
    printf("j - i = 0\t");
    for (int i = 0; i <= n; i++) {
        printf("w[%d][%d] = %-4d ", i, i, w[i][i]);
    }
    printf("\n\t\t");
    for (int i = 0; i <= n; i++) {
        printf("c[%d][%d] = %-4d ", i, i, c[i][i]);
    }
    printf("\n\t\t");
    for (int i = 0; i <= n; i++) {
        printf("r[%d][%d] = %-4d ", i, i, r[i][i]);
    }
    printf("\n-----------------------------------------------------------------------\n");

    // Print j-i = 1 values
    printf("j - i = 1\t");
    for (int i = 0; i < n; i++) {
        printf("w[%d][%d] = %-4d ", i, i+1, w[i][i+1]);
    }
    printf("\n\t\t");
    for (int i = 0; i < n; i++) {
        printf("c[%d][%d] = %-4d ", i, i+1, c[i][i+1]);
    }
    printf("\n\t\t");
    for (int i = 0; i < n; i++) {
        printf("r[%d][%d] = %-4d ", i, i+1, r[i][i+1]);
    }
    printf("\n-----------------------------------------------------------------------\n");

    // Compute for trees with more than two nodes
    for (int d = 2; d <= n; d++) {
        printf("j - i = %d\t", d);
        for (int i = 0; i <= n - d; i++) {
            int j = i + d;
            w[i][j] = w[i][j-1] + p[j] + q[j];

            // Find optimal root
            int kmin = Find(c, i, j);
            r[i+1][j] = kmin; // r matrix is 1-based indexed for keys
            c[i][j] = w[i][j] + c[i][kmin-1] + c[kmin][j];

            printf("w[%d][%d] = %-4d ", i, j, w[i][j]);
        }
        printf("\n\t\t");
        for (int i = 0; i <= n - d; i++) {
            int j = i + d;
            printf("c[%d][%d] = %-4d ", i, j, c[i][j]);
        }
        printf("\n\t\t");
        for (int i = 0; i <= n - d; i++) { // Commenting out r matrix print
           int j = i + d;
           printf("r[%d][%d] = %-4d ", i, j, r[i][j]);
        }
        printf("\n-----------------------------------------------------------------------\n");
    }

    printf("\nOptimal cost: %d\n", c[0][n]);

    // Print the tree using the simpler, more reliable method
    visualizeTree(n, r);


}

int main() {
    int n, i;
    int p[MAX], q[MAX];
    struct timespec start, end;
    double time_taken;

    printf("Enter the number of identifiers (n): ");
    scanf("%d", &n);

    printf("\nEnter the identifiers (names) for a1 to a%d: ", n);
    for (i = 0; i < n; i++) {
        scanf("%s", a[i]);
    }

    printf("\nEnter probabilities p[i] for identifiers a1 to a%d: ", n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &p[i]);
    }

    printf("\nEnter probabilities q[i] for i = 0 to %d: ", n);
    for (i = 0; i <= n; i++) {
        scanf("%d", &q[i]);
    }

    printf("\n\n");
    clock_gettime(CLOCK_MONOTONIC, &start);
    OBST(p, q, n);
    clock_gettime(CLOCK_MONOTONIC, &end);

    time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) / 1e6;
    printf("\nTime Taken: %.6f milliseconds\n", time_taken);

    return 0;
}