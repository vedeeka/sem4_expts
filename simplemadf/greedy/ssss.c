

#include <stdio.h>
#include <stdbool.h>
#define MAX 100  
#define INF 99999

int dist[MAX];
bool s[MAX];
int pred[MAX];
int minDist (int n) {
	int min = INF, index, i;
	for (i = 1; i <= n; i++) {
		if (!s[i] && dist[i] < min) {
			min = dist[i];
			index = i;
		}
	}
	return index;
}

void shortestPath (int n, int cost[MAX][MAX], int v) {
	int i, j, w;
	for (i = 1; i <= n; i++) {

        pred[i]=v;
		s[i] = false;
		dist[i] = cost[v][i];
	}
	s[v] = true;
	dist[v] = 0;
     pred[v] = -1;
	
	
	for (i = 2; i <= n; i++) {
		int u = minDist(n);
		s[u] = true;
		

		
		for (w = 1; w <= n; w++) {
			if (!s[w] && cost[u][w] && dist[u] != INF && dist[w] > dist[u] + cost[u][w]) {
				dist[w] = dist[u] + cost[u][w];
                 pred[w] = u;
			}
		}
		

	}
}
void printPath(int v) {
    if (pred[v] == -1) {
        printf("%d", v);
        return;
    }
    printPath(pred[v]);
    printf(" -> %d", v);
}
int main () {
	int n, maxE, i, j, o, d, w, start	;
	int cost[MAX][MAX];
	
	printf("\nEnter the number of vertices: ");
    scanf("%d", &n);
    maxE = n * (n - 1);

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            cost[i][j] = INF;
        }
    }

    for (i = 1; i <= maxE; i++) {
        printf("Enter edge %d (-1, -1 to quit): ", i);
        scanf("%d%d", &o, &d);
        if (o == -1 && d == -1) {
            break;
        }
        if (o > n || d > n || o < 0 || d < 0) {
            printf("\nInvalid Input");
            i--;
        } else {
            printf("Enter weight of edge: ");
            scanf("%d", &w);
            cost[o][d] = w;
        }
    }
    
    printf ("\nEnter the starting vertex: ");
    scanf ("%d", &start);
    
    shortestPath (n, cost, start);
    
    printf("\nVertex\tShortest Distance from %d\n", start);
    printf("\nVertex\tDistance from %d\tPath\n", start);
    for (i = 1; i <= n; i++) {
        printf("%d\t", i);
        if (dist[i] == INF) {
            printf("INF\t\tNo path\n");
        } else {
            printf("%d\t\t", dist[i]);
            printPath(i);
            printf("\n");
        }
    }

}
