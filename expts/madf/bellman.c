#include <stdio.h>
#include <time.h>  // For measuring execution time
#define MAX 10
#define INF 999

int distance[MAX][MAX], path[MAX];
int predecessor[MAX];  // To store the predecessor of each vertex
int n;

void display_distance_matrix() {
    int i, j;
    printf("\nCurrent Distance Matrix:\n");
    printf("     ");
    for(i=1; i<=n; i++) {
        printf("%-4d", i);
    }
    printf("\n-----");
    for(i=1; i<=n; i++) {
        printf("----");
    }
    printf("\n");
    for(i=1; i<=n; i++) {
        printf("%-4d| ", i);
        for(j=1; j<=n; j++) {
            if(distance[i-1][j-1] == INF) {
                printf("INF ");
            } else {
                printf("%-4d", distance[i-1][j-1]);
            }
        }
        printf("\n");
    }
}

// Function to print the path from source to destination
void print_path(int src, int dest) {
    if (dest == src) {
        printf("%d", src+1);
        return;
    }
    
    if (predecessor[dest] == -1) {
        printf("No path");
        return;
    }
    
    print_path(src, predecessor[dest]);
    printf(" -> %d", dest+1);
}


void singlesource_sp(int v) {
    int temp[MAX], i, j, k;
    
    // Initialize path array with direct distances from source
    for(i=0; i<n; i++) {
        path[i] = distance[v][i];
        
        // Initialize predecessor array
        if (distance[v][i] != INF && i != v) {
            predecessor[i] = v;
        } else {
            predecessor[i] = -1;
        }
    }
    
    printf("\nInitial Distance Values (k=0):\n");
    
    
    // Bellman-Ford algorithm: Compute shortest paths with at most k edges
    for(k=1; k<n; k++) {
        // Make a copy of current path values
        for(i=0; i<n; i++) {
            temp[i] = path[i];
        }
        
        // Try to find shorter paths
        for(i=0; i<n; i++) {
            if(i != v) {  // Skip source vertex
                for(j=0; j<n; j++) {
                    if(distance[j][i] != INF && path[j] != INF) {
                        if(path[i] > path[j] + distance[j][i]) {
                            path[i] = path[j] + distance[j][i];
                            predecessor[i] = j;  // Update predecessor
                        }
                    }
                }
            }
        }
        
        // Display both updated path table and distance matrix after each iteration
        
        
    }
	display_distance_matrix();
	
}

int main() {
    int i, j, origin, destin, weight, v;
    int edge_count = 1;
    clock_t start_time, end_time;
    double execution_time;
    
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    
    // Initialize distance matrix
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            if(i == j)
                distance[i][j] = 0;
            else
                distance[i][j] = INF;
        }
    }
    
    printf("\nEnter edges as origin destination weight\n");
    printf("Enter -1 -1 -1 to stop input\n");
    
    // Using while loop to take input until -1 -1 -1 is entered
    while(1) {
        scanf("%d %d %d", &origin, &destin, &weight);
        
        if(origin == -1 && destin == -1 && weight == -1)
            break;
            
        if(origin > n || destin > n || origin <= 0 || destin <= 0) {
            printf("Invalid edge! Vertices must be between 1 and %d.\n", n);
        } else {
            distance[origin-1][destin-1] = weight;
            edge_count++;
        }
    }
    

    printf("\nEnter starting vertex (1 to %d): ", n);
    scanf("%d", &v);
    
    if(v <= 0 || v > n) {
        printf("Invalid starting vertex.\n");
        return 1;
    }
    
    // Start timing
    start_time = clock();
    
    // Run the shortest path algorithm
    singlesource_sp(v-1);
    
    // End timing
    end_time = clock();
    
    // Calculate execution time in seconds
    execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    
    printf("\n\nFinal Results:\n");
    printf("-------------------------------------------------------\n");
    printf("Source vertex: %d\n", v);
    printf("Time taken: %.6f seconds\n", execution_time);
    printf("-------------------------------------------------------\n");
    printf("Src  Dest  Length  Path\n");
    printf("-------------------------------------------------------\n");
    
    for (i = 0; i < n; i++) {
        if (i != v-1) {
            printf("%-4d %-5d ", v, i+1);
            if (path[i] == INF) {
                printf("%-9s No path", "No Path");
            } else {
                printf("%-7d ", path[i]);
                print_path(v-1, i);
            }
            printf("\n");
        }
    }
    printf("-------------------------------------------------------\n");
    
    return 0;
}