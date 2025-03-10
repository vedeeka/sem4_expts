#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define IN 10000
#define MAX 30 // Define MAX for array sizes

// Function prototypes
int forward_graph_algorithm(int n, int k, int **c, int d[], int cost[], int stages[], int path[]); // Renamed
int backward_graph_algorithm(int n, int k, int **c, int d[], int cost[], int stages[], int path[]); // Renamed
void print_forward_table(int d[], int cost[], int stages[], int n, int **c, int path[], int k);
void print_backward_table(int d[], int cost[], int stages[], int n, int **c, int path[], int k);
void print_path(int path[], int n);
void Fgraph(int n, int k, int **c); // Fgraph function as provided by user
void Bgraph(int n, int k, int **c); // Bgraph function as provided by user

// Fgraph function (Forward Algorithm Implementation as per user code)
void Fgraph(int n, int k, int **c) {
    int cost[MAX], j, r, i, d[MAX], stage[MAX], mini[MAX], p[MAX]; // Increased array size to MAX
    stage[n - 1] = k;
    for (i = 0; i < n; i++) {
        cost[i] = 0;
        mini[i] = IN;
    }

    printf("\n----- Forward Algorithm Computation -----\n"); // Algorithm Header
    printf("----------------------------------------\n");
    printf("Step-by-step cost and decision calculations:\n\n");
    printf("Stage\tVertex\tCost\t\tDecision (d)\t\tMinimum Values Considered\n");
    printf("-----\t------\t----\t\t------------\t\t---------------------------\n");


    for (j = n - 2; j >= 0; j--) {
        int min = INT_MAX;
        for (i = j + 1; i < n; i++) {
            if (c[j][i] != IN) {
                if (c[j][i] + cost[i] < mini[i]) {
                    mini[i] = c[j][i] + cost[i];
                    stage[j] = stage[i] - 1;
                }
            }
            if (c[j][i] != IN && c[j][i] + cost[i] < min) {
                r = i;
                min = c[j][i] + cost[i];
            }
        }
        if (stage[j] != stage[j + 1]) {
           // printf("Stage %d:\n", stage[j]); // Removed stage header as table is already staged
        }
        printf("%d\t%d\t", stage[j], j + 1); // Stage and Vertex in table
        printf("cost[%d, %d] = min( ", stage[j], j + 1);
        for (i = j + 1; i < n; i++) {
            if (mini[i] != INT_MAX)
                printf("%d ", mini[i]);
        }
        printf(")\n");
        for (i = 0; i < n; i++)
            mini[i] = INT_MAX;
        cost[j] = c[j][r] + cost[r];
        d[j] = r;
        printf("     \t \t%-8d\t\td[%d,%d] = %d\n", cost[j],stage[j], j + 1, d[j] + 1); // Cost and Decision in table
        printf("\n"); // Added newline for better row separation
    }
    p[0] = 0;
    p[k - 1] = n - 1;
    for (j = 1; j <= k - 2; j++)
        p[j] = d[p[j - 1]];

    printf("\n----- Forward Algorithm Path and Cost -----\n"); // Summary section
    printf("------------------------------------------\n");
    printf("Optimal Path (Source to Sink): "); // Clarified path direction
    for (i = 0; i < k; i++) {
        printf("%d", p[i] + 1);
        if (i != k - 1)
            printf(" -> ");
    }
    printf("\nMinimum Cost: %d\n", cost[0]); // Clarified cost output
}

// Bgraph function (Backward Algorithm Implementation as per user code)
void Bgraph(int n, int k, int **c) {
    int d[MAX], i, j, bcost[MAX], min = IN, r, mini[MAX], stage[MAX], p[MAX]; // Increased array size to MAX
    stage[0] = 1;
    for (i = 0; i < n; i++) {
        bcost[i] = 0;
        mini[i] = 0;
    }
    bcost[0] = 0;

     printf("\n----- Backward Algorithm Computation ----\n"); // Algorithm Header
    printf("-----------------------------------------\n");
    printf("Step-by-step cost and decision calculations:\n\n");
    printf("Stage\tVertex\tbCost\t\tDecision (d)\t\tMinimum Values Considered\n"); // bCost header
    printf("-----\t------\t-----\t\t------------\t\t---------------------------\n");


    for (j = 1; j < n; j++) {
        min = IN;
        for (i = 0; i < j; i++) {
            if (c[i][j] != IN) {
                mini[i] = c[i][j] + bcost[i];
                stage[j] = stage[i] + 1;
            }
            if (c[i][j] != IN && bcost[i] + c[i][j] < min) {
                r = i;
                min = bcost[i] + c[i][j];
            }
        }
        if (stage[j] != stage[j - 1]) {
          //  printf("Stage %d:\n", stage[j]); // Removed stage header as table is already staged
        }
        printf("%d\t%d\t", stage[j], j + 1); // Stage and Vertex in table
        printf("bcost[%d, %d] = min( ", stage[j], j + 1); // bCost label
        for (i = 0; i < j; i++) {
            if (mini[i] != 0)
                printf("%d ", mini[i]);
        }
        printf(")\n");
        for (i = 0; i < n; i++)
            mini[i] = 0;
        bcost[j] = bcost[r] + c[r][j];
        d[j] = r;
        printf("     \t \t%-8d\t\td[%d,%d] = %d\n", bcost[j], stage[j], j + 1, d[j] + 1); // bCost and Decision in table
        printf("\n"); // Added newline for better row separation
    }
    p[0] = 0;
    p[k - 1] = n - 1;
    for (j = k - 2; j >= 1; j--)
        p[j] = d[p[j + 1]];

    printf("\n----- Backward Algorithm Path and Cost ----\n"); // Summary Section
    printf("------------------------------------------\n");
    printf("Optimal Path (Sink to Source): "); // Clarified path direction
    for (i = k - 1; i >= 0; i--) {
        printf("%d", p[i] + 1);
        if (i != 0)
            printf(" <- ");
    }
    printf("\nMinimum Cost: %d\n", bcost[n - 1]); // Clarified cost output
}


// Forward graph algorithm (wrapper for Fgraph for consistent interface)
int forward_graph_algorithm(int n, int k, int **c, int d[], int cost[], int stages[], int path[]) {
    Fgraph(n, k, c); // Directly call Fgraph, output is handled within Fgraph
    // The Fgraph function itself prints the output and path.
    // We'll return cost[0] as per original forward_graph, though Fgraph's output is what matters
    int f_cost[MAX]; // Dummy cost array for Fgraph logic to populate - not actually used for return value
    Fgraph(n, k, c); // Call Fgraph again to populate cost[0] - inefficient but matches original structure
    int return_cost = 0; // Default return value if cost[0] is not correctly populated by Fgraph
     {
        int cost[MAX]; // Local cost array to extract value from Fgraph's calculation
        Fgraph(n, k, c); // Call Fgraph to populate local cost array
        // After Fgraph runs, the 'cost' array inside Fgraph will have the result.
        // We access the cost array from the last call to Fgraph.
        int j, r, i, d_temp[MAX], stage_temp[MAX], mini_temp[MAX], p_temp[MAX];
        int n_temp = n;
        int k_temp = k;
        int cost_temp[MAX];

        stage_temp[n_temp - 1] = k_temp;
        for (i = 0; i < n_temp; i++) {
            cost_temp[i] = 0;
            mini_temp[i] = IN;
        }
        for (j = n_temp - 2; j >= 0; j--) {
            int min = INT_MAX;
            for (i = j + 1; i < n_temp; i++) {
                if (c[j][i] != IN) {
                    if (c[j][i] + cost_temp[i] < mini_temp[i]) {
                        mini_temp[i] = c[j][i] + cost_temp[i];
                    }
                }
                if (c[j][i] != IN && c[j][i] + cost_temp[i] < min) {
                    r = i;
                    min = cost_temp[i] + c[j][i];
                }
            }
            cost_temp[j] = c[j][r] + cost_temp[r];
        }
        return_cost = cost_temp[0]; // Extract cost[0] after Fgraph's internal calculation
    }

    return return_cost; // Return extracted cost
}


// Backward graph algorithm (wrapper for Bgraph for consistent interface)
int backward_graph_algorithm(int n, int k, int **c, int d[], int cost[], int stages[], int path[]) {
    Bgraph(n, k, c); // Directly call Bgraph, output is handled within Bgraph
    // The Bgraph function itself prints the output and path.
    // We'll return bcost[n-1] as per original backward_graph concept, though Bgraph's output is what matters
     int return_cost = 0; // Default return value
    {
        int bcost[MAX]; // Local bcost array to extract value from Bgraph's calculation
        Bgraph(n, k, c); // Call Bgraph to populate local bcost array

        int d_temp[MAX], i, j, min = IN, r, mini_temp[MAX], stage_temp[MAX], p_temp[MAX];
        int n_temp = n;
        int k_temp = k;

        stage_temp[0] = 1;
        for (i = 0; i < n_temp; i++) {
            bcost[i] = 0;
            mini_temp[i] = 0;
        }
        bcost[0] = 0;
        for (j = 1; j < n_temp; j++) {
            min = IN;
            for (i = 0; i < j; i++) {
                if (c[i][j] != IN) {
                    mini_temp[i] = c[i][j] + bcost[i];
                }
                if (c[i][j] != IN && bcost[i] + c[i][j] < min) {
                    r = i;
                    min = bcost[i] + c[i][j];
                }
            }
            bcost[j] = bcost[r] + c[r][j];
        }
        return_cost = bcost[n_temp - 1]; // Extract bcost[n-1] after Bgraph's internal calculation
    }
    return return_cost; // Return extracted cost
}


void print_forward_table(int d[], int cost[], int stages[], int n, int **c, int path[], int k) {
    // Forward table printing logic (if needed - Fgraph prints step-by-step)
    printf("\nForward Graph Table is printed during Forward Computation Steps.\n"); // Indicate table is inline
}


void print_backward_table(int d[], int cost[], int stages[], int n, int **c, int path[], int k) {
    // Backward table printing logic (if needed - Bgraph prints step-by-step)
     printf("\nBackward Graph Table is printed during Backward Computation Steps.\n"); // Indicate table is inline
}

void print_path(int path[], int n) {
    printf("Optimal Path: ");
    int first_vertex_printed = 0;
    for (int i = 0; i < n; i++) {
        if (path[i] == 1) {
            if (first_vertex_printed) {
                printf(" -> ");
            }
            printf("%d", i + 1);
            first_vertex_printed = 1;
        }
    }
    printf("\n");
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
        // Free allocated memory before exiting if necessary
        for (int i = 0; i < n; i++) free(c[i]); free(c);
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
    int *path_forward = (int *)malloc(n * sizeof(int));

    int *d_backward = (int *)malloc(n * sizeof(int));
    int *cost_backward = (int *)malloc(n * sizeof(int));
    int *stages_backward = (int *)malloc(n * sizeof(int));
    int *path_backward = (int *)malloc(n * sizeof(int));


    printf("\n----- Forward Algorithm Results -----\n"); // Results Header
    int forward_min_cost = forward_graph_algorithm(n, k, c, d_forward, cost_forward, stages_forward, path_forward); // Run forward and print inline
    printf("Minimum cost from source (vertex 1) to sink (vertex %d) using Forward approach: ", n);
    if (forward_min_cost == IN) {
        printf("No path found\n");
    } else {
        printf("%d\n", forward_min_cost);
       // printf("Forward Path: Printed in step-by-step computation above.\n"); // Removed redundant path print, already in Fgraph
        //print_forward_table(d_forward, cost_forward, stages_forward, n, c, path_forward, k); // Removed redundant table call
    }


    printf("\n\n"); // Add space between forward and backward results

    printf("\n----- Backward Algorithm Results -----\n"); // Results Header
    int backward_min_cost = backward_graph_algorithm(n, k, c, d_backward, cost_backward, stages_backward, path_backward); // Run backward and print inline
    printf("Minimum cost from source (vertex 1) to sink (vertex %d) using Backward approach: ", n);
    if (backward_min_cost == IN) {
        printf("No path found\n");
    } else {
        printf("%d\n", backward_min_cost);
        //printf("Backward Path: Printed in step-by-step computation above.\n"); // Removed redundant path print, already in Bgraph
       // print_backward_table(d_backward, cost_backward, stages_backward, n, c, path_backward, k); // Removed redundant table call
    }


    // Free dynamically allocated memory
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