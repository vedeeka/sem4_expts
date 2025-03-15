#include <stdio.h>

int n;
int p[100], w[100];

void printSolutionVector(float x[]) {
    printf("\nSolution Vector: ");
    for (int i = 0; i < n; i++) {
        if (x[i] == 1.0)
            printf("X%d + ", i + 1);
        else if (x[i] > 0)
            printf("%.2fX%d + ", x[i], i + 1);
    }
    printf("\b\b \n");  // Remove last '+'
}

void knapsack(int n, int m, int mode) {
    float x[n], ratio[n];
    int remaining = m, index[n];
    float totalProfit = 0;

    for (int i = 0; i < n; i++) {
        index[i] = i;
        x[i] = 0.0;
        ratio[i] = (float)p[i] / w[i];
    }

    // Sorting based on mode
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            int swap = 0;
            if (mode == 1 && w[index[j]] > w[index[j + 1]])  // Least weight
                swap = 1;
            if (mode == 2 && p[index[j]] < p[index[j + 1]])  // Max profit
                swap = 1;
            if (mode == 3 && ratio[index[j]] < ratio[index[j + 1]])  // Max ratio
                swap = 1;

            if (swap) {
                int temp = index[j];
                index[j] = index[j + 1];
                index[j + 1] = temp;
            }
        }
    }

    printf("\nWeights (w): ");
    for (int i = 0; i < n; i++) {
        printf("%d ", w[index[i]]);
    }

    printf("\nProfits (p): ");
    for (int i = 0; i < n; i++) {
        printf("%d ", p[index[i]]);
    }

    printf("\nFraction (f): ");
    for (int i = 0; i < n && remaining > 0; i++) {
        int id = index[i];

        if (w[id] <= remaining) {
            x[id] = 1.0;
            remaining -= w[id];
            totalProfit += p[id];
        } else {
            x[id] = (float)remaining / w[id];
            totalProfit += x[id] * p[id];
            remaining = 0;
        }
        printf("%.2f ", x[id]);
    }

    printf("\nΣ wixi = %d", m);
    printf("\nΣ pixi = %.2f", totalProfit);

    printSolutionVector(x);
}

int main() {
    int m;

    printf("Enter number of elements (n): ");
    scanf("%d", &n);

    printf("Enter weights (w1, w2, ...): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &w[i]);
    }

    printf("Enter value of m (capacity): ");
    scanf("%d", &m);

    printf("Enter profits (p1, p2, ...): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    printf("\n--- Using Maximum Profit ---");
    knapsack(n, m, 2);

    printf("\n--- Using Least Weight ---");
    knapsack(n, m, 1);

    printf("\n--- Using Maximum Profit/Weight Ratio ---");
    knapsack(n, m, 3);

    return 0;
}

///optimal code for knapsack
// #include <stdio.h>
// int n;
// int p[100], w[100];

// void sort(int p[], int n) {
//     for (int i = 0; i < n; i++) {
//         for (int j = i; j < n; j++) {
//             if (p[i] < p[j]) {
//                 int t = p[i];
//                 p[i] = p[j];
//                 p[j] = t;

//                 t = w[i];
//                 w[i] = w[j];
//                 w[j] = t;
//             }
//         }
//     }


//     // printf("Sorted profits: ");
//     // for (int i = 0; i < n; i++) {
//     //     printf("%d ", p[i]);
//     // }
//     // printf("\n");

//     // printf("Sorted weights: ");
//     // for (int i = 0; i < n; i++) {
//     //     printf("%d ", w[i]);
//     // }
//     // printf("\n");
// }


// void least_w(int n,int m){
  
//     float x[n];
//     int remaining=m;
//   int index[n];
//   int t_p;
//   int t_w;

//   for(int i=0;i<n;i++){
//      index[i]=i;
//      x[i]=0.0;
//   }

//   for(int i=0;i<n;i++){
//     for(int j=0;j<n-i-1;j++){
//         if(w[index[j]]>w[index[j+1]]){
//             int t=index[j];
//             index[j]=index[j+1];
//             index[j+1]=t;
//         }
//     }
//   }

//   for(int i=0;i<n && remaining>0;i++){
//         int id=index[i];
//         if(w[id]<=remaining){
//             remaining -= w[id];
//             t_p=p[id];
//             t_w=w[id];
//             x[id]=1.0;
//         }else{
//             x[id]=(float)remaining/w[id];
//             t_p=x[id]*p[i];
//             t_w=x[id]*w[i];
//             remaining = 0;

//         }
//   }

//      printf("\n Sorted weights: ");
//      for (int i = 0; i < n; i++) {
//         printf("%.2f ", x[i]);
//  }

// }
// void ratio(int n,int m){
  
//     float x[n];
//     int remaining=m;
//   int index[n];
//   int t_p;
//   int t_w;

//   for(int i=0;i<n;i++){
//      index[i]=i;
//      x[i]=0.0;
//   }

//   for(int i=0;i<n;i++){
//     for(int j=0;j<n-i-1;j++){
//         if ((float)p[index[j]] / w[index[j]] < (float)p[index[j+1]] / w[index[j+1]]) {
            
//             int t=index[j];
//             index[j]=index[j+1];
//             index[j+1]=t;
//         }
//     }
//   }

 

//   for(int i=0;i<n && remaining>0;i++){
//         int id=index[i];
//         if(w[id]<=remaining){
//             remaining -= w[id];
//             t_p=p[id];
//             t_w=w[id];
//             x[id]=1.0;
//         }else{
//             x[id]=(float)remaining/w[id];
//             t_p=x[id]*p[i];
//             t_w=x[id]*w[i];
//             remaining = 0;

//         }
//   }

//      printf("\n \nSorted weights: ");
//      for (int i = 0; i < n; i++) {
//         printf("%.2f ", x[i]);
//  }


// }


// void max_profit(int n,int m){
  
//     float x[n];
//     int remaining=m;
//   int index[n];
//   int t_p;
//   int t_w;

//   for(int i=0;i<n;i++){
//      index[i]=i;
//      x[i]=0.0;
//   }

//   for(int i=0;i<n;i++){
//     for(int j=0;j<n-i-1;j++){
//         if ((float)p[index[j]] / w[index[j]] < (float)p[index[j+1]] / w[index[j+1]])
// {
//             int t=index[j];
//             index[j]=index[j+1];
//             index[j+1]=t;
//         }
//     }
//   }

//   for(int i=0;i<n && remaining>0;i++){
//         int id=index[i];
//         if(w[id]<=remaining){
//             remaining -= w[id];
//             t_p=p[id];
//             t_w=w[id];
//             x[id]=1.0;
//         }else{
//             x[id]=(float)remaining/w[id];
//             t_p=x[id]*p[i];
//             t_w=x[id]*w[i];
//             remaining = 0;

//         }
//   }

//      printf("\n \nSorted weights: ");
//      for (int i = 0; i < n; i++) {
//         printf("%.2f ", x[i]);
//  }


// }


// int main(){
   
//     int m;
//      // For example matching the image: n=3, m=20, p=(25,24,15), w=(18,15,10)
//      printf("Enter number of elements (n): ");
//      scanf("%d", &n);
   
    
    
//      printf("Enter weights (w1,w2,...): ");
//      for (int i = 0; i < n; i++)
//      {
//          scanf("%d", &w[i]);
        

//      }
     
//      printf("Enter value of m (capacity): ");
//      scanf("%d", &m);
//      int sum;
//      printf("Enter profits (p1,p2,...): ");
//      for (int i = 0; i < n; i++)
//          scanf("%d", &p[i]);


//       max_profit(n,m);
//       least_w(n,m);
//       ratio(n,m);
     
// }