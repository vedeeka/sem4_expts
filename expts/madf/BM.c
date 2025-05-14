#include <stdio.h>
#include <string.h>

#define MAX_CHAR 256

void computeLast(char *P, int last[]) {
    for (int i = 0; i < MAX_CHAR; i++) {
        last[i] = -1;
    }
    for (int i = 0; P[i] != '\0'; i++) {
        last[(int)P[i]] = i;
    }
}

void printWithHighlight(char *text, int start, int end, int highlight_start, int highlight_end) {
    printf("|");
    for (int i = start; i <= end; i++) {
        if (i >= highlight_start && i <= highlight_end) {
            printf(" %c |", text[i]);
        } else {
            printf(" %c |", text[i]);
        }
    }
    printf("\n");
}

int BM_Match(char *T, char *P) {
    int n = strlen(T);
    int m = strlen(P);
    int last[MAX_CHAR];
    int step = 1;

    computeLast(P, last);

    printf("Last occurrence table:\n");
    for (int ch = 'a'; ch <= 'z'; ch++) {
        if (last[ch] != -1) {
            printf("last['%c'] = %d\n", ch, last[ch]);
        }
    }
    printf("\n");

    printf("Text: ");
    printWithHighlight(T, 0, n - 1, -1, -1);
    printf("\n");

    int i = m - 1;
    int j = m - 1;

    while (i <= n - 1) {
        printf("Step %d:\n", step++);

        printf("      ");
        for (int k = 0; k < i - j; k++) {
            printf("    ");
        }
        printWithHighlight(P, 0, m - 1, j, j);

        while (P[j] == T[i]) {
            if (j == 0) {
                printf("      ");
                for (int k = 0; k < i; k++) 
                    printf("    ");
                printWithHighlight(P, 0, m - 1, 0, m - 1);
                printf("Match found at position %d.\n", i);
                return i;
            }
            i--;
            j--;
        }

        int l = last[(int)T[i]];
        int shift = m - ((j < 1 + l) ? j : 1 + l);
        printf("i = %d, j = %d, last['%c'] = %d, shift = %d\n", i, j, T[i], l, shift);
        i = i + shift;
        j = m - 1;

        printf("\n");
    }

    return -1;
}

int main() {
    char text[100], pattern[100];
    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter the pattern: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = '\0';

    printf("\nText: %s\n", text);
    printf("Pattern: %s\n\n", pattern);

    int pos = BM_Match(text, pattern);

    if (pos != -1) {
        return 0;
    } else {
        printf("There is no substring of T matching P.\n");
    }

    return 0;
}
