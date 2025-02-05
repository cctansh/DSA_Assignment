#pragma once
#include <functional>
#include <iostream>

template <typename T>
class BinarySearchTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;

        Node(const T& data) : data(data), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int size;
    std::function<bool(const T&, const T&)> compare;

    // Helper functions
    void insert(Node*& node, const T& data) {
        if (!node) {
            node = new Node(data); // Insert new node
        }
        else if (compare(data, node->data)) {
            insert(node->left, data); // Go to the left subtree
        }
        else {
            insert(node->right, data); // Go to the right subtree
        }
    }

    void inOrderTraversal(Node* node, const std::function<void(const T&)>& visit) const {
        if (!node) return;

        inOrderTraversal(node->left, visit);
        visit(node->data);
        inOrderTraversal(node->right, visit);
    }

    void clear(Node* node) {
        if (!node) return;

        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    // Constructor
    BinarySearchTree(const std::function<bool(const T&, const T&)>& comp)
        : root(nullptr), size(0), compare(comp) {
    }

    // Deconstructor
    // Calls clear() to remove all nodes from tree and free memory
    ~BinarySearchTree() {
        clear(root);
    }

    // Inserts an element into the binary search tree
    // Parameter: const T& data - element to insert
    // Pre : data should be of a type compatible with the comparison function
    // Post: data is inserted into the tree in the correct position
    void insert(const T& data) {
        insert(root, data);
        size++;
    }

    // Performs in-order traversal of the tree
    // Parameter: const std::function<void(const T&)>& visit - function to apply to each node's data
    // Pre : None
    // Post: visit function is applied to each element in in-order sequence
    void inOrderTraversal(const std::function<void(const T&)>& visit) const {
        inOrderTraversal(root, visit);
    }

    // Clears the binary search tree
    // Pre : None
    // Post: All nodes are removed from the tree, and memory is freed
    void clear() {
        clear(root);
        root = nullptr;
        size = 0;
    }

    // Returns the number of elements in the binary search tree
    // Pre : None
    // Post: None
    // Returns: int - number of elements in the tree
    int getSize() const {
        return size;
    }
};
