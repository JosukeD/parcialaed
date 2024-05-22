#include <iostream>
#include <algorithm>

class Node {
public:
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int value) : data(value), left(nullptr), right(nullptr), height(1) {}
};

class AVL {
private:
    Node* root;

    // Get the height of the node
    int height(Node* node) {
        return node == nullptr ? 0 : node->height;
    }

    // Get balance factor of node
    int getBalance(Node* node) {
        return node == nullptr ? 0 : height(node->left) - height(node->right);
    }

    // Right rotate subtree rooted with y
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        return x;
    }

    // Left rotate subtree rooted with x
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;

        return y;
    }

    // Insert a node and balance the tree
    Node* insert(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }

        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        } else {
            return node; // Equal keys not allowed
        }

        node->height = 1 + std::max(height(node->left), height(node->right));

        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && value < node->left->data) {
            return rightRotate(node);
        }

        // Right Right Case
        if (balance < -1 && value > node->right->data) {
            return leftRotate(node);
        }

        // Left Right Case
        if (balance > 1 && value > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && value < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // Inorder traversal
    void inorder(Node* node) {
        if (node == nullptr) return;
        inorder(node->left);
        std::cout << node->data << " ";
        inorder(node->right);
    }

    // Preorder traversal
    void preorder(Node* node) {
        if (node == nullptr) return;
        std::cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    // Postorder traversal
    void postorder(Node* node) {
        if (node == nullptr) return;
        postorder(node->left);
        postorder(node->right);
        std::cout << node->data << " ";
    }

public:
    AVL() : root(nullptr) {}

    // Public insertion method
    void insert(int value) {
        root = insert(root, value);
    }

    // Public traversal methods
    void inorder() {
        inorder(root);
        std::cout << std::endl;
    }

    void preorder() {
        preorder(root);
        std::cout << std::endl;
    }

    void postorder() {
        postorder(root);
        std::cout << std::endl;
    }
};

int main() {
    AVL tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    std::cout << "Inorder traversal: ";
    tree.inorder();

    std::cout << "Preorder traversal: ";
    tree.preorder();

    std::cout << "Postorder traversal: ";
    tree.postorder();

    return 0;
}
