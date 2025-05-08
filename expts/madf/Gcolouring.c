#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_VERTICES 10
#define MAX_COLORS 10
#define MAX_SOLUTIONS 100
#define MAX_TREE_NODES 1000
int n, m;
int G[MAX_VERTICES+1][MAX_VERTICES+1], x[MAX_VERTICES+1];
int solutionCount = 0;
int solutions[MAX_SOLUTIONS][MAX_VERTICES+1];
int chromatic_number = -1;

typedef struct Node {
    int vertex;
    int color;
    int valid;
    int childCount;
    struct Node* children[MAX_COLORS+1];
} Node;

Node* createNode(int vertex, int color) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->color = color;
    newNode->valid = 1;
    newNode->childCount = 0;
    return newNode;
}

Node* root;

int isValid(int vertex, int color) {
    for (int j = 1; j <= n; j++) {
        if (G[vertex][j] != 0 && color == x[j])
            return 0;
    }
    return 1;
}

void buildStateSpaceTree(Node* node, int k) {
    if (k > n) {
        for (int i = 1; i <= n; i++) {
            solutions[solutionCount][i] = x[i];
        }
        solutionCount++;
        return;
    }
    for (int c = 1; c <= m; c++) {
        x[k] = c;
        Node* child = createNode(k, c);
        if (isValid(k, c)) {
            node->children[node->childCount++] = child;
            buildStateSpaceTree(child, k + 1);
        } else {
            child->valid = 0;
            node->children[node->childCount++] = child;
        }
        x[k] = 0;
    }
}

void printTreeNode(Node* node, int depth, char* prefix, int isLast) {
    if (node == NULL) return;
    char newPrefix[1000];
    printf("%s", prefix);
    if (node->vertex == 0) {
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
            if (node->vertex == n) {
                printf("x%d=%d solution\n", node->vertex, node->color);
            } else {
                printf("x%d=%d\n", node->vertex, node->color);
            }
        } else {
            printf("x%d=%d bound\n", node->vertex, node->color);
        }
    }
    for (int i = 0; i < node->childCount; i++) {
        printTreeNode(node->children[i], depth + 1, newPrefix, i == node->childCount - 1);
    }
}

void printSolutions() {
    printf("\nSolutions (S/n):\n");
    for (int s = 0; s < solutionCount; s++) {
        printf("S%d => ", s+1);
        for (int i = 1; i <= n; i++) {
            printf("%d", solutions[s][i]);
            if (i < n)
                printf(" - ");
        }
        printf("\n");
    }
}

int mColoringCheck(int k, int colors) {
    if (k > n)
        return 1;
    for (int c = 1; c <= colors; c++) {
        int valid = 1;
        for (int j = 1; j <= n; j++) {
            if (G[k][j] != 0 && c == x[j]) {
                valid = 0;
                break;
            }
        }
        if (valid) {
            x[k] = c;
            if (mColoringCheck(k + 1, colors))
                return 1;
            x[k] = 0;
        }
    }
    return 0;
}

int findChromaticNumber() {
    for (int colors = 1; colors <= n; colors++) {
        for (int i = 1; i <= n; i++) {
            x[i] = 0;
        }
        if (mColoringCheck(1, colors))
            return colors;
    }
    return n;
}

void freeTree(Node* node) {
    if (node == NULL)
        return;
    for (int i = 0; i < node->childCount; i++) {
        freeTree(node->children[i]);
    }
    free(node);
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
    chromatic_number = findChromaticNumber();
    printf("\nChromatic number of the graph: %d\n", chromatic_number);
    m = chromatic_number;
    printf("Using %d colors for coloring.\n", m);
    for (int i = 1; i <= n; i++) {
        x[i] = 0;
    }
    clock_t t; 
    t = clock();
    root = createNode(0, 0);
    double time_taken = ((double)t)/CLOCKS_PER_SEC; 
    buildStateSpaceTree(root, 1);
    printf("\nState Space Tree:\n");
    printTreeNode(root, 0, "", 1);
    printf("n Gcoloring fun() took %f seconds to execute \n", time_taken); 
    printSolutions();
    freeTree(root);
    return 0;
}
