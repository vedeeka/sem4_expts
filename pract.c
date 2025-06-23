#include <stdio.h>

#define MAX 100

typedef struct {
    int p; // profit
    int w; // weight
} Pair;

Pair pair[MAX];   // Array to store profit-weight pairs
int b[MAX];       // Boundary markers for each Si
int next;  


int Largest(Pair pair[], int w[], int t, int h, int i, int m) {
    for(int j=h;j>=t;j--){
        if(pair[j].w+w[i]<=m){
            return j;
        }
    }
    return t-1;

}

void DKnap(int p[], int w[], int n, int m) {
    pair[1].w=0;
    pair[1].p=0;
     b[0]=0;
    int next=2;
    b[1]=next;


    int h,t=1;

    for(int i=1;i<=n;i++){
        int k = t;
        int u = Largest(pair, w, t, h, i, m);
        int start = next;


        for (int j = t; j <= u; j++) {
            int pp = pair[j].p + p[i];
            int ww = pair[j].w + w[i];

            while ((k <= h) && (pair[k].w < ww)) {
                pair[next++] = pair[k++];
            }

            if ((k <= h) && (pair[k].w == ww)) {
                if (pp > pair[k].p) {
                    pair[next++] = (Pair){pp, ww};
                } else {
                    pair[next++] = pair[k]; // keep existing
                }
                k++;
            } else {
                // Add pair if non-dominated (strictly better than previous)
                if (next == start || pp > pair[next - 1].p) {
                    pair[next++] = (Pair){pp, ww};
                }
            }

            while ((k <= h) && (pair[k].p <= pair[next - 1].p)) {
                k++;
            }
        }



            while((k<=h)){
                 pair[next++]=pair[k++];
            }

    t=h+1;
    h=next-1;
    b[i+1]=next;
    }


    printf("\nFinal Optimal (Profit, Weight) pairs:\n");
    int maxProfit = 0;
    for (int i = t; i <= h; i++) {
        printf("(%d, %d)\n", pair[i].p, pair[i].w);
        if (pair[i].w <= m && pair[i].p > maxProfit)
            maxProfit = pair[i].p;
    }

    printf("\nMaximum Profit: %d\n", maxProfit);


}






int main() {
    int n = 7, m = 20;
    int p[MAX], w[MAX];

    // 1-based input
    p[1] = 3; w[1] = 4;
    p[2] = 2; w[2] = 2;
    p[3] = 3; w[3] = 3;
    p[4] = 5; w[4] = 5;
    p[5] = 4; w[5] = 2;
    p[6] = 5; w[6] = 4;
    p[7] = 6; w[7] = 5;

    DKnap(p, w, n, m);

    return 0;
}
