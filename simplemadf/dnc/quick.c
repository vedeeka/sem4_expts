#include<stdio.h>
int n;
#define MAX 20
int a[MAX];

void inter(int i,int j){
    int t=a[i];
    a[i]=a[j];
    a[j]=t;

}

int partition(int l,int u){
int v=a[l];
int i=l;
int j=u;
while(1){
    while(a[i]<v)i++;
    while(a[j]>v)j--;

    if(i<j){inter(i,j);}
    else break;
}

return j;
}



void quick_sort(int l,int u){
if(l<u){
    int j=partition(l,u);
    quick_sort(l,j-1);
    quick_sort(j+1,u);
}
}
int main(){
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter sorted array elements:\n");
    for (int i = 1; i <= n; i++) 
        scanf("%d", &a[i]);
    int x;
   
    quick_sort(1,n);

    printf("Array after Select:\n");
    for (int i = 1; i <= n; i++)
        printf("%d ", a[i]);
    printf("\n");

}