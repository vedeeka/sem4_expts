#include<stdio.h>
#include<limits.h>
#define MAX 30
struct Graph{
    int ori,dest;
};

int max_edges,n,k,count=1;
int d[MAX],p[MAX],dist[MAX],c[MAX][MAX],cost[MAX];
struct Graph G[MAX];

void Fgraph(struct Graph G[MAX],int k, int n, int p[MAX]);
void Bgraph(struct Graph G[MAX],int k, int n, int p[MAX]);

void create_graph(){
     int origin,destin,m;

     printf("Enter the no of vertices: ");
     scanf("%d",&n);
     max_edges=n*(n-1);

     printf("Enter graph stages: ");
     scanf("%d",&k);

     for(int i=1; i<=n; i++){
          for(int j=1; j<=n; j++)
                c[i][j]=INT_MAX;
     }

     for(int i=1; i<=n; i++){
          dist[i]=INT_MAX;
     }

     for(int i=1; i<=max_edges; i++){
          printf("Enter the edge %d(-1-1 to quit): ",i);
          scanf("%d%d",&origin,&destin);

          if(origin==-1 && destin== -1)
                break;
          if(origin>n || destin>n || origin<=0 || destin<=0){
                printf("Invalid vertex!\n");
                i--;
          }
          else{
                printf("Enter the cost of edge: ");
                scanf("%d",&c[origin][destin]);
          }
          count++;

          G[i].ori=origin;
          G[i].dest=destin;
     }

     Fgraph(G,k,n,p);
     printf("backward");
     Bgraph(G,k,n,p);
}

void Bgraph(struct Graph G[MAX],int k, int n, int p[MAX]){
     cost[n]=0;
     int r,r1;

     for(int j=n-1; j>=1; j--){
          int min=INT_MAX;

          for(r=1; r<=n; r++){
                if(c[j][r] != INT_MAX && c[j][r]+ cost[r] < min){
                     min=c[j][r]+cost[r];
                     r1=r;
                }
          }

          cost[j]=min;
          d[j]=r1;
     }

     p[1]=1;
     p[k]=n;

     for(int j=2; j<=n-1; j++){
          p[j]=d[p[j-1]];
     }

     for(int i=n; i>=1; i--){
          if(i==(n-1)) k--;
          if(i==(n-4)) k--;
          if(i==(n-7)) k--;
          if(i==1) k--;
          printf("cost[%d][%d]= %d    d[%d][%d]= %d\n",k,i,cost[i],k,i,d[i]);
     }
}

void Fgraph(struct Graph G[MAX],int k, int n, int p[MAX]){
     cost[n]=0;
     int r,r1;

     for(int j=n-1; j>=1; j--){
          int min=INT_MAX;

          for(r=1; r<=n; r++){
                if(c[j][r] != INT_MAX && c[j][r]+ cost[r] < min){
                     min=c[j][r]+cost[r];
                     r1=r;
                }
          }

          cost[j]=min;
          d[j]=r1;
     }

     p[1]=1;
     p[k]=n;

     for(int j=2; j<=n-1; j++){
          p[j]=d[p[j-1]];
     }

     for(int i=n; i>=1; i--){
          if(i==(n-1)) k--;
          if(i==(n-4)) k--;
          if(i==(n-7)) k--;
          if(i==1) k--;
          printf("cost[%d][%d]= %d    d[%d][%d]= %d\n",k,i,cost[i],k,i,d[i]);
     }
}

int main(){
     create_graph();
     return 0;
}
