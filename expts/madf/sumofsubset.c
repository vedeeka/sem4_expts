#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100
#define INF 9999
#define MAX_PREFIX 1024

struct treeNode {
    int id, s, k, r, inc;       
    struct treeNode *left;  
    struct treeNode *right;
};

int n, m, nc = 0, soli = 0;
int w[MAX], x[MAX], sol[MAX][MAX];
char sol_labels[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

struct treeNode* createN(int s, int k, int r, int inc) {
    struct treeNode* nn = (struct treeNode*)malloc(sizeof(struct treeNode));
    if (nn == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    nc++;
    nn->id = nc;
    nn->s = s;
    nn->k = k;
    nn->r = r;
    nn->inc = inc;
    nn->left = NULL;
    nn->right = NULL;
    return nn;
}

void saveSolution() {
    int i;
    for (i = 1; i <= n; i++) {
        sol[soli][i] = x[i];
    }
    soli++;
}

struct treeNode* SumOfSub(int s, int k, int r) {
    struct treeNode* cnode = createN(s, k, r, 1);
    x[k] = 1;
    if (s + w[k] == m) {
        cnode->left = createN(s + w[k], k + 1, r - w[k], 0);
        saveSolution();
    } else if (s + w[k] + w[k + 1] <= m && k < n) {
        cnode->left = SumOfSub(s + w[k], k + 1, r - w[k]);
    }
    if ((s + r - w[k] >= m) && (s + w[k + 1] <= m || k == n) && k < n) {
        x[k] = 0;
        cnode->inc = 0;
        cnode->right = SumOfSub(s, k + 1, r - w[k]);
    }
    return cnode;
}

void freeTree(struct treeNode* node) {
    if (node == NULL) return;
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

void formatNodeInfo(char* buffer, struct treeNode* node) {
    sprintf(buffer, "[s=%d, k=%d, r=%d]", node->s, node->k, node->r);
    
    if (node->s == m) {
        strcat(buffer, " solution");
    }
    
    // Add bound label when a branch is bounded (no children due to constraints)
    if ((node->left == NULL && node->right == NULL) && (node->s != m)) {
        strcat(buffer, " bound");
    }
    
    if (node->s == m) {
        char solution_mark[10];
        sprintf(solution_mark, " (%c)", sol_labels[node->id % 26]);
        strcat(buffer, solution_mark);
    }


}
void printHorizontalTree(struct treeNode* node, char* prefix) {
    if (node == NULL) return;
    char node_info[64];
    char include_prefix[MAX_PREFIX];
    char exclude_prefix[MAX_PREFIX];
    formatNodeInfo(node_info, node);
    printf("%s%s (Node %d)\n", prefix, node_info, node->id);
    if (node->left == NULL && node->right == NULL) {
        return;
    }
    if (node->left != NULL && node->right != NULL) {
        sprintf(include_prefix, "%s├── x%d=1\n%s│   ", prefix, node->k, prefix);
        sprintf(exclude_prefix, "%s└── x%d=0\n%s    ", prefix, node->k, prefix);
    } else if (node->left != NULL) {
        sprintf(include_prefix, "%s└── x%d=1\n%s    ", prefix, node->k, prefix);
    } else if (node->right != NULL) {
        sprintf(exclude_prefix, "%s└── x%d=0\n%s    ", prefix, node->k, prefix);
    }
    if (node->left != NULL) {
        printf("%s├── x%d=1\n", prefix, node->k);
        char new_prefix[MAX_PREFIX];
        sprintf(new_prefix, "%s│   ", prefix);
        printHorizontalTree(node->left, new_prefix);
    }
    if (node->right != NULL) {
        if (node->left != NULL) {
            printf("%s└── x%d=0\n", prefix, node->k);
            char new_prefix[MAX_PREFIX];
            sprintf(new_prefix, "%s    ", prefix);
            printHorizontalTree(node->right, new_prefix);
        } else {
            printf("%s├── x%d=0\n", prefix, node->k);
            char new_prefix[MAX_PREFIX];
            sprintf(new_prefix, "%s│   ", prefix);
            printHorizontalTree(node->right, new_prefix);
        }
    }
}

void printSolutions() {
    printf("\n\nFinal Solutions:\n");
    printf("=================\n");
    if (soli == 0) {
        printf("No solution found.\n");
        return;
    }
    for (int s = 0; s < soli; s++) {
        printf("Solution %c: {", sol_labels[s]);
        int first = 1;
        for (int j = 1; j <= n; j++) {
            if (sol[s][j] == 1) {
                if (!first) {
                    printf(", ");
                }
                printf("%d", w[j]);
                first = 0;
            }
        }
        printf("} = %d\n", m);
        printf("   Binary: ");
        for (int j = 1; j <= n; j++) {
            printf("x[%d]=%d ", j, sol[s][j]);
        }
        printf("\n");
    }
}

int main() {
    int i, j, s;
    struct timespec start, end;
    double time_taken;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    printf("Enter the sum value (m): ");
    scanf("%d", &m);
    printf("Enter %d weights in  order: ", n);
    int sum = 0;
    for (i = 1; i <= n; i++) {
        scanf("%d", &w[i]);
        sum += w[i];
    }
    w[n + 1] = INF;
    if (w[1] > m || sum < m) {
        printf("No possible subsets.\n");
        return 0;
    }
    clock_gettime(CLOCK_MONOTONIC, &start);
    struct treeNode* root = SumOfSub(0, 1, sum);
    clock_gettime(CLOCK_MONOTONIC, &end);
    time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) / 1e6;
    printf("\nSum of Subsets Horizontal Tree (Target = %d):\n\n", m);
    char root_info[64];
    formatNodeInfo(root_info, root);
    printf("%s (Root)\n", root_info);
    printHorizontalTree(root, "");
    printSolutions();
    printf("\nTime Taken: %.6f milliseconds\n", time_taken);
    printf("Total nodes created: %d\n", nc);
    freeTree(root);
    return 0;
}
