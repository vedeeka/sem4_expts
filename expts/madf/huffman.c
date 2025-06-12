#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 256
#include <time.h>

typedef struct Node {
    char ch;
    int freq;
    struct Node *left, *right;
    int l;          // leaf flag (1 if leaf)
    int order;      // original order
    int tn;         // tree node number
} Node;

typedef struct {
    Node* data[MAX];
    int size;
} PQ;

int freq[MAX] = {0}, oc = 0, tc = 1;

// Create a new node
Node* createN(char ch, int freq, int l) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->ch = ch;
    node->freq = freq;
    node->left = node->right = NULL;
    node->l = l;
    node->order = oc++;
    node->tn = 0;
    return node;
}

// Initialize priority queue
void initQueue(PQ* q) {
    q->size = 0;
}

// Compare nodes for priority queue
int compare(Node* a, Node* b) {
    if (a->freq != b->freq)
        return a->freq - b->freq;
    if (a->l && b->l)
        return a->ch - b->ch;
    if (a->l != b->l)
        return a->l ? -1 : 1;
    return a->order - b->order;
}

// Insert node into priority queue
void insertQ(PQ* q, Node* node) {
    int i = q->size++;
    while (i > 0 && compare(node, q->data[(i - 1) / 2]) < 0) {
        q->data[i] = q->data[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    q->data[i] = node;
}

// Remove minimum node from priority queue
Node* removeMin(PQ* q) {
    Node* min = q->data[0];
    Node* last = q->data[--q->size];
    int i = 0, child;
    while (i * 2 + 1 < q->size) {
        child = i * 2 + 1;
        if (child + 1 < q->size && compare(q->data[child + 1], q->data[child]) < 0)
            child++;
        if (compare(last, q->data[child]) <= 0)
            break;
        q->data[i] = q->data[child];
        i = child;
    }
    q->data[i] = last;
    return min;
}

// Improved tree visualization with better formatting
void printTree(Node* root, int depth) {
    if (!root) return;
    
    // Process right subtree first (will appear at top)
    printTree(root->right, depth + 1);
    
    // Print current node with proper indentation
    char buffer[100] = {0};
    for (int i = 0; i < depth; i++)
        strcat(buffer, "    ");
    
    if (root->l) {
        // Leaf node with character
        if (root->ch == ' ')
            printf("%s├── (%d) 'space'\n", buffer, root->freq);
        else if (root->ch == '\n')
            printf("%s├── (%d) '\\n'\n", buffer, root->freq);
        else if (root->ch == '\t')
            printf("%s├── (%d) '\\t'\n", buffer, root->freq);
        else
            printf("%s├── (%d) '%c'\n", buffer, root->freq, root->ch);
    } else {
        // Internal node
        printf("%s├── (%d)", buffer, root->freq);
        if (root->tn > 0)
            printf(" Tree-%d", root->tn);
        printf("\n");
    }
    
    // Process left subtree (will appear at bottom)
    printTree(root->left, depth + 1);
}

// Improved queue display
void printQ(PQ* q) {
    // Sort queue elements for display
    Node* temp[MAX];
    for (int i = 0; i < q->size; i++) {
        temp[i] = q->data[i];
    }
    
    for (int i = 0; i < q->size - 1; i++) {
        for (int j = i + 1; j < q->size; j++) {
            if (compare(temp[i], temp[j]) > 0) {
                Node* t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }
    
    // Header for queue display
    printf("\n┌─── Priority Queue ───────────────────────┐\n");
    printf("│ Node  | ");
    
    // Print node identifiers
    for (int i = 0; i < q->size; i++) {
        if (temp[i]->l) {
            if (temp[i]->ch == ' ')
                printf("space ");
            else if (temp[i]->ch == '\n')
                printf("\\n    ");
            else if (temp[i]->ch == '\t')
                printf("\\t    ");
            else
                printf("'%c'   ", temp[i]->ch);
        } else {
            printf("T%-2d   ", temp[i]->tn);
        }
    }
    printf("\n│ Freq  | ");
    
    // Print frequencies
    for (int i = 0; i < q->size; i++) {
        printf("%-6d", temp[i]->freq);
    }
    printf("\n└───────────────────────────────────────────┘\n");
}

// Generate Huffman codes
void generateHuffmanCodes(Node* root, char* code, int depth, char codes[MAX][MAX]) {
    if (!root) return;
    
    if (root->l) {
        code[depth] = '\0';
        strcpy(codes[(unsigned char)root->ch], code);
        return;
    }
    
    code[depth] = '0';
    generateHuffmanCodes(root->left, code, depth + 1, codes);
    
    code[depth] = '1';
    generateHuffmanCodes(root->right, code, depth + 1, codes);
}

// Build Huffman tree
Node* buildHuffmanTree(char* str) {
    PQ q;
    initQueue(&q);
    
    // Count character frequencies
    for (int i = 0; str[i]; i++)
        freq[(unsigned char)str[i]]++;

    // Create leaf nodes for each character
    for (int i = 0; i < MAX; i++) {
        if (freq[i] > 0) {
            Node* node = createN((char)i, freq[i], 1);
            insertQ(&q, node);
        }
    }
    
    printf("\n✧ INITIAL CHARACTER FREQUENCIES ✧\n");
    printQ(&q);
    printf("\n══════════════════════════════════════════════\n");
    
    // Build the Huffman tree
    int step = 1;
    while (q.size > 1) {
        Node* t1 = removeMin(&q);
        Node* t2 = removeMin(&q);
        
        Node* newNode = createN('\0', t1->freq + t2->freq, 0);
        newNode->left = t1;
        newNode->right = t2;
        newNode->tn = tc++;
        
        printf("\n✧ STEP %d: Combining nodes (freq: %d + %d = %d) ✧\n", 
               step++, t1->freq, t2->freq, newNode->freq);
        printf("\nTree-%d Structure:\n", newNode->tn);
        printTree(newNode, 0);
        
        insertQ(&q, newNode);
        printQ(&q);
        printf("\n══════════════════════════════════════════════\n");
    }
    
    return removeMin(&q);
}

int main() {
    char str[1000], codes[MAX][MAX] = {{0}}, buffer[MAX];
    
    printf("╔═══════════════════════════════════════╗\n");
    printf("║        HUFFMAN CODING PROGRAM         ║\n");
    printf("╚═══════════════════════════════════════╝\n");
    
    printf("\nEnter the input string: ");
    scanf("%[^\n]", str);
    
    printf("\n✧ BUILDING HUFFMAN TREE ✧\n");
    Node* root = buildHuffmanTree(str);
    
    // Generate codes
    generateHuffmanCodes(root, buffer, 0, codes);
    
    // Calculate original and compressed sizes
    int originalSize = strlen(str) * 8;
    int compressedSize = 0;
    
    for (int i = 0; i < MAX; i++) {
        if (freq[i] > 0) {
            compressedSize += freq[i] * strlen(codes[i]);
        }
    }
    
    // Print the final Huffman codes table
    printf("\n✧ FINAL HUFFMAN CODES ✧\n");
    printf("┌────────────┬────────────┬────────────┐\n");
    printf("│ Character  │ Frequency  │ Code       │\n");
    printf("├────────────┼────────────┼────────────┤\n");
    
    for (int i = 0; i < MAX; i++) {
        if (freq[i] > 0) {
            printf("│ ");
            if (i == ' ')
                printf("space      ");
            else if (i == '\n')
                printf("\\n         ");
            else if (i == '\t')
                printf("\\t         ");
            else
                printf("'%c'         ", i);
                
            printf("│ %-10d │ %-10s │\n", freq[i], codes[i]);
        }
    }
    printf("├────────────┼────────────┼────────────┤\n");
    printf("│ TOTAL      │ %-10d │            │\n", strlen(str));
    printf("└────────────┴────────────┴────────────┘\n");
    
    // Print compression statistics
    float compressionRatio = (float)originalSize / compressedSize;
    

    
    return 0;
}