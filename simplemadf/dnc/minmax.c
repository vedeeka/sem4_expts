#include <stdio.h>

#define MAX 100

int a[MAX];

// Recursive function to find maximum and minimum
void MaxMin(int i, int j, int *max, int *min) {
    int mid, max1, min1;

    if (i == j) {
        *max = *min = a[i]; // Only one element
    } else if (i == j - 1) { // Two elements
        if (a[i] < a[j]) {
            *max = a[j];
            *min = a[i];
        } else {
            *max = a[i];
            *min = a[j];
        }
    } else {
        mid = (i + j) / 2;
        MaxMin(i, mid, max, min);               // First half
        MaxMin(mid + 1, j, &max1, &min1);       // Second half

        if (*max < max1) *max = max1;
        if (*min > min1) *min = min1;
    }
}

int main() {
    int n, max, min;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter array elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    MaxMin(0, n - 1, &max, &min);  // Call with full array range

    printf("Maximum element: %d\n", max);
    printf("Minimum element: %d\n", min);

    return 0;
}
