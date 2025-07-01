#include <stdio.h>
#include <string.h>
#define MAX 1000

void KMPFailureFunction(char P[], int f[]) {
    int m = strlen(P), i = 1, j = 0;
    f[0] = 0;
    while (i < m) {
        if (P[i] == P[j]) {
            f[i] = j + 1;
            i++;
            j++;
        } else if (j > 0) {
            j = f[j - 1];
        } else {
            f[i] = 0;
            i++;
        }
    }
}

int KMPMatch(char T[], char P[]) {
    int n = strlen(T), m = strlen(P), f[MAX];
    int i = 0, j = 0;

    KMPFailureFunction(P, f);

    while (i < n) {
        if (T[i] == P[j]) {
            if (j == m - 1) {
                return i - m + 1;  // Pattern found
            } else {
                i++;
                j++;
            }
        } else {
            if (j > 0)
                j = f[j - 1];
            else
                i++;
        }
    }

    return -1;  // Pattern not found
}

int main() {
    char text[MAX], pattern[MAX];

    printf("Enter the text: ");
    scanf(" %[^\n]", text);

    printf("Enter the pattern to search: ");
    scanf(" %[^\n]", pattern);

    int index = KMPMatch(text, pattern);

    if (index != -1) {
        printf("Pattern found at index %d\n", index);
    } else {
        printf("Pattern not found in the text.\n");
    }

    return 0;
}
