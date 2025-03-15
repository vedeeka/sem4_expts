#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#include<time.h>

int order[MAX];
int x[MAX], w[MAX];
int m, n;
float x_solution[MAX][MAX]; // Store multiple solutions
float profits[MAX];

void display_solution(int solution_num, float x_vals[], int weights[], int profits[], int n, int m)
{
    float total_weight = 0, total_profit = 0;
    printf("%d: (", solution_num);
    
    // Print fractions of objects taken
    for (int i = 0; i < n; i++) {
        printf("%s%.2f", i > 0 ? ", " : "", x_vals[i]);
        total_weight += x_vals[i] * weights[i];
        total_profit += x_vals[i] * profits[i];
    }
    
    printf(")\t\t%.1f\t\t%.1f", total_weight, total_profit);
}

void sort_pw(int n, int profit[], int weight[])
{
    float pw[n];
    int i, j;
    
    for (i = 0; i < n; i++) {
        order[i] = i;
        pw[i] = (float)profit[i] / (float)weight[i];
    }
    
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (pw[j] < pw[j + 1]) {
                float temp = pw[j];
                pw[j] = pw[j + 1];
                pw[j + 1] = temp;
                
                int t1 = order[j];
                order[j] = order[j + 1];
                order[j + 1] = t1;
            }
        }
    }
}

// Fractional knapsack using greedy approach with profit/weight ratio
void knapsack_profit_weight_ratio(int n, int w[], int p[], int m)
{
    float x_pw[n], total_weight = 0, total_profit = 0, u = m;
    int i;
    
    for (i = 0; i < n; i++) {
        x_pw[i] = 0.0;
    }
    
    sort_pw(n, p, w);
    
    for (i = 0; i < n && w[order[i]] <= u; i++) {
        x_pw[order[i]] = 1.0;
        u -= w[order[i]];
        total_weight += w[order[i]];
        total_profit += p[order[i]];
    }
    
    if (i < n && u > 0) {
        x_pw[order[i]] = u / w[order[i]];
        total_weight += x_pw[order[i]] * w[order[i]];
        total_profit += x_pw[order[i]] * p[order[i]];
    }
    
    // Store solution
    for (i = 0; i < n; i++) {
        x_solution[3][i] = x_pw[i];
    }
    profits[3] = total_profit;
}



void knapsack_max_profit(int n, int w[], int p[], int m)
{
    float x_mp[n], remaining = m;
    int i, sorted_idx[n];
    
    // Initialize solution
    for (i = 0; i < n; i++) {
        x_mp[i] = 0.0;
        sorted_idx[i] = i;
    }
    
    // Sort by profit (descending)
    for (i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[sorted_idx[j]] < p[sorted_idx[j + 1]]) {
                int temp = sorted_idx[j];
                sorted_idx[j] = sorted_idx[j + 1];
                sorted_idx[j + 1] = temp;
            }
        }
    }
    
    float total_weight = 0, total_profit = 0;
    
    // Fill knapsack
    for (i = 0; i < n && remaining > 0; i++) {
        int idx = sorted_idx[i];
        if (w[idx] <= remaining) {
            x_mp[idx] = 1.0;
            remaining -= w[idx];
            total_weight += w[idx];
            total_profit += p[idx];
        } else {
            x_mp[idx] = remaining / w[idx];
            total_weight += x_mp[idx] * w[idx];
            total_profit += x_mp[idx] * p[idx];
            remaining = 0;
        }
    }
    
    // Store solution
    for (i = 0; i < n; i++) {
        x_solution[1][i] = x_mp[i];
    }
    profits[1] = total_profit;
}

// Least weight strategy (take lightest items first)
void knapsack_least_weight(int n, int w[], int p[], int m)
{
    float x_lw[n], remaining = m;
    int i, sorted_idx[n];
    
    // Initialize solution
    for (i = 0; i < n; i++) {
        x_lw[i] = 0.0;
        sorted_idx[i] = i;
    }
    
   
    for (i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (w[sorted_idx[j]] > w[sorted_idx[j + 1]]) {
                int temp = sorted_idx[j];
                sorted_idx[j] = sorted_idx[j + 1];
                sorted_idx[j + 1] = temp;
            }
        }
    }
    
    float total_weight = 0, total_profit = 0;
    
  
    for (i = 0; i < n && remaining > 0; i++) {
        int idx = sorted_idx[i];
        if (w[idx] <= remaining) {
            x_lw[idx] = 1.0;
            remaining -= w[idx];
            total_weight += w[idx];
            total_profit += p[idx];
        } else {
            x_lw[idx] = remaining / w[idx];
            total_weight += x_lw[idx] * w[idx];
            total_profit += x_lw[idx] * p[idx];
            remaining = 0;
        }
    }
    
 
    for (i = 0; i < n; i++) {
        x_solution[2][i] = x_lw[i];
    }
    profits[2] = total_profit;
}

void solve_multiple_strategies(int n, int w[], int p[], int m)
{
   
    knapsack_max_profit(n, w, p, m);
    knapsack_least_weight(n, w, p, m);
    knapsack_profit_weight_ratio(n, w, p, m);
    
    // Display results
    printf("\nFeasible solutions are as follows:\n\n");
    printf("%-10s %-25s %-15s %-15s %s\n", "", "(x₁, x₂, x₃)", "Capacity of bag", "Profit to be max", "(strategy used)");
    printf("===================================================================================\n");
    
    
    
    display_solution(2, x_solution[1], w, p, n, m);
    printf("\t\tmax. profit\n");
    
    display_solution(3, x_solution[2], w, p, n, m);
    printf("\t\tleast weight\n");
    
    display_solution(4, x_solution[3], w, p, n, m);
    printf("\t\tdescending order of p/w\n");
    
    
    float max_profit = 0;
    int best_strategy = 0;
    for (int i = 0; i < 4; i++) {
        if (profits[i] > max_profit) {
            max_profit = profits[i];
            best_strategy = i;
        }
    }
    
    printf("\nBest strategy: ");

    printf("Maximum profit: %.1f\n", max_profit);
}

int main()
{
    int i, r = 0;
    
    // For example matching the image: n=3, m=20, p=(25,24,15), w=(18,15,10)
    printf("Enter number of elements (n): ");
    scanf("%d", &n);
    
    int p[n], w_temp[n];
    
    printf("Enter weights (w1,w2,...): ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &w_temp[i]);
        r += w_temp[i];
        w[i] = w_temp[i]; // Copy to global array for subset sum
    }
    
    printf("Enter value of m (capacity): ");
    scanf("%d", &m);

    printf("Enter profits (p1,p2,...): ");
    for (i = 0; i < n; i++)
        scanf("%d", &p[i]);

      
            solve_multiple_strategies(n, w_temp, p, m);

           

    
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
//         printf("%f ", x[i]);
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
//         if(p[index[j]]/w[index[j]]<p[index[j+1]]/w[index[j+1]]){
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
//         printf("%f ", x[i]);
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
//         if(p[index[j]]/w[index[j]]<p[index[j+1]]/w[index[j+1]]){
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
//         printf("%f ", x[i]);
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