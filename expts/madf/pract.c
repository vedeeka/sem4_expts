#include<stdio.h>
#include<stdlib.h>
int t[10][2];
int cost[10][10];
int near[10];

#define INF 99999
void prims(int cost[][10],int n,int l,int k){
    int mincost = cost[k][l];  
    t[0][0] = k;  
    t[0][1] = l;
    

    for(int i=0;i<=n;i++){
        if(cost[i][l]<cost[i][k]){
            near[i]=l;
        }else{
            near[i]=k;
        }
    }
    near[l]=0;
    near[k]=0;
    for(int j=1;j<n;j++){
        int min =INF;
        int vn=-1;
        for(int i=0;i<=n;i++){
            if(near[i]!=0 && cost[i][near[i]]<min){
                min=cost[i][near[i]];
                vn=i;
            }
        }
        t[j][0]=vn;
        t[j][1]=near[vn];
        if(vn==-1)
        break;
        mincost=mincost+cost[vn][near[vn]];
        near[vn] = 0;

       
        for (int i = 1; i <= n; i++) {
            if (near[i] != 0 && cost[i][vn] < cost[i][near[i]]) {
                near[i] = vn;
            }
        }
        
    }




    printf("\nMinimum Spanning Tree Edges:\n");
    for (int i = 0; i < n - 1; i++) {
        printf("%d - %d\n", t[i][0], t[i][1]);
    }
    
    printf("\nMinimum Cost: %d\n", mincost);
}

int main(){
    int l,m,k;
    printf("enter");

    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            cost[i][j] = INF; // Fix: Set all values to a large number
        }
    }
        while(1){
                scanf("%d %d %d",&l,&m,&k);
                if(l==-1){
                    break;  
                }
                cost[l][m]=k;
                cost[m][l]=k; 
        }
        int min = INF;

        for(int i=0;i<=8;i++){
            for(int j=0;j<=8;j++){
                if (cost[i][j] != 0 && cost[i][j] < min) { 
                    min=cost[i][j];
                    l=i;
                    k=j;
                }
            }
        }


        prims(cost, 8, l, k);
}