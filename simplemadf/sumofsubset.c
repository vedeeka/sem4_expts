#include <stdio.h>

#define MAX 50

int w[MAX], x[MAX];
int n, m;

void SumOfSub(int s, int k, int r) {
    x[k] = 1;
    if (s + w[k] == m) {

        printf("Subset: ");
        for (int i = 1; i <= k; i++) {
            if (x[i])
                printf("%d ", w[i]);
        }
        printf("\n");
    }
    else if (s + w[k] + w[k+1] <= m) {
        SumOfSub(s + w[k], k + 1, r - w[k]);
    }

    if ((s + r - w[k] >= m) && (s + w[k+1] <= m)) {
        x[k] = 0;
        SumOfSub(s, k + 1, r - w[k]);
    }
}

int main() {
    int sum = 0;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter the elements (in increasing order):\n");
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w[i]);
        sum += w[i];
    }

    printf("Enter the required sum: ");
    scanf("%d", &m);

    if (w[1] > m || sum < m) {
        printf("No solution possible.\n");
        return 0;
    }

    printf("Subsets with sum %d are:\n", m);
    SumOfSub(0, 1, sum);

    return 0;
}
