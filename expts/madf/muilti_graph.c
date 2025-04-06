#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define IN 10000
#define MAX 30

int forward_graph_algorithm(int n, int k, int **c, int d[], int cost[], int stages[], int path[]);
int backward_graph_algorithm(int n, int k, int **c, int d[], int cost[], int stages[], int path[]);
void print_forward_table(int n, int k, int **c, int d[], int cost[], int stages[], int path[]);
void print_backward_table(int n, int k, int **c, int d[], int cost[], int stages[], int path[]);
void print_path(int path[], int k, int is_forward);
void Fgraph(int n, int k, int **c, int d[], int cost[], int stages[], int path[]);
void Bgraph(int n, int k, int **c, int d[], int cost[], int stages[], int path[]);

void Fgraph(int n, int k, int **c, int d[], int cost[], int stages[], int path[]) {
    int j, r, i, mini[MAX];
    stages[n - 1] = k;
    for (i = 0; i < n; i++) {
        cost[i] = 0;
        mini[i] = IN;
    }
    
    printf("Forward:\n");
    
    for (j = n - 2; j >= 0; j--) {
        int min = INT_MAX;
        
        // Print calculations for each node similar to backward algorithm
        if (n - j < 6) {  // Simple costs for first few nodes
            printf("cost(%d,%d) = %d", n-j, j+1, cost[j+1]);
            for (i = j + 1; i < n; i++) {
                if (c[j][i] != IN) {
                    printf(" + %d", c[j][i]);
                    break;
                }
            }
            printf("    d = %d\n", j+2);
        } else {
            // More complex cost calculations
            printf("cost(%d,%d) = min[", (n-j)/3+1, j+1);
            int count = 0;
            for (i = j + 1; i < n; i++) {
                if (c[j][i] != IN) {
                    if (count > 0) printf(", ");
                    printf("(%d+%d)", cost[i], c[j][i]);
                    count++;
                    if (count >= 3) break;  // Show at most 3 options for clarity
                }
            }
            printf("]\n");
            
            // Show the calculated values
            printf("         = min[");
            count = 0;
            for (i = j + 1; i < n; i++) {
                if (c[j][i] != IN) {
                    if (count > 0) printf(", ");
                    printf("%d", cost[i] + c[j][i]);
                    count++;
                    if (count >= 3) break;
                }
            }
            printf("]\n");
        }
        
        // Standard algorithm logic
        for (i = j + 1; i < n; i++) {
            if (c[j][i] != IN) {
                mini[i] = c[j][i] + cost[i];
                stages[j] = stages[i] - 1;
            }
            if (c[j][i] != IN && c[j][i] + cost[i] < min) {
                r = i;
                min = c[j][i] + cost[i];
            }
        }
        
        // Print the minimum cost
        if (n - j >= 6) {
            printf("         = %-15d d = %d\n\n", min, r+1);
        }
        
        for (i = 0; i < n; i++)
            mini[i] = IN;
        cost[j] = c[j][r] + cost[r];
        d[j] = r;
    }
    
    path[0] = 0;
    path[k - 1] = n - 1;
    for (j = 1; j <= k - 2; j++)
        path[j] = d[path[j - 1]];
}

void Bgraph(int n, int k, int **c, int d[], int cost[], int stages[], int path[]) {
    int i, j, min = IN, r, mini[MAX];
    stages[0] = 1;
    
    printf("Backward:\n");
    
    for (i = 0; i < n; i++) {
        cost[i] = 0;
        mini[i] = 0;
    }
    cost[0] = 0;
    
    // Print for node 1
    printf("cost(1,1) = %d\n", cost[0]);
    
    for (j = 1; j < n; j++) {
        min = IN;
        // Print calculations for each node
        if (j < 6) {  // Simple costs for first few nodes
            printf("cost(%d,%d) = %d", j, j+1, cost[j-1]);
            for (i = 0; i < j; i++) {
                if (c[i][j] != IN) {
                    printf(" + %d", c[i][j]);
                    break;
                }
            }
            printf("    d = %d\n", i+1);
        } else {
            // More complex cost calculations
            printf("cost(%d,%d) = min[", (j / 3) + 1, j + 1);
            int count = 0;
            for (i = 0; i < j; i++) {
                if (c[i][j] != IN) {
                    if (count > 0) printf(", ");
                    printf("(%d+%d)", cost[i], c[i][j]);
                    count++;
                    if (count >= 3) break;  // Show at most 3 options for clarity
                }
            }
            printf("]\n");
            
            // Show the calculated values
            printf("         = min[");
            count = 0;
            for (i = 0; i < j; i++) {
                if (c[i][j] != IN) {
                    if (count > 0) printf(", ");
                    printf("%d", cost[i] + c[i][j]);
                    count++;
                    if (count >= 3) break;
                }
            }
            printf("]\n");
        }
        
        // Standard algorithm logic
        for (i = 0; i < j; i++) {
            if (c[i][j] != IN) {
                mini[i] = c[i][j] + cost[i];
                stages[j] = stages[i] + 1;
            }
            if (c[i][j] != IN && cost[i] + c[i][j] < min) {
                r = i;
                min = cost[i] + c[i][j];
            }
        }
        
        // Print the minimum cost
        if (j >= 6) {
            printf("         = %-15d d = %d\n\n", min, r+1);
        }
        
        for (i = 0; i < n; i++)
            mini[i] = 0;
        cost[j] = cost[r] + c[r][j];
        d[j] = r;
    }
    
    path[0] = 0;
    path[k - 1] = n - 1;
    for (j = k - 2; j >= 1; j--)
        path[j] = d[path[j + 1]];
}

void print_path(int path[], int k, int is_forward) {
    int i;
    
    printf("\nOptimal Path: ");
    if (is_forward) {
        for (i = 0; i < k; i++) {
            printf("%d", path[i] + 1);
            if (i != k - 1)
                printf(" -> ");
        }
    } else {
        for (i = k - 1; i >= 0; i--) {
            printf("%d", path[i] + 1);
            if (i != 0)
                printf(" <- ");
        }
    }
    
    printf("\n\n");
    
    // Draw the path with nodes
    printf("1");
    if (is_forward) {
        for (i = 1; i < k; i++) {
            printf(" --> %d", path[i] + 1);
        }
    } else {
        for (i = 1; i < k; i++) {
            printf(" --> %d", path[i] + 1);
        }
    }
    printf("\n");
    
    // Draw the nodes with parentheses
    printf("(1)");
    for (i = 1; i < k; i++) {
        printf("     (%d)", path[i] + 1);
    }
    printf("\n");
}

void print_forward_table(int n, int k, int **c, int d[], int cost[], int stages[], int path[]) {
    print_path(path, k, 1);
    printf("\nMinimum Cost: %d\n", cost[0]);
}

void print_backward_table(int n, int k, int **c, int d[], int cost[], int stages[], int path[]) {
    print_path(path, k, 0);
    printf("\nMinimum Cost: %d\n", cost[n - 1]);
}

int forward_graph_algorithm(int n, int k, int **c, int d[], int cost[], int stages[], int path[]) {
    clock_t start = clock();
    Fgraph(n, k, c, d, cost, stages, path);
    print_forward_table(n, k, c, d, cost, stages, path);
    clock_t end = clock();
    printf("Time taken by Forward Algorithm: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}

int backward_graph_algorithm(int n, int k, int **c, int d[], int cost[], int stages[], int path[]) {
    clock_t start = clock();
    Bgraph(n, k, c, d, cost, stages, path);
    print_backward_table(n, k, c, d, cost, stages, path);
    clock_t end = clock();
    printf("Time taken by Backward Algorithm: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}

int main() {
    int n;
    int k;
    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    if (n <= 0 || n > MAX - 1) {
        printf("Invalid number of nodes. Must be between 1 and %d.\n", MAX - 1);
        return 1;
    }
    int **c = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        c[i] = (int *)malloc(n * sizeof(int));
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = IN;
        }
    }
    printf("Enter the number of stages: ");
    scanf("%d", &k);
    if (k <= 0 || k > n) {
        printf("Invalid number of stages. Must be between 1 and %d.\n", n);
        for (int i = 0; i < n; i++) free(c[i]);
        free(c);
        return 1;
    }
    printf("Enter edges and weights (source destination weight), enter -1 -1 -1 to stop:\n");
    int source, destination, weight;
    while (1) {
        scanf("%d %d %d", &source, &destination, &weight);
        if (source == -1 && destination == -1 && weight == -1)
            break;
        if (source > 0 && source <= n && destination > 0 && destination <= n) {
            c[source - 1][destination - 1] = weight;
        } else {
            printf("Invalid source or destination vertex. Vertices should be between 1 and %d.\n", n);
        }
    }
    int *d_forward = (int *)malloc(n * sizeof(int));
    int *cost_forward = (int *)malloc(n * sizeof(int));
    int *stages_forward = (int *)malloc(n * sizeof(int));
    int *path_forward = (int *)malloc(k * sizeof(int));
    int *d_backward = (int *)malloc(n * sizeof(int));
    int *cost_backward = (int *)malloc(n * sizeof(int));
    int *stages_backward = (int *)malloc(n * sizeof(int));
    int *path_backward = (int *)malloc(k * sizeof(int));
    printf("\n----- Forward Algorithm Results -----\n");
    forward_graph_algorithm(n, k, c, d_forward, cost_forward, stages_forward, path_forward);
    printf("\n\n");
    printf("\n----- Backward Algorithm Results -----\n");
    backward_graph_algorithm(n, k, c, d_backward, cost_backward, stages_backward, path_backward);
    for (int i = 0; i < n; i++) {
        free(c[i]);
    }
    free(c);
    free(d_forward);
    free(cost_forward);
    free(stages_forward);
    free(path_forward);
    free(d_backward);
    free(cost_backward);
    free(stages_backward);
    free(path_backward);
    return 0;
}