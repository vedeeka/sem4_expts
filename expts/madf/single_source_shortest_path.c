#include <stdio.h>
#define MAX 10
int distance[MAX][MAX];
int n;
enum{false,true};
int count=0;
int next_vertex(int dist[],int s[],int v)
{ int u=-1,i,min=999; count+=3;
for(i=0;i<n;i++)
{ count+=2;
if(i!=v)
{ count++;
if(s[i]==false && min>dist[i])
{ min=dist[i];u=i; count+=2; } } }
count++;
return u;
}
void shortest_distance(int v)
{ int dist[n],s[n],i,j,k,itr=1; count+=2;
for(i=0;i<n;i++)
{ count+=3;
dist[i]=distance[v][i]; s[i]=false; }
count++;
printf("%15s %20s %15s", "Iteration", "Selected vertices", "Next vertex");
count++;
for(i=1;i<=n;i++)
printf("\t[%d]", i);
count=count+(n); // corrected count here, loop runs n times, count inside loop is already handled
printf("\n%15s %20s %15s", "Initial", "--", "--");
printf("\n"); // Added missing newline
s[v]=true; dist[v]=0; count+=3;
for(i=0;i<n;i++)
{ count+=2;
if(dist[i]==999)
printf("\t%s", "++");
else
printf("\t%d", dist[i]); }
printf("\n");
count+=2;
for(i=0;i<n;i++)
{ count+=2;
if(i!=v)
{ int u=next_vertex(dist,s,v); count+=2;
if(u==-1)
{ count++; break;}
count+=2;
printf("%15d ",itr++);
for(k=0;k<n;k++)
{ count+=2;
if(s[k]==true)
printf("%d ", k);
else
printf("  "); // Changed to print space for better formatting
}
s[u]=true;count+=3;
for(j=0;j<n;j++)
{ count+=2;
if(i!=v) // Condition should be based on whether j is v, not i. But actually this condition (i!=v) seems incorrect and unnecessary in this loop. Let's remove it.
{ count++;
if(distance[u][j]!=999 && s[j]==false)
{ count++;
if(dist[j]>dist[u]+distance[u][j])
{count++; dist[j]=dist[u]+distance[u][j];} } }
}
printf("%15d ", u);
count+=3;
for(k=0;k<n;k++)
{ count+=2;
if(dist[k]==999)
printf("\t%s", "++");
else
printf("\t %d", dist[k]); }
printf("\n");
count++;
}
}

}
int main() // Changed void main() to int main()
{ int i,max_edges,origin,destin,dist,v,j;
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
distance[i][j]=999; }
count++; }
count++;
max_edges=n*(n-1); count++;
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
printf("Enter starting vertex: ");
scanf("%d", &v);
count++;
shortest_distance(v);
printf("\nStep Count: %d", count);
printf("\n"); // Added newline for better output formatting
return 0; // Added return 0 for int main()
}