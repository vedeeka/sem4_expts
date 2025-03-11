#include <stdio.h>
#include <limits.h>

#define N 4
int w[10][10];
int c[10][10];
int r[10][10];

int find(int c[10][10], int r[10][10], int i, int j) {
    int k;
    int min = INT_MAX;
    for (int m = i + 1; m <= j; m++) {
        if (c[i][m-1] + c[m][j] < min) {
            min = c[i][m-1] + c[m][j];
            k = m;
        }
    }
    return k;
}
void print_op(int n) {
    printf("Combined matrices (w, r, c):\n");
    for (int i = 0; i <= n; i++) {
        int m = 0;
        
        for (int j = i; j <= n; j++) {
           
            printf("(%d, %d, %d) ", w[m][j], r[m][j], c[m][j]);
           
            m = m + 1;
        }
        printf("\n");
    }
    printf("\n");
}
void print_matrices(int n) {
    printf("Final matrices:\n");
    printf("Cost matrix:\n");
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }

    printf("Weight matrix:\n");
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            printf("%d ", w[i][j]);
        }
        printf("\n");
    }

    printf("Root matrix:\n");
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            printf("%d ", r[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void print_trees(int r[10][10], int i, int j, int depth) {
    if (i < j) {
        int k = r[i][j];
        for (int d = 0; d < depth; d++) {
            printf("  ");
        }
        printf("k%d\n", k);
        print_trees(r, i, k - 1, depth + 1);
        print_trees(r, k, j, depth + 1);
    } else if (i == j) {
        for (int d = 0; d < depth; d++) {
            printf("  ");
        }
       
    }
}
void obst(int p[], int q[], int n) {
    for (int i = 0; i <= n; i++) {
        w[i][i] = q[i];
        c[i][i] = 0;
        r[i][i] = 0;
        if (i < n) {
            w[i][i+1] = q[i] + q[i+1] + p[i];
            c[i][i+1] = w[i][i+1];
            r[i][i+1] = i + 1;
        }
    }

    for (int d = 2; d <= n + 1; d++) {
        for (int i = 0; i <= n - d + 1; i++) {
            int j = i + d - 1;
            w[i][j] = w[i][j-1] + p[j-1] + q[j];
            int k = find(c, r, i, j);
            c[i][j] = w[i][j] + c[i][k-1] + c[k][j];
            r[i][j] = k;
        }
    }
    print_matrices(n);
    print_op(n);
    print_trees(r, 0, n, 0);
}
int main(){
    int p[]={5,6,4,3,7};
    int q[]={7,6,5,4,3,7};
    int n=5;
    obst(p,q,n);
    return 0;
}

// int main() {
//     int n;
//     printf("Enter the number of keys: ");
//     scanf("%d", &n);

//     int p[n];
//     int q[n+1];

//     printf("Enter the values for the keys (p):\n");
//     for (int i = 0; i < n; i++) {
//         scanf("%d", &p[i]);
//     }

//     printf("Enter the values for the weight (q):\n");
//     for (int i = 0; i <= n; i++) {
//         scanf("%d", &q[i]);
//     }

//     obst(p, q, n);

//     return 0;
// }

