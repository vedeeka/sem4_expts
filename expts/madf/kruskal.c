#include <stdio.h>
#include <string.h>

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

void heapify(Edge a[], int n) {
    for (int i = n / 2; i >= 1; i--) {
        adjust(a, i, n);
    }
}

Edge DelMin(Edge a[], int *n) {
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

int kruskal(Edge t[], int n, int cost[100][100], Edge a[], int edgeCount) {
    heapify(a, edgeCount);
    int mincost = 0;
    int i = 0;
    while ((i < n - 1) && (edgeCount > 0)) {
        Edge e = DelMin(a, &edgeCount);
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
        return -1;
    }
    
    return mincost;
}

int main() {
    Edge t[10];
    int cost[100][100] = {0};
    Edge a[100];
    int n, i, j;
    
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    
    for (i = 0; i < n; i++) {
        parent[i] = i;
    }
    
    printf("Enter the edges and their costs (enter -1 -1 to stop):\n");
    int edgeCount = 0;
    while (1) {
        int u, v, w;
        scanf("%d %d", &u, &v);
        if (u == -1 && v == -1) {
            break;
        }
        printf("Enter the cost of (%d, %d): ", u, v);
        scanf("%d", &w);
        cost[u][v] = w;
        cost[v][u] = w;
        a[++edgeCount] = (Edge){u, v, w};
    }
    
    printf("The cost adjacency matrix is:\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            printf("%d ", cost[i][j]);
        }
        printf("\n");
    }
    
    int mincost = kruskal(t, n, cost, a, edgeCount);
    if (mincost != -1) {
        showmst(n, t);
        printf("Minimum cost of spanning tree: %d\n", mincost);
    }
    
    return 0;
}



//easier way
// #include <stdio.h>
// #include <string.h>

// typedef struct {
//     int u, v, w;
// } Edge;

// int parent[100];

// void adjust(Edge a[], int i, int n) {
//     int j = 2 * i;
//     Edge item = a[i];
//     while (j <= n) {
//         if ((j < n) && (a[j].w > a[j + 1].w || 
//             (a[j].w == a[j + 1].w && a[j].u > a[j + 1].u))) {
//             j = j + 1;
//         }
//         if (item.w <= a[j].w && 
//             (item.w < a[j].w || item.u <= a[j].u)) {
//             break;
//         }
//         a[j / 2] = a[j];
//         j = 2 * j;
//     }
//     a[j / 2] = item;
// }

// void heapify(Edge a[], int n) {
//     for (int i = n / 2; i >= 1; i--) {
//         adjust(a, i, n);
//     }
// }

// Edge DelMin(Edge a[], int *n) {
//     if (*n == 0) {
//         printf("Heap is empty\n");
//         Edge empty = {-1, -1, -1};
//         return empty;
//     }
//     Edge item = a[1];
//     a[1] = a[*n];
//     (*n)--;
//     adjust(a, 1, *n);
//     return item;
// }

// void showmst(int n, Edge t[]) {
//     printf("The edges of the Minimum Spanning Tree (MST) are:\n");
//     for (int i = 0; i < n - 1; i++) {
//         printf("%d - %d (Weight: %d)\n", t[i].u, t[i].v, t[i].w);
//     }
// }

// int find(int i) {
//     while (parent[i] != i) {
//         parent[i] = parent[parent[i]]; // Path compression optimization
//         i = parent[i];
//     }
//     return i;
// }

// void unions(int i, int j) {
//     parent[i] = j;
// }

// int kruskal(Edge t[], int n, Edge a[], int edgeCount) {
//     heapify(a, edgeCount);
//     int mincost = 0;
//     int i = 0;
//     while ((i < n - 1) && (edgeCount > 0)) {
//         Edge e = DelMin(a, &edgeCount);
//         int j = find(e.u);
//         int k = find(e.v);
        
//         if (j != k) {
//             t[i] = e;
//             mincost += e.w;
//             unions(j, k);
//             i++;
//         }
//     }
    
//     if (i != n - 1) {
//         printf("The graph is not connected, MST cannot be formed.\n");
//         return -1;
//     }
    
//     return mincost;
// }

// int main() {
//     Edge t[10];
//     Edge a[100];
//     int n, i, edgeCount = 0;
    
//     printf("Enter the number of vertices: ");
//     scanf("%d", &n);
    
//     for (i = 0; i < n; i++) {
//         parent[i] = i;
//     }
    
//     printf("Enter the edges and their costs (enter -1 -1 to stop):\n");
//     while (1) {
//         int u, v, w;
//         scanf("%d %d", &u, &v);
//         if (u == -1 && v == -1) {
//             break;
//         }
//         printf("Enter the cost of (%d, %d): ", u, v);
//         scanf("%d", &w);
//         a[++edgeCount] = (Edge){u, v, w};
//     }
    
//     int mincost = kruskal(t, n, a, edgeCount);
//     if (mincost != -1) {
//         showmst(n, t);
//         printf("Minimum cost of spanning tree: %d\n", mincost);
//     }
    
//     return 0;
// }
