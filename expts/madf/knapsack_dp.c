#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

struct Pair {
    float p, w;
};

int n, m, b[MAX], x[MAX];
float profit[MAX], weight[MAX];
struct Pair pair[MAX * MAX];

int Largest(struct Pair pair[], float weight[], int t, int h, int i, int m) {
    int low = t, high = h, mid, index = h;
    
    while (low <= high) {
        mid = low + (high - low) / 2;
        if (pair[mid].w + weight[i] <= m) {
            index = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return index;
}

void TraceBack(float profit[], float weight[], struct Pair pair[], int x[], int m, int n) {
    int i = n, j = b[n], k;
    float p = pair[b[n + 1] - 1].p, w = pair[b[n + 1] - 1].w;
    
    printf("\nTracing back to identify selected items:\n");
    printf("---------------------------------------------------\n");
    
    while (i >= 1) {
        int found = 0;
        for (k = b[i - 1]; k < b[i]; k++) {
            if (pair[k].p == p && pair[k].w == w) {
                printf("(%.0f, %.0f) belongs to S%d\t\tx%d = 0\n", p, w, i - 1, i);
                x[i] = 0;
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("(%.0f, %.0f) does not belong to S%d\tx%d = 1\n", p, w, i - 1, i);
            x[i] = 1;
            p = p - profit[i];
            w = w - weight[i];
        }
        i--;
    }
    
    printf("\nFinal solution vector: [");
    for (i = 1; i <= n; i++) {
        printf("%d", x[i]);
        if (i < n) printf(", ");
    }
    printf("]\n");
    
    float totalProfit = 0, totalWeight = 0;
    printf("\nSelected items: ");
    for (i = 1; i <= n; i++) {
        if (x[i] == 1) {
            printf("%d ", i);
            totalProfit += profit[i];
            totalWeight += weight[i];
        }
    }
    printf("\nTotal profit: %.0f\n", totalProfit);
    printf("Total weight: %.0f\n", totalWeight);
}

void DKnap(float p[], float w[], int x[], int n, int m) {
    int next, t, h, k, u, i, j, z;
    
    printf("Dynamic Programming Knapsack Algorithm\n");
    printf("======================================\n\n");
    
    // Initialize
    b[0] = 0;
    pair[0].p = 0;
    pair[0].w = 0;
    next = 1;
    t = 0;
    h = 0;
    b[1] = 1;
    
    printf("Initial S0 = {(0, 0)}\n\n");
    
    // Main loop for each item
    for (i = 1; i <= n; i++) {
        printf("Iteration %d:\n", i);
        printf("-----------\n");
        
        int temp_next = next;
        k = t;
        u = Largest(pair, w, t, h, i, m);
        
        printf("Current set S%d = {", i-1);
        for (z = b[i-1]; z < b[i]; z++) {
            printf("(%.0f, %.0f)", pair[z].p, pair[z].w);
            if (z != b[i] - 1) printf(", ");
        }
        printf("}\n");
        
        // Generate new pairs by including item i
        struct Pair npair[MAX];
        int npc = 0;
        
        for (j = t; j <= u; j++) {
            float pp = pair[j].p + p[i];
            float ww = pair[j].w + w[i];
            
            if (ww <= m) {
                npair[npc].p = pp;
                npair[npc].w = ww;
                npc++;
            }
        }
        
        printf("Set after including item %d (S%d(1)) = {", i, i-1);
        for (z = 0; z < npc; z++) {
            printf("(%.0f, %.0f)", npair[z].p, npair[z].w);
            if (z != npc - 1) printf(", ");
        }
        printf("}\n");
        
        // Merge and eliminate dominated pairs
        struct Pair merged[MAX];
        int mc = 0;
        k = t;
        z = 0;
        
        // Merge step
        while (k <= h && z < npc) {
            if (pair[k].w < npair[z].w) {
                merged[mc++] = pair[k++];
            } else if (pair[k].w > npair[z].w) {
                merged[mc++] = npair[z++];
            } else {
                if (pair[k].p > npair[z].p) 
                    merged[mc++] = pair[k++];
                else 
                    merged[mc++] = npair[z++];
            }
        }
        
        while (k <= h) merged[mc++] = pair[k++];
        while (z < npc) merged[mc++] = npair[z++];
        
        // Eliminate dominated pairs
        next = b[i];
        pair[next++] = merged[0];
        
        for (j = 1; j < mc; j++) {
            if (merged[j].w > pair[next-1].w && merged[j].p > pair[next-1].p) {
                pair[next++] = merged[j];
            }
        }
        
        t = b[i];
        h = next - 1;
        b[i+1] = next;
        
        printf("Final set after merging and eliminating dominated pairs S%d = {", i);
        for (z = b[i]; z < next; z++) {
            printf("(%.0f, %.0f)", pair[z].p, pair[z].w);
            if (z != next - 1) printf(", ");
        }
        printf("}\n\n");
    }
    
    // Print optimal solution
    printf("Optimal solution found: (%.0f, %.0f)\n", pair[next-1].p, pair[next-1].w);
    
    // Traceback to find selected items
    TraceBack(p, w, pair, x, m, n);
}

int main() {
    int i;
    struct timespec start, end;
    double time_taken;
    
    printf("Enter the number of elements in Knapsack: ");
    scanf("%d", &n);
    
    printf("Enter the Maximum Size of Knapsack: ");
    scanf("%d", &m);
    
    printf("Enter Profits: ");
    for (i = 1; i <= n; i++) 
        scanf("%f", &profit[i]);
    
    printf("Enter Weights: ");
    for (i = 1; i <= n; i++) 
        scanf("%f", &weight[i]);
    
    printf("\n\n");
    
    clock_gettime(CLOCK_MONOTONIC, &start);
    DKnap(profit, weight, x, n, m);
    clock_gettime(CLOCK_MONOTONIC, &end);
    
    time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) / 1e6;
    
    printf("\nTime Taken: %.6f milliseconds\n", time_taken);
    
    return 0;
}