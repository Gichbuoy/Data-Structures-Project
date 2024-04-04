#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node into the BST
struct Node* insertNode(struct Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->data) {
        root->left = insertNode(root->left, value);
    } else if (value > root->data) {
        root->right = insertNode(root->right, value);
    }
    return root;
}

// Function to delete a node from the BST
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) return root;
    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        struct Node* temp = root->right;
        while (temp && temp->left != NULL) {
            temp = temp->left;
        }
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to calculate the height of the BST
int height(struct Node* root) {
    if (root == NULL) return -1;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Function to print the level and height of a node
void printLevelHeight(struct Node* root, int key) {
    if (root == NULL) {
        printf("Node not found.\n");
        return;
    }
    if (key == root->data) {
        printf("Level: %d, Height: %d\n", 0, height(root));
    } else if (key < root->data) {
        printLevelHeight(root->left, key);
        printf("Level: %d, Height: %d\n", height(root->left) + 1, height(root));
    } else {
        printLevelHeight(root->right, key);
        printf("Level: %d, Height: %d\n", height(root->right) + 1, height(root));
    }
}

// Function to print the BST in inorder traversal
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

int main() {
    int arr[] = {30, 20, 40, 10, 25, 35, 45, 5, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    struct Node* root = NULL;
    
    // Creating the BST
    for (int i = 0; i < n; i++) {
        root = insertNode(root, arr[i]);
    }
    
    
    printf("BST created successfully.\n");
    
    printf("Inorder traversal of the BST: ");
    inorderTraversal(root);
    printf("\n");
    
    // Deleting a node (for example, deleting node with value 20)
    root = deleteNode(root, 20);
    
    printf("Inorder traversal after deleting node with value 20: ");
    inorderTraversal(root);
    printf("\n");
    
    // Printing the height of the BST
    printf("Height of the BST: %d\n", height(root));
    
    // Printing the level and height of a node (for example, node with value 30)
    printLevelHeight(root, 30);
    
    return 0;
}