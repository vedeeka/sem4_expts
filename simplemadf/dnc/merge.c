
#include <stdio.h>

#define MAX 100

int a[MAX], b[MAX]; // Global arrays

void merge(int l, int m, int u) {
    int h = l, i = l, j = m + 1;

    while (h <= m && j <= u) {
        if (a[h] < a[j])
            b[i++] = a[h++];
        else
            b[i++] = a[j++];
    }

    if (h <= m) {
        for (int k = h; k <= m; k++)
            b[i++] = a[k];
    } else {
        for (int k = j; k <= u; k++)
            b[i++] = a[k];
    }

    // ✅ FIX: include u
    for (int i = l; i <= u; i++) {
        a[i] = b[i];
    }
}

void MergeSort(int l, int u) {
    if (l < u) {
        int m = (l + u) / 2;
        MergeSort(l, m);
        MergeSort(m + 1, u);
        merge(l, m, u);
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