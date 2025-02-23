#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

void printArray(char *a[], int low, int high) {
    printf("[");
    for (int i = low; i <= high; i++) {
        printf("\"%s\"", a[i]);
        if (i < high) {
            printf(", ");
        }
    }
    printf("]\n");
}

int BinarySearch(char *a[], int n, char *x) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        printf("\nCurrent list segment: ");
        printArray(a, low, high);
        printf("low :%d ,mid index: %d ,up: %d, mid value: \"%s\"\n", low,mid,high, a[mid]);
        
        int cmp = strcmp(x, a[mid]);
        if (cmp < 0) {
            printf("Element \"%s\" is less than \"%s\", searching the left half\n", x, a[mid]);
            high = mid - 1;
        } else if (cmp > 0) {
            printf("Element \"%s\" is greater than \"%s\", searching the right half\n", x, a[mid]);
            low = mid + 1;
        } else {
            printf("Element \"%s\" found at index %d\n", x, mid);
            return mid;
        }
    }
    printf("Element \"%s\" is not present in the array\n", x);
    return -1; // Not Found
}

int main() {
    int n;
    char x[100];
    printf("Enter number of elements: ");
    scanf("%d", &n);
    char *a[n];
    printf("Enter %d elements (sorted in ascending order):\n", n);
    for (int i = 0; i < n; i++) {
        a[i] = (char *)malloc(100 * sizeof(char)); // Allocate memory for each string
        scanf("%s", a[i]);
    }
    printf("Enter the element to search: ");
    scanf("%s", x);
    clock_t t; 
    t = clock();
    int result = BinarySearch(a, n, x);
    if (result != -1)
        printf("Element is present at index %d\n", result);
    else
        printf("Element is not present in array\n");
    t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 

    printf("BinarySearch fun() took %f seconds to execute \n", time_taken);     

    for (int i = 0; i < n; i++) {
        free(a[i]); // Free allocated memory
    }

    return 0;
}
