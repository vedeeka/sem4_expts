#include <stdio.h>
#define MAX 10
int distance[MAX][MAX], path[MAX][MAX];
int n;
enum{false,true};
int count=0;
void shortest_path()
{ int temp[n][n],i,j,k;
count++;
for(i=0;i<n;i++)
{ count+=2;
for(j=0;j<n;j++)
{ count+3; path[i][j]=temp[i][j]=distance[i][j]; }
count++; }
count+=2;
for(k=0;k<n;k++)
{ count+=2;
for(i=0;i<n;i++)
{ count+=2;
for(j=0;j<n;j++)
{ count+=2;
if(path[i][j]>path[i][k]+path[k][j])
{ temp[i][j]= path[i][k]+path[k][j];count++;} }
count++; }
count+=2;
for(i=0;i<n;i++)
{ count+=2;
for(j=0;j<n;j++)
{ path[i][j]=temp[i][j];count++; }
count++; }
count++;
}
count++;
printf("\nSolution matrix for all source shortest path: \n%4s", " ");
for(i=0;i<n;i++)
printf("%4d",i);
count+=(n+1);count++;
for(i=0;i<n;i++)
{ count++;
printf("\n%4d",i);
for(j=0;j<n;j++)
{ count+=3;
if(path[i][j]==999)
printf("%4s","++");
else
printf("%4d",path[i][j]); }
count++; }

count++;
}
void main()
{ int i,max_edges,origin,destin,dist,j;
printf("Enter number of nodes: ");
scanf("%d",&n);
count++;
for(i=0;i<n;i++)
{ count+=2;
for(j=0;j<n;j++)
{ count+=3;
if(i==j)
distance[i][j]=0;
else

distance[i][j]=999; 
count++;
}
count+=2;
max_edges=n*(n-1);
for(i=1;i<=max_edges;i++)
{ count+=3;
printf("\nPress origin as -1 and destination as -1 to end\n");
printf("Enter edge %d: ",i);
scanf("%d %d",&origin, &destin);
if((origin==-1)&&(destin==-1))
{count++; break;}
printf("Distance: ");
scanf("%d",&dist);
count+=2;
if(origin>=n||destin>=n||origin<0||destin<0)
{ printf("Invalid edge!\n"); i--; count++; }
else
{count++; distance[origin][destin]=dist;}
}
count++;
shortest_path();
printf("\nStep Count: %d", count);
}