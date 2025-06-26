#include<stdio.h>

int L[12][12];

int lsc(char x[], char y[]) {
    for (int i = 0; i <= 12; i++) {
        L[i][0] = 0;
    }
    for (int i = 0; i <= 10; i++) {
        L[0][i] = 0;
    }

    for (int i = 1; i < 12; i++) {
        for (int j = 1; j < 10; j++) {
            if (x[j] == y[i]) {
                L[i][j] = L[i - 1][j - 1] + 1;
            } else {
                int max;
                if (L[i - 1][j] > L[i][j - 1]) {
                    max = L[i - 1][j];
                } else {
                    max = L[i][j - 1];
                }
                L[i][j] = max;
            }
        }
    }

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%d ", L[i][j]);
        }
        printf(" \n");
    }

    // Backtrack to find LCS
    int i = 11, j = 9;
    char lcs[12]; // Max LCS size is min(10,12)
    int index = 0;

    while (i > 0 && j > 0) {
        if (y[i] == x[j]) {
            lcs[index++] = x[j];
            i--;
            j--;
        } else if (L[i - 1][j] > L[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    printf("LCS: ");
    for (int k = index - 1; k >= 0; k--) {
        printf("%c", lcs[k]);
    }
    printf("\n");

    return 0;
}

int main() {
    char t1[10] = { 'g','t','t','c','c','t','a','a','t','a' };
    char t2[12] = { 'c','g','a','t','a','a','t','t','g','a','g','a' };

    lsc(t1, t2);
}
