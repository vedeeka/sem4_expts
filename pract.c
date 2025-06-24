

#include <stdio.h>

#define MAX 100

int a[MAX], b[MAX]; // Global arrays

void interchange(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}
int merge(int l,int u){
int v=a[l];
int i=l,j=u;
while(i<j){
    while(a[i]<v){
        i++;
    }
    while(a[j]>v){
        j--;
    }
    if(i<j){
        interchange(&a[i],&a[j]);
       
    }else
            break;

}
 
    return j;




}




void MergeSort(int l,int u){
    if(l<u){
        int m = merge(l,u);

        MergeSort(l,m-1);
        MergeSort(m+1,u);
        
    }
}



int main() {
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    MergeSort(0, n - 1);

    printf("Sorted array:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");
    return 0;
}
