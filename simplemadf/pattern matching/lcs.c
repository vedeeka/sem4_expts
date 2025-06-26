#include <stdio.h>
#include <string.h>

int L[100][100];

void printLCS(char t1[], char t2[], int m, int n) {
    int i = m, j = n;
    char lcs[100];
    int index = L[m][n];
    lcs[index] = '\0';  // null-terminate the string
    index--;

    while (i > 0 && j > 0) {
        if (t1[i - 1] == t2[j - 1]) {
            lcs[index--] = t1[i - 1];
            i--; j--;
        } else if (L[i - 1][j] > L[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    printf("\nLongest Common Subsequence: %s\n", lcs);
}

int lsc(char t1[], char t2[], int m, int n) {
    for (int i = 0; i <= m; i++) L[i][0] = 0;
    for (int j = 0; j <= n; j++) L[0][j] = 0;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (t1[i - 1] == t2[j - 1]) {
                L[i][j] = L[i - 1][j - 1] + 1;
            } else {
                L[i][j] = (L[i - 1][j] > L[i][j - 1]) ? L[i - 1][j] : L[i][j - 1];
            }
        }
    }

    // Optional: Print LCS matrix
    printf("LCS Matrix:\n");
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            printf("%d ", L[i][j]);
        }
        printf("\n");
    }

    printLCS(t1, t2, m, n);
    return 0;
}

int main() {
    // Add null-terminated versions of the sequences
    char t1[] = "gttcctaata";         // length = 10
    char t2[] = "cgataattgaga";       // length = 12

    int m = strlen(t1);
    int n = strlen(t2);

    lsc(t1, t2, m, n);
    return 0;
}
