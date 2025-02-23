#include <stdio.h>
#include <time.h> 
void printArray(int a[], int i, int j) {
    printf("  i: %d , j: %d \n", i, j);



}

void MinMax(int i, int j, int *max, int *min, int a[]) {
    int mid, max1, min1;
    if (i == j) {
        *max = *min = a[i];
    } else if (i == j - 1) {
        if (a[i] < a[j]) {
            *max = a[j];
            *min = a[i];
        } else {
            *max = a[i];
            *min = a[j];
        }
    } else {
        mid = (i + j) / 2;
        MinMax(i, mid, max, min, a);
        MinMax(mid + 1, j, &max1, &min1, a);
        if (*max < max1) *max = max1;
        if (*min > min1) *min = min1;
    }
    
    printArray(a, i, j); 
    printf("min: %d,  max: %d\n", *min, *max);
    printf("\n \n");
}

int main() {
    int n, i;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    int a[n];
    printf("Enter the elements of the array:\n");
    for (i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    int max, min;
    clock_t t; 
    t = clock();
    MinMax(1, n, &max, &min, a);

    printf("\nFinal Results:\n");
    printf("The maximum element in the array is: %d\n", max);
    printf("The minimum element in the array is: %d\n", min);
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 

    printf("BinarySearch fun() took %f seconds to execute \n", time_taken);  

    return 0;
}
