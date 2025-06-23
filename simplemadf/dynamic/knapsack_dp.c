#include <stdio.h>

#define MAX 100

typedef struct {
    int p; // profit
    int w; // weight
} Pair;

Pair pair[MAX];   // Array to store profit-weight pairs
int b[MAX];       // Boundary markers for each Si
int next = 2;     // Next free position in pair array

// Function to get the largest index 'u' in S(i-1) such that
// weight + w[i] <= capacity (m)
int Largest(Pair pair[], int w[], int t, int h, int i, int m) {
    int u = h;
    for (int j = h; j >= t; j--) {
        if (pair[j].w + w[i] <= m)
            return j;
    }
    return t - 1;
}

void DKnap(int p[], int w[], int x[], int n, int m) {
    int t = 1, h = 1; // Start and end of S0

    // Initialize S0
    b[0] = 1;
    pair[1].p = 0;
    pair[1].w = 0;
    b[1] = next;

    for (int i = 1; i <= n; i++) {
        int k = t;
        int u = Largest(pair, w, t, h, i, m);
        for (int j = t; j <= u; j++) {
            int pp = pair[j].p + p[i];
            int ww = pair[j].w + w[i];

            // Merge while pair[k].w < ww
            while ((k <= h) && (pair[k].w < ww)) {
                pair[next] = pair[k];
                next++;
                k++;
            }

            if ((k <= h) && (pair[k].w == ww)) {
                if (pp > pair[k].p)
                    pair[k].p = pp;
                k++;
            } else {
                if (pp > pair[next - 1].p) {
                    pair[next].p = pp;
                    pair[next].w = ww;
                    next++;
                }
            }

            while ((k <= h) && (pair[k].p <= pair[next - 1].p))
                k++;
        }

        // Add remaining from Si-1
        while (k <= h) {
            pair[next] = pair[k];
            next++;
            k++;
        }

        // Prepare for Si+1
        t = h + 1;
        h = next - 1;
        b[i + 1] = next;
    }

    printf("\nOptimal (Profit, Weight) pairs in final set:\n");
    for (int i = t; i <= h; i++)
        printf("(%d, %d)\n", pair[i].p, pair[i].w);
}

int main() {
    int n, m;
    int p[MAX], w[MAX], x[MAX];

    // Sample input
    // You can change this for dynamic user input if needed
    n = 4; // Number of items
    m = 7; // Max weight capacity

    // Using 1-based indexing
    p[1] = 16; w[1] = 2;
    p[2] = 19; w[2] = 3;
    p[3] = 23; w[3] = 4;
    p[4] = 28; w[4] = 5;

    printf("Items:\n");
    for (int i = 1; i <= n; i++)
        printf("Item %d -> Profit: %d, Weight: %d\n", i, p[i], w[i]);

    DKnap(p, w, x, n, m);

    return 0;
}
