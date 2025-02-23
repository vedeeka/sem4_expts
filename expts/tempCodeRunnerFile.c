#include <stdio.h>

void printArray(int a[], int i, int j) {
    printf("Subarray: ");
    for (int k = i; k <= j; k++) {
        printf("%d ", a[k]);
    }
    printf("\n");
}

void MinMax(int i, int j, int *max, int *min, int a[]) {
    int mid, max1, min1;
    printArray(a, i, j); // Print the current subarray
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
    printf("Current min: %d, Current max: %d\n", *min, *max); // Print the current min and max
}

int main() {
    int n, i;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    int a[n];
    printf("Enter the elements of the array:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int max, min;
    MinMax(0, n - 1, &max, &min, a);

    printf("The maximum element in the array is: %d\n", max);
    printf("The minimum element in the array is: %d\n", min);

    return 0;
}