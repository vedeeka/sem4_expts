#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define direction constants
#define DIAG 0  // '\' (will use this character for diagonal)
#define LEFT 1  // '<' (will use this character for left)
#define UP   2  // '^' (will use this character for up)

// Define a struct to hold the LCS matrix, the LCS length, path directions, and the arrw array
typedef struct {
    int** L;          // LCS matrix
    int** path;       // Path matrix to store directions
    int length;       // Length of LCS
    int* arrw;        // Additional array
    int** onPath;     // Matrix to mark cells on the LCS path
} LCSResult;

// Function to find the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// LCS function that returns a struct with the matrix, length, path, and arrw
LCSResult LCS(char* X, char* Y, int n, int m) {
    // Allocate memory for 2D array (LCS matrix)
    int** L = (int**)malloc((n+1) * sizeof(int*));
    int** path = (int**)malloc((n+1) * sizeof(int*));
    int** onPath = (int**)malloc((n+1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        L[i] = (int*)malloc((m+1) * sizeof(int));
        path[i] = (int*)malloc((m+1) * sizeof(int));
        onPath[i] = (int*)malloc((m+1) * sizeof(int));
        for (int j = 0; j <= m; j++) {
            onPath[i][j] = 0;  // Initialize all cells as not on path
        }
    }

    // Allocate memory for arrw array
    int* arrw = (int*)malloc(n * sizeof(int));

    // Initialize first row and column to 0
    for (int i = 0; i <= n; i++) {
        L[i][0] = 0;
    }
    for (int j = 0; j <= m; j++) {
        L[0][j] = 0;
    }

    // Fill the L array and path array based on the algorithm
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (X[i-1] == Y[j-1]) {
                L[i][j] = L[i-1][j-1] + 1;
                path[i][j] = DIAG;  // Diagonal arrow
            } else {
                if (L[i-1][j] >= L[i][j-1]) {
                    L[i][j] = L[i-1][j];
                    path[i][j] = UP;  // Up arrow
                } else {
                    L[i][j] = L[i][j-1];
                    path[i][j] = LEFT;  // Left arrow
                }
            }
        }
    }

    // Mark cells on the LCS path
    int i = n, j = m;
    while (i > 0 && j > 0) {
        onPath[i][j] = 1;  // Mark this cell as on the path
        
        if (path[i][j] == DIAG) {
            i--; j--;
        } else if (path[i][j] == UP) {
            i--;
        } else {
            j--;
        }
    }

    // Fill the arrw array with direction indicators
    for (int i = 0; i < n; i++) {
        arrw[i] = path[i+1][m];  // Store the path directions from the last column
    }

    // Create and return the result struct
    LCSResult result;
    result.L = L;
    result.path = path;
    result.length = L[n][m];  // Length of LCS
    result.arrw = arrw;
    result.onPath = onPath;

    return result;
}

// Function to print the combined matrix with numbers and arrows only for path cells
void printPathWithNumbers(char* X, char* Y, LCSResult result, int n, int m) {
    printf("\nLCS Matrix with Path Arrows:\n");
    
    // Print column headers (Y characters)
    printf("L  |");
    for (int j = -1; j < m; j++) {
        if (j == -1) {
            printf("%2d |", j);
        } else {
            printf("%2d |", j);
        }
    }
    printf("\n");
    
    // Print separator line
    for (int j = 0; j <= m+1; j++) {
        printf("----");
    }
    printf("\n");
    
    // Print rows with X characters and values
    for (int i = 0; i <= n; i++) {
        if (i == 0) {
            printf("%2d |", -1);
        } else {
            printf("%2d |", i-1);
        }
        
        for (int j = 0; j <= m; j++) {
            if (result.onPath[i][j]) {
                // Cell is on the LCS path
                const char* arrow = " ";
                if (i > 0 && j > 0) {
                    switch(result.path[i][j]) {
                        case DIAG: arrow = "↖"; break;  // Using diagonal arrow
                        case LEFT: arrow = "←"; break;   // Using left arrow
                        case UP:   arrow = "↑"; break;   // Using up arrow
                    }
                }
                // Print value with arrow and highlight (using * to represent highlighting)
                printf(" %d%s |", result.L[i][j], arrow);
            } else {
                // Cell is not on the path
                printf("%3d |", result.L[i][j]);
            }
        }
        printf("\n");
    }
}


// Function to reconstruct the LCS string from the matrix
void printLCS(char* X, char* Y, LCSResult result, int n, int m) {
    // Get the LCS
    char* lcs = (char*)malloc((result.length + 1) * sizeof(char));
    int index = result.length;
    lcs[index] = '\0';  // Null terminate the string
    
    int i = n;
    int j = m;
    
    // Backtrack using the path matrix
    while (i > 0 && j > 0) {
        if (result.path[i][j] == DIAG) {
            lcs[--index] = X[i-1];  // Add to LCS
            i--; j--;
        } else if (result.path[i][j] == UP) {
            i--;
        } else {
            j--;
        }
    }
    
    printf("\nLCS: %s\n", lcs);
    printf("Length: %d\n", result.length);
    
    free(lcs);
}

// Main function
int main() {
    char X[100], Y[100];
    printf("Enter string X: ");
    fgets(X, sizeof(X), stdin);
    X[strcspn(X, "\n")] = '\0';
    printf("Enter string Y: ");
    fgets(Y, sizeof(Y), stdin);
    Y[strcspn(Y, "\n")] = '\0';

    int n = strlen(X);
    int m = strlen(Y);

    printf("String X: %s (length: %d)\n", X, n);
    printf("String Y: %s (length: %d)\n", Y, m);

    // Call LCS function and get the result struct
    LCSResult result = LCS(X, Y, n, m);

    // Print LCS info
    printLCS(X, Y, result, n, m);

    // Print the combined matrix with numbers and arrows
    printPathWithNumbers(X, Y, result, n, m);

    // Free allocated memory
    for (int i = 0; i <= n; i++) {
        free(result.L[i]);
        free(result.path[i]);
        free(result.onPath[i]);
    }
    free(result.L);
    free(result.path);
    free(result.onPath);
    free(result.arrw);

    return 0;
}