#include <stdio.h>

#define MAX 100
#define INF 1000000000

int a[MAX];  // Global array

void Interchange(int i, int j) {
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

// Hoare's Partition (as you gave)
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

// Select algorithm to find k-th smallest element
void Select(int n, int k) {
    int low = 1;
    int up = n + 1;
    a[n + 1] = INF; // Sentinel value

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

// Test
int main() {
    int n = 6, k = 4;

    // 1-based indexing (a[1..n])
    a[1] = 12;
    a[2] = 3;
    a[3] = 5;
    a[4] = 7;
    a[5] = 19;
    a[6] = 0;

    Select(n, k);

    printf("The %d-th smallest element is: %d\n", k, a[k]);

    printf("Array after Select:\n");
    for (int i = 1; i <= n; i++)
        printf("%d ", a[i]);
    printf("\n");

    return 0;
}
