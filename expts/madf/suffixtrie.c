#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 256

// Trie Node structure
typedef struct TrieNode {
    int start;                     // Start index in text for edge label
    int end;                       // End index in text for edge label
    struct TrieNode* children[ALPHABET_SIZE]; // Children
    int is_leaf;                   // 1 if it's a leaf node
} TrieNode;

// Suffix Trie structure
typedef struct {
    TrieNode* root;
    char* text;
} SuffixTrie;

// Create a new Trie node
TrieNode* newNode(int start, int end) {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->start = start;
    node->end = end;
    node->is_leaf = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;
    return node;
}

// Build a basic suffix trie (not compact)
SuffixTrie* buildSuffixTrie(const char* text) {
    SuffixTrie* trie = (SuffixTrie*)malloc(sizeof(SuffixTrie));
    trie->text = strdup(text);  // Store text
    trie->root = newNode(-1, -1);

    int n = strlen(text);
    for (int i = 0; i < n; i++) {
        TrieNode* current = trie->root;
        for (int j = i; j < n; j++) {
            unsigned char index = text[j];
            if (!current->children[index]) {
                current->children[index] = newNode(j, j);
            }
            current = current->children[index];
        }
        current->is_leaf = 1;
    }
    return trie;
}

// Match pattern P in suffix trie
int suffixTrieMatch(SuffixTrie* T, const char* P) {
    int p = strlen(P);
    int j = 0;
    TrieNode* v = T->root;

    while (1) {
        int f = 1; // Flag to check if any child was processed

        for (int c = 0; c < ALPHABET_SIZE; ++c) {
            TrieNode* w = v->children[c];
            if (!w) continue;

            int i = w->start;
            if (P[j] == T->text[i]) {
                int x = w->end - w->start + 1;

                if (p <= x) {
                    if (strncmp(P + j, T->text + i, p) == 0)
                        return i - j; // Match
                    else
                        return -1;   // Mismatch
                } else {
                    if (strncmp(P + j, T->text + i, x) == 0) {
                        p -= x;
                        j += x;
                        v = w;
                        f = 0;
                        break;
                    } else {
                        return -1;
                    }
                }
            }
        }

        if (f || v->is_leaf) return -1;
    }
}

// Free trie recursively
void freeTrie(TrieNode* node) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i])
            freeTrie(node->children[i]);
    }
    free(node);
}

// Main
int main() {
    const char* text = "banana";
    const char* pattern = "nan";

    SuffixTrie* trie = buildSuffixTrie(text);
    int index = suffixTrieMatch(trie, pattern);

    if (index != -1)
        printf("Pattern '%s' found at index %d\n", pattern, index);
    else
        printf("Pattern '%s' not found in text\n", pattern);

    freeTrie(trie->root);
    free(trie->text);
    free(trie);

    return 0;
}
