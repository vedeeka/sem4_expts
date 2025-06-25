#include <stdio.h>
#include <math.h>
#include<stdlib.h>

#define MAX 20

int x[MAX];  
int Place(int k, int i) {
    for (int j = 1; j < k; j++) {
        if (x[j] == i || abs(x[j] - i) == abs(j - k))
            return 0; // Conflict
    }
    return 1; 
}

void NQueens(int k, int n) {
    for (int i = 1; i <= n; i++) {
        if (Place(k, i)) {
            x[k] = i;
            if (k == n) {
                // Print one solution
                for (int j = 1; j <= n; j++) {
                    printf("%d ", x[j]);
                }
                printf("\n");
            }
            else {
                NQueens(k + 1, n);
            }
        }
    }
}

int main() {
    int n;
    printf("Enter number of queens: ");
    scanf("%d", &n);

    printf("Solutions to %d-Queens problem:\n", n);
    NQueens(1, n);

    return 0;
}
