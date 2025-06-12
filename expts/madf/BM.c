#include <stdio.h>
#include <string.h>
#include <time.h>
#define MAX 256

void lastOccurence(char *P, int m, int last[]) {
    int i;
    for (i = 0; i < MAX; i++)
        last[i] = -1;
    for (i = 0; i < m; i++)
        last[(unsigned char)P[i]] = i;
}

void printT(char *T) {
    int n = strlen(T), i;
    printf("\n    ");
    for (i = 0; i < n; i++)
        printf("%3d ", i);
    printf("\n    ");
    for (i = 0; i < n; i++)
        printf("----");
    printf("-\nT = |");
    for (i = 0; i < n; i++)
        printf(" %c |", T[i]);
    printf("\n    ");
    for (i = 0; i < n; i++)
        printf("----");
    printf("-\n\n");
}

void printP(char *P, int shift, int i, int j, int l, int comp, int *cc) {
    int m = strlen(P);
    int s, k;

    for (s = 0; s < shift * 4 + 4; s++) printf(" ");
    for (k = 0; k < m; k++) printf("%3d ", k);
    printf("\n");

    for (s = 0; s < shift * 4 + 4; s++) printf(" ");
    for (k = 0; k < m; k++) printf("----");
    printf("-\n");

    for (s = 0; s < shift * 4; s++) printf(" ");
    printf("P = |");
    for (k = 0; k < m; k++) printf(" %c |", P[k]);
    printf("\t\t i = %d    j = %d    l = %d\n", i, j, l);

    for (s = 0; s < shift * 4 + 4; s++) printf(" ");
    for (k = 0; k < m; k++) printf("----");
    printf("-\n");

    int rpos = shift * 4 + 4 + j * 4;
    int nums[comp];
    for (k = 0; k < comp; k++)
        nums[k] = ++(*cc);

    for (s = 0; s < rpos; s++) printf(" ");
    for (k = comp - 1; k >= 0; k--) {
        printf("%3d ", nums[k]);
    }
    printf ("\n\n");
}

int BMMatch(char *T, char *P) {
    int n = strlen(T), m = strlen(P);
    int last[MAX], tc = 0, cc = 0;
    int s, j, comp, l;

    lastOccurence(P, m, last);
    printT(T);
    s = 0; 

    while (s <= n - m) {
        j = m - 1;
        comp = 0;
        while (j >= 0 && P[j] == T[s + j]) {
            comp++;
            j--;
        }
        l = last[(unsigned char)T[s + m - 1]];
        if (j < 0) {
            printP(P, s, s + j + 1, j + 1, l, comp, &cc);
            tc += comp;
            printf("Total number of comparisons = %d\n", tc);
            return s;
        } else {
            comp++;
            l = last[(unsigned char)T[s + j]];
            printP(P, s, s + j, j, l, comp, &cc);
            s += (j - l > 0) ? j - l : 1;
            tc += comp;
        }
    }
    printf("Total number of comparisons = %d\n", tc);
    return -1;
}

int main() {
    char T[100], P[100];
    struct timespec start, end;
    double time_taken;

    printf("Enter the text T: ");
    scanf("%s", T);
    printf("Enter the pattern P: ");
    scanf("%s", P);
	
	clock_gettime(CLOCK_MONOTONIC, &start);
    int index = BMMatch(T, P);
    clock_gettime(CLOCK_MONOTONIC, &end);
    
    time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) / 1e6;

    if (index != -1)
        printf("Pattern found at index %d\n", index);
    else
        printf("Pattern not found.\n");
	
	printf("\nTime Taken: %.6f milliseconds\n", time_taken);
}
