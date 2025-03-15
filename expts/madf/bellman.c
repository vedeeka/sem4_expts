#include <stdio.h>
#define MAX 10
int distance[MAX][MAX], path[MAX];
int n;
enum{false,true};
int count=0;

void singlesource_sp(int v)
{
	int temp[n],i,j,k=1,min;
	count+=2;
	for(i=0;i<n;i++)
	{
		count+=3; temp[i]=path[i]=distance[0][i];
	}		
	count++;
	printf("\nSolution matrix for single source shortest path with general weights: \n%4s", "k");
	for(i=0;i<n;i++)
		printf("%4d",i);
		count=count+(n+1);
	printf("\n%4d", k++);
	count++;
	for(i=0;i<n;i++)
	{
		count+=3;
		if(path[i]==999)
			printf("%4s","++");
		else
			printf("%4d",path[i]);
	}
	count++;
	for(;k<n;k++)
	{
		count+=2;
		for(i=0;i<n;i++)
		{
			count+=3;min=999;
			for(j=0;j<n;j++)
			{
				count+=2;
				if(i!=j && min>(path[j]+distance[j][i]))
				{
						count++;min=path[j]+distance[j][i];
				}	
			}
			count+=2;
			if(temp[i]>min)
			{ temp[i]=min; count++;		}	
		}	
		for(i=0;i<n;i++)
			path[i]=temp[i];
		count=count+(2*(n+1));
		printf("\n%4d", k);
		count++;
		for(i=0;i<n;i++)
		{
			count+=3;
			if(path[i]==999)
			printf("%4s","++");
		else
			printf("%4d",path[i]);
		}	
		count++;
	}
}

void main()
{
    int i,max_edges,origin,destin,dist,v,j;
    printf("Enter number of nodes: ");
	scanf("%d",&n);
	count++;
	for(i=0;i<n;i++)
	{
		count+=2;
		for(j=0;j<n;j++)
	    {
			count+=3;
	    		if(i==j)
	    			distance[i][j]=0;
	    		else
	    			distance[i][j]=999;
		}
		count++;
	}
	count++;
	max_edges=n*(n-1);
	count++;
	for(i=1;i<=max_edges;i++)
	{
		count+=3;
		printf("\nPress origin as -1 and destination as -1 to end\n");
		printf("Enter edge %d: ",i);
		scanf("%d %d",&origin, &destin);
		if((origin==-1)&&(destin==-1))
		{count++;	break;}
		printf("Distance: ");
		scanf("%d",&dist);
		count+=2;
		if(origin>=n||destin>=n||origin<0||destin<0)
		{
			printf("Invalid edge!\n");
			i--; count++;
		}
		else
		{count++;	distance[origin][destin]=dist;}
	}
	count++;
	printf("Enter starting vertex: ");
	scanf("%d", &v);
	count+=2;
	singlesource_sp(v);
	printf("\nStep Count: %d", count);
}
