#include <stdio.h>
#include <stdbool.h>
#define MAX 100  
#define INF 99999
#include<time.h>
int dist[MAX];
bool s[MAX];

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
		s[i] = false;
		dist[i] = cost[v][i];
	}
	s[v] = true;
	dist[v] = 0;
	printf ("\n\nIteration 1\tv = %d\n", v);
	for (j = 1; j <= n; j++) {
		if (s[j] == 1) {
			printf ("s[%d] = ", j);
		}
	}
	printf ("TRUE\n");
	for (j = 1; j <= n; j++) {
		if (s[j] == 0) {
			printf ("s[%d] = ", j);
		}
	}
	printf ("FALSE\nDist Array: [ ");
	for (j = 1; j <= n; j++) {
		if (dist[j] == INF) {
			printf ("INF ");
		} else {
			printf ("%d ", dist[j]);
		}
	}
	printf ("]\n");
	
	
	for (i = 2; i <= n; i++) {
		int u = minDist(n);
		s[u] = true;
		
		printf ("\n\nIteration %d\tu = %d\n", i, u);
		for (j = 1; j <= n; j++) {
			if (s[j] == 1) {
				printf ("s[%d] = ", j);
			}
		}
		printf ("TRUE\n");
		for (j = 1; j <= n; j++) {
			if (s[j] == 0) {
				printf ("s[%d] = ", j);
			}
		}
		printf ("FALSE\nDist Array: [ ");
		
		for (w = 1; w <= n; w++) {
			if (!s[w] && cost[u][w] && dist[u] != INF && dist[w] > dist[u] + cost[u][w]) {
				dist[w] = dist[u] + cost[u][w];
			}
		}
		
		for (j = 1; j <= n; j++) {
			if (dist[j] == INF) {
				printf ("INF ");
			} else {
				printf ("%d ", dist[j]);
			}
		}
		printf ("]\n");
	}
}

int main () {
	int n, maxE, i, j, o, d, w, start;
	int cost[MAX][MAX];
	clock_t start_time, end_time;
	double cpu_time_used;
	
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
	
	start_time = clock();
	shortestPath (n, cost, start);
	end_time = clock();
	
	cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC * 1000;
	
	printf("\nVertex\tShortest Distance from %d\n", start);
	for (i = 1; i <= n; i++) {
		printf("%d\t", i);
		if (dist[i] == INF)
			printf("INF\n");
		else
			printf("%d\n", dist[i]);
	}
	
	printf("\nTime taken to execute the function: %f ms\n", cpu_time_used);
}


//easy sssp
// #include <stdio.h>
// #include <stdbool.h>
// #define MAX 100  
// #define INF 99999

// int dist[MAX];
// bool s[MAX];

// int minDist (int n) {
// 	int min = INF, index, i;
// 	for (i = 1; i <= n; i++) {
// 		if (!s[i] && dist[i] < min) {
// 			min = dist[i];
// 			index = i;
// 		}
// 	}
// 	return index;
// }

// void shortestPath (int n, int cost[MAX][MAX], int v) {
// 	int i, j, w;
// 	for (i = 1; i <= n; i++) {
// 		s[i] = false;
// 		dist[i] = cost[v][i];
// 	}
// 	s[v] = true;
// 	dist[v] = 0;

	
	
// 	for (i = 2; i <= n; i++) {
// 		int u = minDist(n);
// 		s[u] = true;
		

		
// 		for (w = 1; w <= n; w++) {
// 			if (!s[w] && cost[u][w] && dist[u] != INF && dist[w] > dist[u] + cost[u][w]) {
// 				dist[w] = dist[u] + cost[u][w];
// 			}
// 		}
		

// 	}
// }

// int main () {
// 	int n, maxE, i, j, o, d, w, start	;
// 	int cost[MAX][MAX];
	
// 	printf("\nEnter the number of vertices: ");
//     scanf("%d", &n);
//     maxE = n * (n - 1);

//     for (i = 1; i <= n; i++) {
//         for (j = 1; j <= n; j++) {
//             cost[i][j] = INF;
//         }
//     }

//     for (i = 1; i <= maxE; i++) {
//         printf("Enter edge %d (-1, -1 to quit): ", i);
//         scanf("%d%d", &o, &d);
//         if (o == -1 && d == -1) {
//             break;
//         }
//         if (o > n || d > n || o < 0 || d < 0) {
//             printf("\nInvalid Input");
//             i--;
//         } else {
//             printf("Enter weight of edge: ");
//             scanf("%d", &w);
//             cost[o][d] = w;
//         }
//     }
    
//     printf ("\nEnter the starting vertex: ");
//     scanf ("%d", &start);
    
//     shortestPath (n, cost, start);
    
//     printf("\nVertex\tShortest Distance from %d\n", start);
//     for (i = 1; i <= n; i++) {
//         printf("%d\t", i);
//         if (dist[i] == INF)
//             printf("INF\n");
//         else
//             printf("%d\n", dist[i]);
//     }
// }
