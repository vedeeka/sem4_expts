void printTree(struct treeNode* root, int level) {
    if (root == NULL) return;

    // Print indentation
    for (int i = 0; i < level; i++) {
        printf("    ");
    }

    // Print the node
    printf("%s\n", root->key);

    // Process children
    printTree(root->left, level + 1);
    printTree(root->right, level + 1);
}
