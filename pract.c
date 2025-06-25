#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 256

typedef struct Node {
char ch;
int freq;
int l;
struct Node *left, *right;
int order;
} Node;

typedef struct {
    Node* data[MAX];
    int size;
} PQ;

int freq[MAX] = {0}, order_count = 0;

Node* createNode(char ch, int freq, int isLeaf) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->ch = ch;
    node->freq = freq;
    node->left = node->right = NULL;
    node->l = isLeaf;
    node->order = order_count++;
    return node;
}



int compare(Node* a, Node* b) {
    if (a->freq != b->freq) return a->freq - b->freq;
    if (a->l && b->l) return a->ch - b->ch;
    if (a->l != b->l) return a->l ? -1 : 1;
    return a->order - b->order;
}

void insertQueue(PQ* q, Node* node) {
    int i = q->size++;
    while (i > 0 && compare(node, q->data[(i - 1) / 2]) < 0) {
        q->data[i] = q->data[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    q->data[i] = node;
}

Node* removeMin(PQ* q) {
Node *min =q->data[0];
Node *last =q->data[--q->size];
int i=0;
int child;
while(i*2-1<q->size){
    child   =i*2+1;
    if(child+1<q->size  && compare(q->data[child+1], q->data[child])<0)
        child++;
        if(compare(last,q->data[child])<=0) break;
        q->data[i]=q->data[child];
   
        i=child;
}
q->data[i]=last;
return min;
}

void generateCodes(Node* root, char* code, int depth, char codes[MAX][MAX]) {
    if (!root) return;
    if (root->l) {
        code[depth] = '\0';
        strcpy(codes[(unsigned char)root->ch], code);
        return;
    }
    code[depth] = '0';
    generateCodes(root->left, code, depth + 1, codes);
    code[depth] = '1';
    generateCodes(root->right, code, depth + 1, codes);
}

Node* buildHuffmanTree(char* str) {
PQ q;
    q.size = 0;

for(int i=0;i<MAX;i++){
    freq[(unsigned char)str[i]]++;
}

for(int i = 0; i < MAX; i++) {
    if (freq[i] > 0) {
        insertQueue(&q, createNode((char)i, freq[i], 1));
    }
}

if(q.size >0) {
Node *left, *right, *newNode;
    while (q.size > 1) {
        left = removeMin(&q);
        right = removeMin(&q);
        newNode = createNode('\0', left->freq + right->freq, 0);
        newNode->left = left;
        newNode->right = right;
        insertQueue(&q, newNode);
    }
    return q.data[0];
}
    return removeMin(&q);
}

int main() {
    char str[1000], codes[MAX][MAX] = {{0}}, buffer[MAX];

    printf("Enter the input string: ");
    scanf(" %[^\n]", str);

    Node* root = buildHuffmanTree(str);
    generateCodes(root, buffer, 0, codes);

    printf("\nHuffman Codes:\nCharacter | Code\n------------------------\n");
    for (int i = 0; i < MAX; i++) {
        if (freq[i] > 0) {
            if (i == ' ')
                printf("   sp     | %s\n", codes[i]);
            else
                printf("    %c     | %s\n", i, codes[i]);
        }
    }

    return 0;
}