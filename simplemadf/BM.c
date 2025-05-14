#include <stdio.h>
#include <string.h>

#define MAX_CHAR 256  // For all possible ASCII characters

// Function to compute the last occurrence of each character in the pattern
void computeLast(char *P, int last[]) {
    int i;
    for (i = 0; i < MAX_CHAR; i++) {
        last[i] = -1;  // Initialize all to -1
    }
    for (i = 0; P[i] != '\0'; i++) {
        last[(int)P[i]] = i;  // Update last occurrence
    }
}

// Boyer-Moore string matching function
int BM_Match(char *T, char *P) {
    int n = strlen(T);
    int m = strlen(P);
    int last[MAX_CHAR];

    computeLast(P, last);

    int i = m - 1;
    int j = m - 1;

    while (i <= n - 1) {
        if (P[j] == T[i]) {
            if (j == 0) {
                return i;  // Match found
            } else {
                i--;
                j--;
            }
        } else {
            int l = last[(int)T[i]];
            i = i + m - ((j < 1 + l) ? j : 1 + l);  // jump step
            j = m - 1;
        }
    }

    return -1;  // No match found
}

// Main function to test the BM_Match
int main() {#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    #define MAX_TREE_HT 100
    #define MAX_CHAR 256
    
    // A Huffman tree node
    struct MinHeapNode {
        char data;
        unsigned freq;
        struct MinHeapNode *left, *right;
    };
    
    // Min-Heap (priority queue) structure
    struct MinHeap {
        unsigned size;
        unsigned capacity;
        struct MinHeapNode **array;
    };
    
    // Create a new node
    struct MinHeapNode* newNode(char data, unsigned freq) {
        struct MinHeapNode* temp = (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
        temp->left = temp->right = NULL;
        temp->data = data;
        temp->freq = freq;
        return temp;
    }
    
    // Create a min heap of given capacity
    struct MinHeap* createMinHeap(unsigned capacity) {
        struct MinHeap* minHeap = (struct MinHeap*) malloc(sizeof(struct MinHeap));
        minHeap->size = 0;
        minHeap->capacity = capacity;
        minHeap->array = (struct MinHeapNode**) malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
        return minHeap;
    }
    
    // Swap two nodes
    void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
        struct MinHeapNode* t = *a;
        *a = *b;
        *b = t;
    }
    
    // Heapify at given index
    void minHeapify(struct MinHeap* minHeap, int idx) {
        int smallest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
    
        if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
            smallest = left;
    
        if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
            smallest = right;
    
        if (smallest != idx) {
            swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
            minHeapify(minHeap, smallest);
        }
    }
    
    // Check if size is 1
    int isSizeOne(struct MinHeap* minHeap) {
        return (minHeap->size == 1);
    }
    
    // Extract min value node
    struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
        struct MinHeapNode* temp = minHeap->array[0];
        minHeap->array[0] = minHeap->array[--minHeap->size];
        minHeapify(minHeap, 0);
        return temp;
    }
    
    // Insert a node into the min heap
    void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
        ++minHeap->size;
        int i = minHeap->size - 1;
    
        while (i && minHeapNode->freq < minHeap->array[(i - 1)/2]->freq) {
            minHeap->array[i] = minHeap->array[(i - 1)/2];
            i = (i - 1)/2;
        }
    
        minHeap->array[i] = minHeapNode;
    }
    
    // Build the min heap
    void buildMinHeap(struct MinHeap* minHeap) {
        int n = minHeap->size - 1;
        for (int i = (n - 1)/2; i >= 0; --i)
            minHeapify(minHeap, i);
    }
    
    // Create and build min heap
    struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
        struct MinHeap* minHeap = createMinHeap(size);
    
        for (int i = 0; i < size; ++i)
            minHeap->array[i] = newNode(data[i], freq[i]);
    
        minHeap->size = size;
        buildMinHeap(minHeap);
    
        return minHeap;
    }
    
    // Build the Huffman tree
    struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
        struct MinHeapNode *left, *right, *top;
        struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);
    
        while (!isSizeOne(minHeap)) {
            left = extractMin(minHeap);
            right = extractMin(minHeap);
    
            top = newNode('$', left->freq + right->freq);  // $ is a special symbol
            top->left = left;
            top->right = right;
    
            insertMinHeap(minHeap, top);
        }
    
        return extractMin(minHeap);
    }
    
    // Print Huffman codes
    void printCodes(struct MinHeapNode* root, int arr[], int top) {
        if (root->left) {
            arr[top] = 0;
            printCodes(root->left, arr, top + 1);
        }
    
        if (root->right) {
            arr[top] = 1;
            printCodes(root->right, arr, top + 1);
        }
    
        if (!(root->left) && !(root->right)) {
            printf("%c: ", root->data);
            for (int i = 0; i < top; ++i)
                printf("%d", arr[i]);
            printf("\n");
        }
    }
    
    // Count frequencies of characters
    void calculateFrequencies(char input[], int freq[], char chars[], int* distinct) {
        int count[MAX_CHAR] = {0};
        for (int i = 0; input[i] != '\0'; i++)
            count[(unsigned char)input[i]]++;
    
        *distinct = 0;
        for (int i = 0; i < MAX_CHAR; i++) {
            if (count[i] > 0) {
                chars[*distinct] = (char)i;
                freq[*distinct] = count[i];
                (*distinct)++;
            }
        }
    }
    
    // Main
    int main() {
        char input[1000];
        printf("Enter the input string: ");
        scanf("%[^\n]", input);
    
        int freq[MAX_CHAR], distinct = 0;
        char chars[MAX_CHAR];
    
        calculateFrequencies(input, freq, chars, &distinct);
    
        struct MinHeapNode* root = buildHuffmanTree(chars, freq, distinct);
    
        int arr[MAX_TREE_HT], top = 0;
        printf("Huffman Codes:\n");
        printCodes(root, arr, top);
    
        return 0;
    }
    
    char text[100], pattern[100];
    printf("Enter the text: ");
    gets(text);  // Use fgets() in real applications to avoid buffer overflow
    printf("Enter the pattern: ");
    gets(pattern);

    int pos = BM_Match(text, pattern);
    if (pos != -1) {
        printf("Pattern found at index %d\n", pos);
    } else {
        printf("There is no substring of T matching P.\n");
    }

    return 0;
}
