#include <stdio.h>
#include <string.h>

#define MAX_CHAR 256  
void computeLast(char *P, int last[]) {
    int i;
    for (i = 0; i < MAX_CHAR; i++) {
        last[i] = -1;  
    }
    for (i = 0; P[i] != '\0'; i++) {
        last[(int)P[i]] = i;  
    }
}

int BM_Match(char *T, char *P) {
    int n = strlen(T);
    int m = strlen(P);
    int last[MAX_CHAR];

    computeLast(P, last);

    int i = m - 1;
    int j = m - 1;

    while (i <= n - 1) {
        if (P[j] == T[i]) {
            if (j == 0) {
                return i;  
            } else {
                i--;
                j--;
            }
        } else {
            int l = last[(int)T[i]];
            i = i + m - ((j < 1 + l) ? j : 1 + l);  
            j = m - 1;
        }
    }

    return -1;  
}

int main() {
    char text[1000], pattern[100];

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);

    text[strcspn(text, "\n")] = '\0';

    printf("Enter the pattern to search: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = '\0';

    int pos = BM_Match(text, pattern);

    if (pos != -1) {
        printf("Pattern found at index %d\n", pos);
    } else {
        printf("Pattern not found in the text.\n");
    }

    return 0;
}