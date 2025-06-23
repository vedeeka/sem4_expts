#include <stdio.h>

#define MAX 100

int a[MAX], b[MAX]; // Global arrays

// Merge function: merges two sorted subarrays into one
void Merge(int low, int mid, int high) {
    int h = low, i = low, j = mid + 1;

    while (h <= mid && j <= high) {
        if (a[h] <= a[j])
            b[i++] = a[h++];
        else
            b[i++] = a[j++];
    }

    if (h > mid) {
        for (int k = j; k <= high; k++)
            b[i++] = a[k];
    } else {
        for (int k = h; k <= mid; k++)
            b[i++] = a[k];
    }

    for (int k = low; k <= high; k++)
        a[k] = b[k];
}

// Recursive Merge Sort
void MergeSort(int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        MergeSort(low, mid);
        MergeSort(mid + 1, high);
        Merge(low, mid, high);
    }
}

int main() {
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    MergeSort(0, n - 1);

    printf("Sorted array:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");
    return 0;
}
