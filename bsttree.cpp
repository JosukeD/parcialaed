#include <iostream>
#include <queue>
#include <stack>

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    // Helper function for insertion
    Node* insert(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        }
        return node;
    }

    // Helper function for search
    Node* search(Node* node, int value) {
        if (node == nullptr || node->data == value) {
            return node;
        }
        if (value < node->data) {
            return search(node->left, value);
        } else {
            return search(node->right, value);
        }
    }

    // Helper functions for traversals
    void inorder(Node* node) {
        if (node == nullptr) return;
        inorder(node->left);
        std::cout << node->data << " ";
        inorder(node->right);
    }

    void preorder(Node* node) {
        if (node == nullptr) return;
        std::cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) {
        if (node == nullptr) return;
        postorder(node->left);
        postorder(node->right);
        std::cout << node->data << " ";
    }

public:
    BST() : root(nullptr) {}

    // Public insertion method
    void insert(int value) {
        root = insert(root, value);
    }

    // Public search method
    bool search(int value) {
        return search(root, value) != nullptr;
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

    // Depth-first search (DFS) using stack
    void depthFirstSearch(int value) {
        if (root == nullptr) {
            std::cout << "Tree is empty" << std::endl;
            return;
        }

        std::stack<Node*> stack;
        stack.push(root);

        while (!stack.empty()) {
            Node* current = stack.top();
            stack.pop();

            if (current->data == value) {
                std::cout << "Found " << value << std::endl;
                return;
            }

            if (current->right != nullptr) {
                stack.push(current->right);
            }
            if (current->left != nullptr) {
                stack.push(current->left);
            }
        }

        std::cout << "Value " << value << " not found" << std::endl;
    }

    // Breadth-first search (BFS) using queue
    void breadthFirstSearch(int value) {
        if (root == nullptr) {
            std::cout << "Tree is empty" << std::endl;
            return;
        }

        std::queue<Node*> queue;
        queue.push(root);

        while (!queue.empty()) {
            Node* current = queue.front();
            queue.pop();

            if (current->data == value) {
                std::cout << "Found " << value << std::endl;
                return;
            }

            if (current->left != nullptr) {
                queue.push(current->left);
            }
            if (current->right != nullptr) {
                queue.push(current->right);
            }
        }

        std::cout << "Value " << value << " not found" << std::endl;
    }
};

int main() {
    BST tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(70);
    tree.insert(60);
    tree.insert(80);

    std::cout << "Inorder traversal: ";
    tree.inorder();

    std::cout << "Preorder traversal: ";
    tree.preorder();

    std::cout << "Postorder traversal: ";
    tree.postorder();

    std::cout << "Depth-first search for 40: ";
    tree.depthFirstSearch(40);

    std::cout << "Breadth-first search for 40: ";
    tree.breadthFirstSearch(40);

    std::cout << "Depth-first search for 90: ";
    tree.depthFirstSearch(90);

    std::cout << "Breadth-first search for 90: ";
    tree.breadthFirstSearch(90);

    return 0;
}
