#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 100
#define MAX_CHAR 256

struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
};

struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode **array;
};

struct MinHeapNode* newNode(char data, unsigned freq) {
    struct MinHeapNode* temp = (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**) malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

int compareNodes(struct MinHeapNode* a, struct MinHeapNode* b) {
    if (a->freq != b->freq)
        return a->freq - b->freq;  // Sort by frequency
    return a->data - b->data;  // If frequencies are the same, sort alphabetically
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && compareNodes(minHeap->array[left], minHeap->array[smallest]) < 0)
        smallest = left;

    if (right < minHeap->size && compareNodes(minHeap->array[right], minHeap->array[smallest]) < 0)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

int isSizeOne(struct MinHeap* minHeap) {
    return (minHeap->size == 1);
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[--minHeap->size];
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && compareNodes(minHeapNode, minHeap->array[(i - 1)/2]) < 0) {
        minHeap->array[i] = minHeap->array[(i - 1)/2];
        i = (i - 1)/2;
    }

    minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap* minHeap) {
    int n = minHeap->size - 1;
    for (int i = (n - 1)/2; i >= 0; --i)
        minHeapify(minHeap, i);
}

struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

void printPriorityQueue(struct MinHeap* minHeap) {
    printf("Priority Queue: [");
    for (int i = 0; i < minHeap->size; i++) {
        if (minHeap->array[i]->data == ' ')
            printf("space(%d)", minHeap->array[i]->freq);
        else
            printf("%c(%d)", minHeap->array[i]->data, minHeap->array[i]->freq);
        if (i != minHeap->size - 1)
            printf(", ");
    }
    printf("]\n");
}

struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
    struct MinHeapNode *left, *right, *top;
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}

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
        if (root->data == ' ')
            printf("space : ");
        else
            printf("  %c   : ", root->data);
        for (int i = 0; i < top; ++i)
            printf("%d", arr[i]);
        printf("\n");
    }
}

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

int main() {
    char input[1000];
    printf("Enter input string: ");
    scanf(" %[^\n]", input);

    int freq[MAX_CHAR], distinct = 0;
    char chars[MAX_CHAR];

    calculateFrequencies(input, freq, chars, &distinct);

    // Sorting frequencies and characters based on frequency and alphabetical order
    for (int i = 0; i < distinct - 1; i++) {
        for (int j = i + 1; j < distinct; j++) {
            if (freq[i] > freq[j] || (freq[i] == freq[j] && chars[i] > chars[j])) {
                // Swap frequencies
                int tempFreq = freq[i];
                freq[i] = freq[j];
                freq[j] = tempFreq;

                // Swap characters
                char tempChar = chars[i];
                chars[i] = chars[j];
                chars[j] = tempChar;
            }
        }
    }

    printf("\nCharacter Frequencies (sorted by frequency and alphabetical order):\n");
    for (int i = 0; i < distinct; i++) {
        if (chars[i] == ' ')
            printf("space : %d\n", freq[i]);
        else
            printf("  %c   : %d\n", chars[i], freq[i]);
    }

    struct MinHeapNode* root = buildHuffmanTree(chars, freq, distinct);

    int arr[MAX_TREE_HT], top = 0;
    printf("\nHuffman Codes:\n");
    printCodes(root, arr, top);

    return 0;
}
