#pragma once
#include <functional>
#include <iostream>

template <typename T>
class BinarySearchTree {
private:
    // Node structure representing each element in the tree
    struct Node {
        T data;         // Data stored in the node
        Node* left;     // Pointer to the left child
        Node* right;    // Pointer to the right child

        // Constructor to initialize node with data
        // Parameter: const T& data - data to store in the node
        Node(const T& data) : data(data), left(nullptr), right(nullptr) {}
    };

    Node* root;  // Pointer to the root of the tree
    int size;    // Number of elements in the tree
    std::function<bool(const T&, const T&)> compare;  // Comparison function for ordering

    // Helper function to insert an element into the tree
    // Parameters: Node*& node - reference to the current node
    //             const T& data - data to insert
    // Pre : data should be compatible with the comparison function
    // Post: data is inserted in the correct position in the tree
    void insert(Node*& node, const T& data) {
        if (!node) {
            node = new Node(data);  // Insert new node if current node is null
        }
        else if (compare(data, node->data)) {
            insert(node->left, data);  // Recursively insert into the left subtree
        }
        else {
            insert(node->right, data);  // Recursively insert into the right subtree
        }
    }

    // Helper function to perform in-order traversal
    // Parameters: Node* node - current node
    //             const std::function<void(const T&)>& visit - function to apply to each node's data
    // Pre : None
    // Post: visit function is applied to each element in in-order sequence
    void inOrderTraversal(Node* node, const std::function<void(const T&)>& visit) const {
        if (!node) return;  // Base case: return if node is null

        inOrderTraversal(node->left, visit);  // Traverse left subtree
        visit(node->data);                   // Visit current node
        inOrderTraversal(node->right, visit); // Traverse right subtree
    }

    // Helper function to clear the tree and free memory
    // Parameter: Node* node - current node
    // Pre : None
    // Post: All nodes are removed, and memory is freed
    void clear(Node* node) {
        if (!node) return;  // Base case: return if node is null

        clear(node->left);  // Clear left subtree
        clear(node->right); // Clear right subtree
        delete node;        // Delete current node
    }

public:
    // Constructor
    // Initializes an empty binary search tree with a custom comparison function
    // Parameter: const std::function<bool(const T&, const T&)>& comp - comparison function
    BinarySearchTree(const std::function<bool(const T&, const T&)>& comp)
        : root(nullptr), size(0), compare(comp) {}

    // Destructor
    // Frees all memory allocated by the tree
    // Pre : None
    // Post: All nodes are removed, and memory is freed
    ~BinarySearchTree() {
        clear(root);
    }

    // Inserts an element into the binary search tree
    // Parameter: const T& data - element to insert
    // Pre : data should be of a type compatible with the comparison function
    // Post: data is inserted into the tree in the correct position
    void insert(const T& data) {
        insert(root, data);  // Insert data starting from the root
        size++;              // Increment size after insertion
    }

    // Performs in-order traversal of the tree
    // Parameter: const std::function<void(const T&)>& visit - function to apply to each node's data
    // Pre : None
    // Post: visit function is applied to each element in in-order sequence
    void inOrderTraversal(const std::function<void(const T&)>& visit) const {
        inOrderTraversal(root, visit);  // Start traversal from the root
    }

    // Clears the binary search tree
    // Pre : None
    // Post: All nodes are removed from the tree, and memory is freed
    void clear() {
        clear(root);   // Clear all nodes starting from the root
        root = nullptr; // Reset root to null
        size = 0;      // Reset size to 0
    }

    // Returns the number of elements in the binary search tree
    // Pre : None
    // Post: None
    // Returns: int - number of elements in the tree
    int getSize() const {
        return size;
    }
};
