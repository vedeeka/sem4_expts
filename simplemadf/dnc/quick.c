#include <stdio.h>

#define MAX 100
int a[MAX];

// Function to swap two elements
void Interchange(int i, int j) {
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

// Partition function
int Partition(int m, int p) {
    int v = a[m];
    int i = m, j = p;

    while (1) {
        do {
            i++;
        } while (a[i] < v);

        do {
            j--;
        } while (a[j] > v);

        if (i < j)
            Interchange(i, j);
        else
            break;
    }

    a[m] = a[j];
    a[j] = v;
    return j;
}

// Recursive QuickSort function
void QuickSort(int p, int q) {
    if (p < q) {
        int j = Partition(p, q + 1);  // Adjusted as per the pseudocode
        QuickSort(p, j - 1);
        QuickSort(j + 1, q);
    }
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter array elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    QuickSort(0, n - 1);

    printf("Sorted array:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");

    return 0;
}
