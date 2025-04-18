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
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(node->key, key);
    node->left = node->right = NULL;
    return node;
}

struct treeNode *constructT(int r[MAX][MAX], int i, int j) {
    if (i > j) return NULL;
    int rootIdx = r[i][j];
    if (rootIdx == 0) return NULL;
    struct treeNode* root = createN(a[rootIdx-1]);
    root->left = constructT(r, i, rootIdx-1);
    root->right = constructT(r, rootIdx+1, j);
    return root;
}

void printTree(struct treeNode* root, int level, char prefix[], int isLeft) {
    if (root == NULL) return;
    printf("%s", prefix);
    if (level > 0) printf(isLeft ? "├── " : "└── ");
    printf("%s\n", root->key);
    char newPrefix[256];
    strcpy(newPrefix, prefix);
    if (level > 0) strcat(newPrefix, isLeft ? "│   " : "    ");
    printTree(root->left, level + 1, newPrefix, 1);
    printTree(root->right, level + 1, newPrefix, 0);
}

void visualizeTree(int n, int r[MAX][MAX]) {
    struct treeNode* root = constructT(r, 0, n);
    char initialPrefix[1] = "";
    printTree(root, 0, initialPrefix, 0);
}

int Find(int c[MAX][MAX], int i, int j) {
    int min = INF, kmin = i + 1;
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
    for (int i = 0; i <= n; i++) {
        w[i][i] = q[i];
        c[i][i] = 0;
        r[i][i] = 0;
    }
    for (int i = 0; i < n; i++) {
        int j = i + 1;
        w[i][j] = w[i][j-1] + p[j] + q[j];
        c[i][j] = w[i][j] + c[i][i] + c[j][j];
        r[i][j] = j;
    }
    for (int d = 2; d <= n; d++) {
        for (int i = 0; i <= n - d; i++) {
            int j = i + d;
            w[i][j] = w[i][j-1] + p[j] + q[j];
            int kmin = Find(c, i, j);
            r[i][j] = kmin;
            c[i][j] = w[i][j] + c[i][kmin-1] + c[kmin][j];
        }
    }
    printf("\nOptimal cost: %d\n", c[0][n]);
    visualizeTree(n, r);
}

int main() {
    int n, i, p[MAX], q[MAX];
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

    clock_gettime(CLOCK_MONOTONIC, &start);
    OBST(p, q, n);
    clock_gettime(CLOCK_MONOTONIC, &end);

    time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) / 1e6;
    printf("\nTime Taken: %.6f milliseconds\n", time_taken);

    return 0;
}
