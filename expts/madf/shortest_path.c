#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // Include for bool type

#define MAX 10
int distance[MAX][MAX], path[MAX][MAX];
int n;
int count = 0;

void shortest_path() {
    int temp[MAX][MAX], i, j, k; // Use MAX for temp array as well
    count++; // Increment for function entry

    // Initialize path and temp matrices with distance matrix
    for (i = 0; i < n; i++) {
        count += 2; // Loop initialization and increment
        for (j = 0; j < n; j++) {
            count += 3; // Loop initialization, increment, and array access (distance[i][j])
            path[i][j] = distance[i][j];
            temp[i][j] = distance[i][j];
            count += 2; // Two assignments
        }
        count++; // Inner loop exit
    }
    count++; // Outer loop exit

    // Floyd-Warshall algorithm core
    for (k = 0; k < n; k++) {
        count += 2; // Loop initialization and increment
        for (i = 0; i < n; i++) {
            count += 2; // Loop initialization and increment
            for (j = 0; j < n; j++) {
                count += 2; // Loop initialization and increment
                count++; // Comparison: path[i][j] > path[i][k] + path[k][j]
                if (path[i][j] > path[i][k] + path[k][j]) {
                    temp[i][j] = path[i][k] + path[k][j];
                    count += 2; // Addition and assignment
                }
                count++; // if condition check
            }
            count++; // Inner loop exit
        }
        count++; // Middle loop exit

        // Update path matrix from temp matrix
        for (i = 0; i < n; i++) {
            count += 2; // Loop initialization and increment
            for (j = 0; j < n; j++) {
                count += 2; // Loop initialization and increment and array access (temp[i][j])
                path[i][j] = temp[i][j];
                count++; // Assignment
            }
            count++; // Inner loop exit
        }
        count++; // Outer loop exit
    }
    count++; // Outer loop exit

    printf("\nSolution matrix for all source shortest path: \n%4s", " ");
    for (i = 0; i < n; i++) {
        printf("%4d", i);
        count += 2; // Loop, printf
    }
    count++; // Loop exit

    for (i = 0; i < n; i++) {
        count++; // Loop initialization and increment
        printf("\n%4d", i);
        count++; // printf
        for (j = 0; j < n; j++) {
            count += 2; // Loop initialization and increment, array access (path[i][j])
            if (path[i][j] == 999) {
                printf("%4s", "++");
                count++; // comparison and printf
            } else {
                printf("%4d", path[i][j]);
                count++; // comparison and printf
            }
        }
        count++; // Inner loop exit
    }
    count++; // Outer loop exit
}

int main() {
    int i, max_edges, origin, destin, dist, j;
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    count++; // scanf

    // Initialize distance matrix
    for (i = 0; i < n; i++) {
        count += 2; // Loop initialization and increment
        for (j = 0; j < n; j++) {
            count += 3; // Loop initialization, increment, and array access (distance[i][j])
            if (i == j) {
                distance[i][j] = 0;
                count++; // comparison and assignment
            } else {
                distance[i][j] = 999;
                count++; // comparison and assignment
            }
        }
        count++; // Inner loop exit
    }
    count++; // Outer loop exit

    max_edges = n * (n - 1);
    count++; // Multiplication and assignment

    // Input edges and distances
    for (i = 1; i <= max_edges; i++) {
        count += 2; // Loop initialization and increment
        printf("\nPress origin as -1 and destination as -1 to end\n");
        printf("Enter edge %d: ", i);
        scanf("%d %d", &origin, &destin);
        count += 2; // scanf

        if ((origin == -1) && (destin == -1)) {
            count++; // comparison
            break;
        }

        printf("Distance: ");
        scanf("%d", &dist);
        count++; // scanf

        if (origin > n || destin > n || origin < 0 || destin < 0) {
            printf("Invalid edge!\n");
            i--;
            count += 5; // Comparisons and printf
        } else {
            distance[origin][destin] = dist;
            count++; // Assignment
        }
    }
    count++; // Loop exit

    shortest_path();
    printf("\nStep Count: %d", count);
    count++; // printf and increment for the end of main (though not really counted in algorithm complexity)

    return 0; // Added return 0 for good practice
}