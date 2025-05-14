#include <stdio.h>
#include <string.h>

#define MAX 100

void computeFailureFunction(char *P, int f[]) {
    int m = strlen(P);
    int i = 1, j = 0;

    f[0] = 0;

    while (i < m) {
        if (P[j] == P[i]) {
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


void printWithHighlight(char *text, int start, int end, int highlight_start, int highlight_end) {
    printf("|");
    for (int i = start; i <= end; i++) {
        if (i >= highlight_start && i <= highlight_end) {
            printf(" %c* |", text[i]);
        } else {
            printf(" %c |", text[i]);
        }
    }
    printf("\n");
}

int KMP_Match(char *T, char *P) {
    int n = strlen(T);
    int m = strlen(P);
    int f[MAX];
    int step = 1;

    computeFailureFunction(P, f);

    printf("Failure function:\n");
    for (int i = 0; i < m; i++) {
        printf("f[%d] = %d\n", i, f[i]);
    }
    printf("\nText: ");
    printWithHighlight(T, 0, n - 1, -1, -1);
    printf("\n");

    int i = 0, j = 0;
    while (i < n) {
        if (T[i] == P[j]) {
            i++;
            j++;
            if (j == m) {
                // Print step and match alignment only once, when match is complete
                printf("Step %d:\n", step++);
                printf("i = %d, j = %d\n", i, j);
                printf("      ");
                for (int k = 0; k < i - j; k++) {
                    printf("    ");
                }
                printWithHighlight(P, 0, m - 1, 0, m - 1);
                printf("Match found at position %d.\n", i - m);
                return i - m;
            }
        } else {
            printf("Step %d:\n", step++);
            printf("i = %d, j = %d\n", i, j);
            printf("      ");
            for (int k = 0; k < i - j; k++) {
                printf("    ");
            }
            printWithHighlight(P, 0, m - 1, j, j);

            if (j != 0) {
               
                j = f[j - 1];
            } else {
                
                i++;
            }
            printf("\n");
        }
    }

    return -1;
}


int main() {
    char text[MAX], pattern[MAX];
    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter the pattern: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = '\0';

    printf("\nText: %s\n", text);
    printf("Pattern: %s\n\n", pattern);

    int pos = KMP_Match(text, pattern);

    if (pos == -1) {
        printf("There is no substring of T matching P.\n");
    }

    return 0;
}
