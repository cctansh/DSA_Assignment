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
    BinarySearchTree(const std::function<bool(const T&, const T&)>& comp)
        : root(nullptr), size(0), compare(comp) {
    }

    ~BinarySearchTree() {
        clear(root);
    }

    void insert(const T& data) {
        insert(root, data);
        size++;
    }

    void inOrderTraversal(const std::function<void(const T&)>& visit) const {
        inOrderTraversal(root, visit);
    }

    void clear() {
        clear(root);
        root = nullptr;
        size = 0;
    }

    int getSize() const {
        return size;
    }
};
