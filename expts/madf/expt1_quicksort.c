#include <stdio.h>
#include <time.h>
void interchange(int b[], int i, int j) {
    int temp = b[i];
    b[i] = b[j];
    b[j] = temp;
}

void print_array(int b[], int n, int low, int up) {
    printf("\nCurrent Array: ");
    for (int i = 1; i <= n; i++) {
        if (i == low) printf("[");
        printf("%d", b[i]);
        if (i == up) printf("]");
        if (i < n) printf(" ");
    }
    printf("\n");
}

int partition(int b[], int low, int up, int n, int ascending) {
    int pivot = b[low];
    int i = low + 1;
    int j = up;

    while (i <= j) {
        if (ascending) {
            while (i <= up && b[i] <= pivot) i++;
            while (j > low && b[j] > pivot) j--;
        } else {
            while (i <= up && b[i] >= pivot) i++;
            while (j > low && b[j] < pivot) j--;
        }

        if (i < j) {
            interchange(b, i, j);
            print_array(b, n, low, up);
            
           
            printf("\nValue at j (index %d): %d\n", j, b[j]);
        }
    }

    interchange(b, low, j);
    print_array(b, n, low, up);

    printf("\nFinal value at j (index %d): %d\n", j, b[j]);
    
    return j;
}

void quick_sort(int b[], int low, int up, int n, int ascending) {
    if (low < up) {
        print_array(b, n, low, up);
        int pivot_index = partition(b, low, up, n, ascending);
        quick_sort(b, low, pivot_index - 1, n, ascending);
        quick_sort(b, pivot_index + 1, up, n, ascending);
    }
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n + 1];
    int sorted_arr[n + 1];

    // Input array data
    for (int i = 1; i <= n; i++) {
        printf("Enter element %d: ", i);
        scanf("%d", &arr[i]);
    }

    // Copy original array
    for (int i = 1; i <= n; i++) {
        sorted_arr[i] = arr[i];
    }

    // Ascending order sort
    printf("\n--- Ascending Order Sort ---\n");
    quick_sort(arr, 1, n, n, 1);
    printf("\nFinal Sorted Array (Ascending):\n");
    for (int i = 1; i <= n; i++) {
        printf("%d ", arr[i]);
    }

    // Descending order sort
    printf("\n\n--- Descending Order Sort ---\n");
    clock_t t; 
    t = clock();
    quick_sort(sorted_arr, 1, n, n, 0);
     double time_taken = ((double)t)/CLOCKS_PER_SEC; 
    printf("\nFinal Sorted Array (Descending):\n");
    for (int i = 1; i <= n; i++) {
        printf("%d ", sorted_arr[i]);
    }
    printf("QUICK SORT fun() took %f seconds to execute \n", time_taken);  
    return 0;
}
