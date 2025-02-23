#include <stdio.h>
#include <limits.h>
#define INF INT_MAX

int k = 1, l;

void showmst(int n, int t[][2]) {
    printf("\nThe edges of the Minimum Spanning Tree (MST) are:\n");
    for (int i = 0; i < n - 1; i++) {
        printf("%d - %d\n", t[i][0], t[i][1]);
    }
}

void displayTable(int size, int near[], int cost[][10], int iter) {
    printf("\nIteration %d:\n", iter);
    printf("Vertex  Near  Cost[v,near[v]]\n");
    printf("-------------------------\n");
    for (int i = 1; i <= size; i++) {
        if (near[i] != 0) {
            printf("%d\t%d\t%d\n", i, near[i], cost[i][near[i]]);
        }
    }
}

void showcost(int cost[][10], int n) {
    printf("\nThe cost adjacency matrix is:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (cost[i][j] == INF) {
                printf("0 ");
            } else {
                printf("%d ", cost[i][j]);
            }
        }
        printf("\n");
    }
}

int prims(int t[][2], int size, int cost[][10], int near[]) {
    int mincost = cost[k][l];
    t[0][0] = k;
    t[0][1] = l;
    
    for (int i = 1; i <= size; i++) {
        if (cost[i][l] < cost[i][k]) {
            near[i] = l;
        } else {
            near[i] = k;
        }
    }
    near[k] = 0;
    near[l] = 0;
    
    displayTable(size, near, cost, 0);
    
    for (int j = 1; j < size - 1; j++) {
        int min = INF;
        int nextVertex = -1;
        for (int i = 1; i <= size; i++) {
            if (near[i] != 0 && cost[i][near[i]] < min) {
                min = cost[i][near[i]];
                nextVertex = i;
            }
        }
        t[j][0] = nextVertex;
        t[j][1] = near[nextVertex];
        mincost += cost[nextVertex][near[nextVertex]];
        near[nextVertex] = 0;
        
        for (int i = 1; i <= size; i++) {
            if (near[i] != 0 && cost[i][near[i]] > cost[i][nextVertex]) {
                near[i] = nextVertex;
            }
        }
        displayTable(size, near, cost, j);
    }
    
    showcost(cost, size);
    showmst(size, t);
    return mincost;
}


int main() {
   int n;
   int cost[10][10];
   int t[10][2];
   int near[10];


   printf("Enter the number of vertices: ");
   scanf("%d", &n);


   printf("Enter the cost adjacency matrix (use 0 for no edge):\n");
   for (int i = 1; i <= n; i++) {
       for (int j = 1; j <= n; j++) {
           cost[i][j] = INF;
       }
   }


   printf("Enter the edges and their costs (enter -1 -1 to stop):\n");
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
   }


   // find the smallest cost edge connected to
   int min = INF;
   for (int i = 1; i <= n; i++) {
       for (int j = 1; j <= n; j++) {
           if (cost[i][j] < min) {
               min = cost[i][j];
               k = i;
               l = j;
           }
       }
   }


   int mincost = prims(t, n, cost, near);




   printf("\n");




   printf("The minimum cost is: %d\n", mincost);


   return 0;
}





