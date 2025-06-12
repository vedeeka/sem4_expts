#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 257

typedef struct Node {
    char ch;
    int freq;
    struct Node *left, *right;
} Node;

typedef struct {
    Node *tree;
    int freq;
} HeapNode;

HeapNode heap[MAX];
int heapSize = 0;

// Create new Huffman Tree node
Node* createNode(char ch, int freq, Node* left, Node* right) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}

// Sift down (adjust) to maintain min-heap property
void adjust(HeapNode a[], int i, int n) {
    HeapNode temp = a[i];
    int child;
    for (; 2*i <= n; i = child) {
        child = 2 * i;
        if (child < n && a[child + 1].freq < a[child].freq)
            child++;
        if (temp.freq <= a[child].freq)
            break;
        a[i] = a[child];
    }
    a[i] = temp;
}

// Heapify the array from bottom up
void heapify(HeapNode a[], int n) {
    for (int i = n / 2; i >= 1; i--) {
        adjust(a, i, n);
    }
}

// Remove and return the min element from the heap
HeapNode delMin(HeapNode a[], int *n) {
    HeapNode minElem = a[1];
    a[1] = a[*n];
    (*n)--;
    adjust(a, 1, *n);
    return minElem;
}

// Insert a new element into the heap (sift up)
void insertHeap(HeapNode a[], HeapNode item, int *n) {
    (*n)++;
    int i = *n;
    while (i > 1 && a[i / 2].freq > item.freq) {
        a[i] = a[i / 2];
        i /= 2;
    }
    a[i] = item;
}

// Build frequency table from input string
void buildFrequency(char *str, int freq[256]) {
    for (int i = 0; i < 256; i++)
        freq[i] = 0;
    for (int i = 0; str[i]; i++) {
        freq[(unsigned char)str[i]]++;
    }
}

// Build Huffman Tree and return root
Node* huffman(char *str) {
    int freq[256];
    buildFrequency(str, freq);

    heapSize = 0;

    // Insert all chars with freq > 0 into heap
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            Node *node = createNode((char)i, freq[i], NULL, NULL);
            heap[++heapSize].tree = node;
            heap[heapSize].freq = freq[i];
        }
    }

    // Build min heap
    heapify(heap, heapSize);

    // Build Huffman tree
    while (heapSize > 1) {
        HeapNode min1 = delMin(heap, &heapSize);
        HeapNode min2 = delMin(heap, &heapSize);

        Node *merged = createNode('$', min1.freq + min2.freq, min1.tree, min2.tree);
        HeapNode newNode = {merged, merged->freq};

        insertHeap(heap, newNode, &heapSize);
    }

    return heapSize == 1 ? heap[1].tree : NULL;
}

// Print Huffman codes recursively
void printCodes(Node* root, char *code, int depth) {
    if (!root->left && !root->right) {
        code[depth] = '\0';
        if (root->ch == ' ')
            printf("Character 'space': %s\n", code);
        else if (root->ch == '\n')
            printf("Character '\\n': %s\n", code);
        else if (root->ch < 32 || root->ch > 126) // Non-printable
            printf("Character 0x%02x: %s\n", (unsigned char)root->ch, code);
        else
            printf("Character '%c': %s\n", root->ch, code);
        return;
    }
    if (root->left) {
        code[depth] = '0';
        printCodes(root->left, code, depth + 1);
    }
    if (root->right) {
        code[depth] = '1';
        printCodes(root->right, code, depth + 1);
    }
}

int main() {
    char str[] = "j is the position of the partitioning element";

    Node* root = huffman(str);
    if (!root) {
        printf("Error: Huffman tree could not be built.\n");
        return 1;
    }

    char code[100];
    printf("Huffman Codes:\n");
    printCodes(root, code, 0);

    return 0;
}
