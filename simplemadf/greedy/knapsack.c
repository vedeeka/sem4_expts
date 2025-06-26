#include <stdio.h>
int n;
int p[100], w[100];

void sort(int p[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (p[i] < p[j]) {
                int t = p[i];
                p[i] = p[j];
                p[j] = t;

                t = w[i];
                w[i] = w[j];
                w[j] = t;
            }
        }
    }


    // printf("Sorted profits: ");
    // for (int i = 0; i < n; i++) {
    //     printf("%d ", p[i]);
    // }
    // printf("\n");

    // printf("Sorted weights: ");
    // for (int i = 0; i < n; i++) {
    //     printf("%d ", w[i]);
    // }
    // printf("\n");
}


void least_w(int n,int m){
  
    float x[n];
    int remaining=m;
  int index[n];
  int t_p=0;
  int t_w=0;

  for(int i=0;i<n;i++){
     index[i]=i;
     x[i]=0.0;
  }

  for(int i=0;i<n;i++){
    for(int j=0;j<n-i-1;j++){
        if(w[index[j]]>w[index[j+1]]){
            int t=index[j];
            index[j]=index[j+1];
            index[j+1]=t;
        }
    }
  }

  for(int i=0;i<n && remaining>0;i++){
        int id=index[i];
        if(w[id]<=remaining){
            remaining -= w[id];
            t_p+=p[id];
            t_w+=w[id];
            x[id]=1.0;
        }else{
            x[id]=(float)remaining/w[id];
            t_p+=x[id]*p[i];
            t_w+=x[id]*w[i];
            remaining = 0;

        }
  }

     printf("\n Sorted weights: ");
     for (int i = 0; i < n; i++) {
        printf("%.2f ", x[i]);
 }
 printf("total: %d ", t_p);
}
void ratio(int n,int m){
  
    float x[n];
    int remaining=m;
  int index[n];
  int t_p=0;
  int t_w=0;

  for(int i=0;i<n;i++){
     index[i]=i;
     x[i]=0.0;
  }

  for(int i=0;i<n;i++){
    for(int j=0;j<n-i-1;j++){
        if ((float)p[index[j]] / w[index[j]] < (float)p[index[j+1]] / w[index[j+1]]) {
            
            int t=index[j];
            index[j]=index[j+1];
            index[j+1]=t;
        }
    }
  }

 

  for(int i=0;i<n && remaining>0;i++){
        int id=index[i];
        if(w[id]<=remaining){
            remaining -= w[id];
            t_p+=p[id];
            t_w+=w[id];
            x[id]=1.0;
        }else{
            x[id]=(float)remaining/w[id];
            t_p+=x[id]*p[i];
            t_w+=x[id]*w[i];
            remaining = 0;

        }
  }

     printf("\n \nSorted weights: ");
     for (int i = 0; i < n; i++) {
        printf("%.2f ", x[i]);
 }

 printf("total: %d ", t_p);
}


void max_profit(int n,int m){
  
    float x[n];
    int remaining=m;
  int index[n];
  int t_p=0;
  int t_w=0;

  for(int i=0;i<n;i++){
     index[i]=i;
     x[i]=0.0;
  }

  for(int i=0;i<n;i++){
    for(int j=0;j<n-i-1;j++){
        if (p[index[j]]< p[index[j+1]])
{
            int t=index[j];
            index[j]=index[j+1];
            index[j+1]=t;
        }
    }
  }

  for(int i=0;i<n && remaining>0;i++){
        int id=index[i];
        if(w[id]<=remaining){
            remaining -= w[id];
            t_p=t_p+p[id];
            t_w=t_w+w[id];
            x[id]=1.0;
        }else{
            x[id]=(float)remaining/w[id];
            t_p+=x[id]*p[i];
            t_w+=x[id]*w[i];
            remaining = 0;

        }
  }

     printf("\n \nSorted weights: ");
     for (int i = 0; i < n; i++) {
        
        printf("%.2f ", x[i]);

 }
 printf("total: %d ", t_p);

}


int main(){
   
    int m;
     // For example matching the image: n=3, m=20, p=(25,24,15), w=(18,15,10)
     printf("Enter number of elements (n): ");
     scanf("%d", &n);
   
    
    
     printf("Enter weights (w1,w2,...): ");
     for (int i = 0; i < n; i++)
     {
         scanf("%d", &w[i]);
        

     }
     
     printf("Enter value of m (capacity): ");
     scanf("%d", &m);
     int sum;
     printf("Enter profits (p1,p2,...): ");
     for (int i = 0; i < n; i++)
         scanf("%d", &p[i]);


      max_profit(n,m);
      least_w(n,m);
      ratio(n,m);
     
}