#include <stdio.h>
#include <string.h>
#include <time.h>
typedef struct {
    int u, v, w;
} Edge;

int parent[100];

void adjust(Edge a[], int i, int n) {
    int j = 2 * i;
    Edge item = a[i];
    while (j <= n) {
        if ((j < n) && (a[j].w > a[j + 1].w || 
            (a[j].w == a[j + 1].w && a[j].u > a[j + 1].u))) {
            j = j + 1;
        }
        if (item.w <= a[j].w && 
            (item.w < a[j].w || item.u <= a[j].u)) {
            break;
        }
        a[j / 2] = a[j];
        j = 2 * j;
    }
    a[j / 2] = item;
}
Edge deleteMin(Edge a[], int *n) {
    if (*n == 0) {
        printf("Heap is empty\n");
        Edge empty = {-1, -1, -1};
        return empty;
    }
    Edge item = a[1];
    a[1] = a[*n];
    (*n)--;
    adjust(a, 1, *n);
    return item;
}

void showmst(int n, Edge t[]) {
    printf("The edges of the Minimum Spanning Tree (MST) are:\n");
    for (int i = 0; i < n - 1; i++) {
        printf("%d - %d (Weight: %d)\n", t[i].u, t[i].v, t[i].w);
    }
}


int find(int i) {
    while (parent[i] != i) {
        parent[i] = parent[parent[i]]; // Path compression optimization
        i = parent[i];
    }
    return i;
}

void unions(int i, int j) {
    parent[i] = j;
}

void krushkal(Edge t[], int n, Edge a[], int edgeCount) {
    adjust(a, 1, edgeCount);
    int mincost = 0;
    int i = 0;
    while (i < n - 1 && edgeCount > 0) {
        Edge e = deleteMin(a, &edgeCount);
        int j = find(e.u);
        int k = find(e.v);
        if (j != k) {
            t[i] = e;
            mincost += e.w;
            unions(j, k);
            i++;
        }
    }
    if (i != n - 1) {
        printf("The graph is not connected, MST cannot be formed.\n");
        return;
    }
    showmst(n, t);
    printf("Minimum cost of spanning tree: %d\n", mincost);
}
int main(){
    int n;
    Edge t[100], a[100];
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    int edgeCount = 0;
    printf("Enter the cost adjacency matrix (use 0 for no edge):\n");
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        for (int j = 1; j <= n; j++) {
            int w;
            scanf("%d", &w);
            if (w != 0) {
                a[edgeCount].u = i;
                a[edgeCount].v = j;
                a[edgeCount].w = w;
                edgeCount++;
            }
        }
    }
    krushkal(t, n, a, edgeCount);
    return 0;
}