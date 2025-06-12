#include <stdio.h>
#include <string.h>
#include <time.h>
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

void printT(char T[]) {
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

void printP(char P[], int pos, int i, int j, int tempi, int tempj, int comp, int *cc) {
    int m = strlen(P), k;
    int tc = comp - (*cc);

    for (k = 0; k < pos * 4 + 4; k++) printf(" ");
    for (k = 0; k < m; k++) printf("%3d ", k);
    printf("\t\ti = %-5d j = %-5d\n", tempi, tempj);

    for (k = 0; k < pos * 4 + 4; k++) printf(" ");
    for (k = 0; k < m; k++) printf("----");
    printf("-\n");

    for (k = 0; k < pos * 4; k++) printf(" ");
    printf("P = |");
    for (k = 0; k < m; k++) printf(" %c |", P[k]);
    printf("\t\ti = %-5d j = %-5d\n", i, j);

    for (k = 0; k < pos * 4 + 4; k++) printf(" ");
    for (k = 0; k < m; k++) printf("----");
    printf("-\n");

    for (k = 0; k < pos * 4 + 4 + tempj * 4; k++) printf(" ");
	for (k = 0; k < tc; k++)
    	printf("%3d ", ++(*cc));
    printf ("\n\n");
}

int KMPMatch(char T[], char P[]) {
    int n = strlen(T), m = strlen(P), f[MAX];
    int i = 0, j = 0, comp = 0, cc = 0, tempi = 0, tempj = 0;

    KMPFailureFunction(P, f);
    printT(T);

    while (i < n) {
    	if (T[i] == P[j]) {
        	if (j == m - 1) {
        		comp++;	
        		printP(P, i - j, i, j, tempi, tempj, comp, &cc);
            	printf("Pattern found at index %d\n", i - m + 1);
            	printf("Total number of comparisons = %d\n", comp);
            	return i - m + 1;
        	} else {
        		comp++;
        		i++;
        		j++;
			}
    	} else {
    		comp++;
    		printP(P, i - j, i, j, tempi, tempj, comp, &cc);
        	if (j > 0)
           		j = f[j - 1];
        	else
           		i++;
           	tempi = i;
			tempj = j;
		}	
    }
	printf("There is no substring of T matching P.\n");
    printf("Total number of comparisons = %d\n", comp);
    return -1;
}

int main() {
    char text[MAX], pattern[MAX];
    struct timespec start, end;
    double time_taken;
    
    printf("Enter the text: ");
    scanf("%s", text);
    printf("Enter the pattern: ");
    scanf("%s", pattern);
	
	clock_gettime(CLOCK_MONOTONIC, &start);
    KMPMatch(text, pattern);
    clock_gettime(CLOCK_MONOTONIC, &end);
    
    time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) / 1e6;
    
    printf("\nTime Taken: %.6f milliseconds\n", time_taken);
}
