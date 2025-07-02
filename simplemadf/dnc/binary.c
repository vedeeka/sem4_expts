#include <stdio.h>

// Recursive Binary Search function
int BinarySearch(int a[], int i, int l, int x) {

        int mid = (i + l) / 2;

        if (x == a[mid])
            return mid;
        else if (x < a[mid])
            return BinarySearch(a, i, mid - 1, x);
        else
            return BinarySearch(a, mid + 1, l, x);
    
}

int main() {
    int a[100], n, x, result;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter sorted array elements:\n");
    for (int i = 1; i <= n; i++) // Note: indexing from 1
        scanf("%d", &a[i]);

    printf("Enter the element to search: ");
    scanf("%d", &x);

    result = BinarySearch(a, 1, n, x);

    if (result != 0)
        printf("Element %d found at position %d\n", x, result);
    else
        printf("Element %d not found\n", x);

    return 0;
}
