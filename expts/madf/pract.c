#include <stdio.h>
int b[10];
void swap(int i,int j,int a[]){
    int t=a[i];
    a[i]=a[j];
    a[j]=t;
}

int partition(int low,int high,int a[]){
int i=low;
int j=high;
int p=a[low];
while(i<j){
    while(i<=high && a[i]<=p){
        i++;
    }
    while(a[j]>p){
        j--;
    }
    if(i<j){
        swap(i,j,a);
    }
}
swap(low,j,a);
return j;
}
void merge(int low,int h,int a[],int k){
    while(low<h){
        int j =partition(low,h,a);
        if(k==j) return;
        else if(k<j){
            h=j;
        }else{
            low=j+1;
        }
    }
}

int main() {
    int n, i;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    int a[n];
    printf("Enter the elements of the array:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
 int k=3;
 int min,max;
merge(0,n,a,k);



    printf("%d ", a[k]);



    return 0;
}
