#include <stdio.h>
#include <stdlib.h>
#define MAX_N 20

int queens[MAX_N + 1]; // Array to store queen positions (1-indexed)
int solution_count = 0;
int solutions_to_display = 2; // Only display 2 solutions

// Check if queen can be placed at position (row, col)
int is_safe(int row, int col) {
    for (int i = 1; i < row; i++) {
        if (queens[i] == col || abs(queens[i] - col) == abs(i - row)) {
            return 0;
        }
    }
    return 1;
}

// Print the board in a perfect square grid as shown in the image
void print_solution(int n) {
    solution_count++;
    
    // Only display the first two solutions found
    if (solution_count <= solutions_to_display) {
        // Create an empty board
        char board[MAX_N][MAX_N];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                board[i][j] = ' ';
            }
        }
        
        // Place queen numbers on the board
        for (int i = 1; i <= n; i++) {
            board[i-1][queens[i]-1] = i + '0'; // Convert to char
        }
        
        // Print top border of the square
        printf("    ");
        for (int j = 0; j < n; j++) {
            printf(" _");
        }
        printf("\n");
        
        // Print board with borders
        for (int i = 0; i < n; i++) {
            printf("   |");
            for (int j = 0; j < n; j++) {
                printf("%c|", board[i][j]);
            }
            printf("\n");
        }
        
        // Print the coordinate representation as shown in the image
        printf("   (");
        for (int j = 1; j <= n; j++) {
            printf("%d", queens[j]);
            if (j < n) printf(",");
        }
        printf(") = %d\n\n", solution_count);
    }
}

// Solve N-Queens using backtracking
void solve_nqueens(int row, int n) {
    if (row > n) {
        print_solution(n);
        return;
    }
    
    for (int col = 1; col <= n; col++) {
        if (is_safe(row, col)) {
            queens[row] = col;
            solve_nqueens(row + 1, n);
        }
    }
}

int main() {
    int n;
    printf("Enter the number of queens: ");
    scanf("%d", &n);
    
    if (n <= 0 || n > MAX_N) {
        printf("Invalid input. Please enter a value between 1 and %d.\n", MAX_N);
        return 1;
    }
    
    solution_count = 0;
    solve_nqueens(1, n);
    
    printf("Total solutions: %d\n", solution_count);
    return 0;
}