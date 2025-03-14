#include <stdio.h>
#include <stdlib.h>
#define MAX 100
int count;
int order[MAX];
void sort_weight(int n, int weight[n])
{
   int w[n];
   int i,j;
   count++;
   for(i=0;i<n;i++)
   {
        order[i]=i; w[i]=weight[i]; count+=3;
   }
   count+=2;
    for(i=0;i<n-1;i++)
    {
    	count+=2;
        for(j=0;j<n-i-1;j++)
        {
        	count+=2;
            if(w[j]>w[j+1])
            {
                int temp=w[j];
                w[j]=w[j+1];
                w[j+1]=temp;
                int t1=order[j];
                order[j]=order[j+1];
                order[j+1]=t1;	count+=6;
            }
        }
        count++;
    }
    count++;
}
void sort_profit(int n, int profit[n])
{
   int p[n];
   int i,j;
   count++;
   for(i=0;i<n;i++)
   {
        order[i]=i; p[i]=profit[i]; count+=3;
   }
   count+=2;
    for(i=0;i<n-1;i++)
    {
    	count+=2;
        for(j=0;j<n-i-1;j++)
        {
        	count+=2;
            if(p[j]<p[j+1])
            {
                int temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
                int t1=order[j];
                order[j]=order[j+1];
                order[j+1]=t1;	count+=6;
            }
        }
        count++;
    }
    count++;
}
void sort_pw(int n, int profit[n],int weight[n])
{
   float pw[n];
   int i,j;
   count++;
   for(i=0;i<n;i++)
   {
        order[i]=i; pw[i]=(float)profit[i]/(float)weight[i]; count+=3;
   }
   count+=2;
    for(i=0;i<n-1;i++)
    {
    	count+=2;
        for(j=0;j<n-i-1;j++)
        {
        	count+=2;
            if(pw[j]<pw[j+1])
            {
                float temp=pw[j];
                pw[j]=pw[j+1];
                pw[j+1]=temp;
                int t1=order[j];
                order[j]=order[j+1];
                order[j+1]=t1;	count+=6;
            }
        }
        count++;
    }
    count++;
}
void max_profit(int n,int w[n],int p[n], int m)
{
    float x_p[n],total=0.0,u=m;
	int i;
	count++;
	for(i=0;i<n;i++)
   	{
        x_p[i]=0.0; count+=2;
   	}
   	count+=3;
	sort_profit(n,p);
	for(i=0;w[order[i]]<=u && i<n;i++)
	{
		total=total+ p[order[i]];
		x_p[order[i]]=1.0;
		u-=w[order[i]];
		count+=4;
	}
	count+=2;
	if(u>0)
	{
		x_p[order[i]]=u/w[order[i]];
		total+=p[order[i]]*(u/w[order[i]]); count+=2;
	}
	printf("%30s (", "Max. profit");
	for(i=0;i<n;i++)
		printf("%5.2f  ", x_p[i]);
	printf(")\t %.2f\n", total);
	count=count+n+2;
}

void min_weight(int n,int w[n],int p[n], int m)
{
	float x_w[n],total=0,u=m;
	int i;
	count++;
	for(i=0;i<n;i++)
  	{
        x_w[i]=0.0;count+=2;
    }
    count+=3;    
	sort_weight(n,w);
	for(i=0;w[order[i]]<=u && i<n;i++)
	{
		count+=4;
		total+=p[order[i]];
		x_w[order[i]]=1;
		u-=w[order[i]];
	}
	count+=2;
	if(u>0)
	{
		x_w[order[i]]=u/w[order[i]];
		total+=p[order[i]]*(u/w[order[i]]); count+=2;
	}
	printf("%30s (", "Min. weight");
	for(i=0;i<n;i++)
		printf("%5.2f  ", x_w[i]);
	printf(")\t %.2f\n", total);
	count=count+n+2;
}

void dec_pw(int n,int w[n],int p[n], int m)
{
	float x_pw[n],total=0,u=m;
	int i;
	count++;
	for(i=0;i<n;i++)
    {
        x_pw[i]=0.0; count+=2;
    }
    count+=3;    
	sort_pw(n,p,w);
	for(i=0;w[order[i]]<=u && i<n;i++)
	{
		total+=p[order[i]];
		x_pw[order[i]]=1;
		u-=w[order[i]];
		count+=4;
	}
	count+=2;
	if(u>0)
	{
		x_pw[order[i]]=u/w[order[i]];
		total+=p[order[i]]*(u/w[order[i]]); count+=2;
	}
	printf("%30s (", "Dec. P[i]/W[i]");
	for(i=0;i<n;i++)
		printf("%5.2f  ", x_pw[i]);
	printf(")\t %.2f\n", total);
	count=count+n+2;
}

void print(int n)
{
	int i;
	printf("%30s (", " "); 
	for(i=0;i<n;i++)
		printf(" x[%d]  ", i+1);
	printf(")\t   Total Cost\n");
}
int main()
{
    int n,m,i;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    printf("Enter size of knapsack bag: ");
    scanf("%d", &m);

    float p[n], w[n];
    printf("Enter profits : ");
    for(i=0;i<n;i++)
        scanf("%d", &p[i]);
    printf("Enter weights : ");
    for(i=0;i<n;i++)
        scanf("%d", &w[i]);
	
	int ch;
	while(1)
	{
		count=2*(n+1);
		printf("\n1. Maximum Profit\n2.Minimum weight\n3.Decreasing order of P[i]/W[i]\n4.Exit\nEnter choice: ");
		scanf("%d", &ch);
		switch(ch)
		{
			case 1: print(n);max_profit(n,w,p,m);break;
			case 2: print(n);min_weight(n,w,p,m);break;
			case 3: print(n);dec_pw(n,w,p,m);break;
			case 4: exit(1);
			default: printf("Invalid input\n");
		}
		printf("Step count= %d\n", count);
	}
}
