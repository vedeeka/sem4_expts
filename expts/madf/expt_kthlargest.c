#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void print(char **arr, int size, int low, int pivot, int high) {
    printf("\n[ ");
    for (int i = 0; i < size; i++) {
        if (i == low) {
            printf("| ");
        }
        printf("%s", arr[i]);
        if (i == pivot) {
            printf(" (pivot)");
        }
        if (i == high) {
            printf(" |");
        }
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf(" ]");
}


void swap(char **a, int i, int j) {
    char *temp = a[j];
    a[j] = a[i];
    a[i] = temp;
}

int partition(char **a, int low, int up, int size) {
    int i = low;
    int j = up + 1;
    char *pivot = a[low];

    do {

        do {
            i++;
        } while (i <= up  && strcmp(a[i], pivot) > 0);


        do {
            j--;
        } while (strcmp(a[j], pivot) < 0);

        if (i < j) {
            swap(a, i, j);
            print(a, size, low, low, up); 
        } else {
            break;
        }
    } while (i < j);


    swap(a, low, j);
    print(a, size, low, j, up); 
    printf(" (Pivot position: %d)", j);
    return j;
}


void select(char **a, int high, int k) {
    int low = 0;
    int n = high - 1;

    while (low <= n) {
        int p = partition(a, low, n, high);

        if (p == k - 1) {
            return; 
        } else if (p > k - 1) {
            n = p - 1; 
        } else {
            low = p + 1; 
        }
    }
}


int main() {
    int k, n;

    printf("Enter the kth place: ");
    scanf("%d", &k);

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    char **a = malloc(n * sizeof(char *));
    for (int h = 0; h < n; h++) {
        a[h] = malloc(1000 * sizeof(char));
    }

    printf("Enter the elements: ");
    for (int h = 0; h < n; h++) {
        scanf("%s", a[h]);
    }

    printf("Array transformations during selection:");
    clock_t t; 
    t = clock();
    select(a, n, k);
        t = clock() - t;
    
    double time_taken = ((double)t)/CLOCKS_PER_SEC; 

    printf("\n\nThe %dth largest element is: %s\n", k, a[k - 1]);
    printf("select fun() took %f seconds to execute \n", time_taken);  
    for (int h = 0; h < n; h++) {
        free(a[h]);
    }
    free(a);

    return 0;
}
