#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char str[100];
    int num;
} Element;

void merge(Element a[], int low, int mid, int high) {
    Element b[high - low + 1];
    int h = low, i = 0, j = mid + 1;

    while (h <= mid && j <= high) {
        if (strcmp(a[h].str, a[j].str) <= 0) {
            b[i] = a[h];
            h++;
        } else {
            b[i] = a[j];
            j++;
        }
        i++;
    }

    while (h <= mid) {
        b[i] = a[h];
        h++;
        i++;
    }

    while (j <= high) {
        b[i] = a[j];
        j++;
        i++;
    }

    for (int k = low; k <= high; k++) {
        a[k] = b[k - low];
    }



}

void mergeSort(Element arr[], int l, int r, int n) {
    if (l < r) {
        int m = l + (r - l) / 2;

      
        for (int i = 1; i <= n; i++) {
            if (i == l) printf("|");
            printf("%s(%d)", arr[i].str, arr[i].num);
            if (i == r) printf("");
            if (i < n) printf(", ");
        }
        printf("|\n");

        printf("low: %d, mid: %d, high: %d\n", l, m, r);

        mergeSort(arr, l, m, n);
        mergeSort(arr, m + 1, r, n);

        merge(arr, l, m, r);
    }
}

void printArray(Element arr[], int size) {
    printf("[");
    for (int i = 1; i < size; i++) {
        printf("%s(%d)", arr[i].str, arr[i].num);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    Element arr[n + 1];
    printf("Enter the elements (string and integer): ");
    for (int i = 1; i <= n; i++) {
        scanf("%s %d", arr[i].str, &arr[i].num);
    }

    printf("\nGiven array is: ");
    printArray(arr, n + 1);
    
    clock_t t; 
    t = clock();
   mergeSort(arr, 1, n, n);
    t = clock() - t;
    
    double time_taken = ((double)t)/CLOCKS_PER_SEC; 
    
    printf("\nSorted array is: ");
    printArray(arr, n + 1);
    printf("MergeSort fun() took %f seconds to execute \n", time_taken);  
    
    return 0;
}
