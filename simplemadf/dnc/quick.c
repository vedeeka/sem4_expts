#include <stdio.h>

#define MAX 100
#define INF 1000000000

int a[MAX];

void Interchange(int i, int j) {
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

// Hoare's Partition (you provided), adapted to 0-based indexing
int Partition(int m, int p) {
    int v = a[m];
    int i = m, j = p;

    while (1) {
        do {
            i++;
        } while (i <= p && a[i] < v);

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

// Select algorithm for k-th smallest element (0-based)
void Select(int n, int k) {
    int low = 0;
    int up = n;
    a[n] = INF;  // Sentinel at a[n], since input ends at a[n-1]

    while (1) {
        int j = Partition(low, up);

        if (k == j)
            return;
        else if (k < j)
            up = j;
        else
            low = j + 1;
    }
}

int main() {
    int n, k;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter k (0-based index of k-th smallest element): ");
    scanf("%d", &k);

    if (k < 0 || k >= n) {
        printf("Invalid k\n");
        return 1;
    }

    Select(n, k);

    printf("The %d-th smallest element is: %d\n", k, a[k]);

    printf("Array after Select (not fully sorted):\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");

    return 0;
}
