#include <stdio.h>
#include <time.h>
#define MAX 10
#define INF 999

int distance[MAX][MAX], path[MAX];
int predecessor[MAX];
int n;

void print_path(int src, int dest) {
    if (dest == src) {
        printf("%d", src+1);
        return;
    }
    if (predecessor[dest] == -1) {
        printf("No path");
        return;
    }
    print_path(src, predecessor[dest]);
    printf("->%d", dest+1);
}

void singlesource_sp(int v) {
    int temp[MAX], i, j, k;
    for(i=0; i<n; i++) {
        path[i] = distance[v][i];
        if (distance[v][i] != INF && i != v)
            predecessor[i] = v;
        else
            predecessor[i] = -1;
    }
    for(k=1; k<n; k++) {
        for(i=0; i<n; i++)
            temp[i] = path[i];
        for(i=0; i<n; i++) {
            if(i != v) {
                for(j=0; j<n; j++) {
                    if(distance[j][i] != INF && path[j] != INF) {
                        if(path[i] > path[j] + distance[j][i]) {
                            path[i] = path[j] + distance[j][i];
                            predecessor[i] = j;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int i, j, origin, destin, weight, v;

    printf("Enter number of nodes\n");
    scanf("%d", &n);

    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
            distance[i][j] = (i == j) ? 0 : INF;

    printf("Enter edges as origin destination weight\n");
    while(1) {
        scanf("%d %d %d", &origin, &destin, &weight);
        if(origin == -1 && destin == -1 && weight == -1)
            break;
        if(origin > n || destin > n || origin <= 0 || destin <= 0)
            printf("Invalid edge\n");
        else
            distance[origin-1][destin-1] = weight;
    }

    printf("Enter starting vertex\n");
    scanf("%d", &v);
    if(v <= 0 || v > n) {
        printf("Invalid starting vertex\n");
        return 1;
    }

    singlesource_sp(v-1);

    for (i = 0; i < n; i++) {
        if (i != v-1) {
            if (path[i] == INF) {
                printf("No path\n");
            } else {
                printf("%d\n", path[i]);
                print_path(v-1, i);
                printf("\n");
            }
        }
    }

    return 0;
}
