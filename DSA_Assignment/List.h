/*
DSA T02
Group 7
Tan Si Huei Chloe S10260078
Ng Joe Yi S10262850
*/
#pragma once
#include <iostream>
#include <memory>
#include <functional>
#include <type_traits>
#include <stdexcept>
using namespace std;

template <typename T>
class List {
private:
    struct Node {
        T item;
        Node* next;
    };

    Node* firstNode;
    int size;

public:
    // Constructor
    List();

    // Destructor
    ~List();

    // Adds an item to the list
    // Parameter: const T& item - item to add
    // Pre : List size should be less than 17000
    // Post: item is added to the list if size limit not reached
    // Returns: bool - true if item added, false otherwise
    bool add(const T& item);

    // Removes an item at a specific index
    // Parameter: int index - index of item to remove
    // Pre : index should be within bounds of the list
    // Post: Item at specified index is removed
    void remove(int index);

    // Gets an item at a specific index
    // Parameter: int index - index of item to retrieve
    // Pre : index should be within bounds of the list
    // Post: None
    // Returns: const T& - item at the specified index
    const T& get(int index) const;

    // Checks if an item exists in the list
    // Parameter: const T& item - item to check
    // Pre : None
    // Post: None
    // Returns: bool - true if item exists, false otherwise
    bool contains(const T& item) const;

    // Prints all items in the list
    // Pre : None
    // Post: All items are printed to the console
    void print() const;

    // Checks if the list is empty
    // Pre : None
    // Post: None
    // Returns: bool - true if the list is empty, false otherwise
    bool isEmpty() const;

    // Gets the number of items in the list
    // Pre : None
    // Post: None
    // Returns: int - number of items in the list
    int getLength() const;
};

// Constructor
// Initializes an empty list with no nodes and size set to 0
template <typename T>
List<T>::List() : firstNode(nullptr), size(0) {}

// Destructor
// Frees all allocated memory by deleting each node and its item if it's a pointer
template <typename T>
List<T>::~List() {
    while (firstNode) {
        Node* temp = firstNode;        // Store the current node
        firstNode = firstNode->next;   // Move to the next node

        if constexpr (is_pointer<T>::value) {
            delete temp->item;        // Delete the object pointed to by the pointer if T is a pointer
        }

        delete temp;  // Delete the node itself
    }
}

// Adds an item to the list
// Returns false if the list exceeds 17000 items
template <typename T>
bool List<T>::add(const T& item) {
    if (size >= 17000) return false;  // Prevent exceeding maximum size

    Node* newNode = new Node{ item, nullptr };  // Create a new node with the item
    if (!firstNode) {
        firstNode = newNode;  // If the list is empty, set the first node
    }
    else {
        newNode->next = firstNode;  // Point the new node's `next` to the current `firstNode`
        firstNode = newNode;  // Update `firstNode` to be the new node
    }

    size++;  // Increment the size of the list
    return true;  // Indicate successful addition
}

// Removes an item at a specific index
// Throws out_of_range exception if index is invalid
template <typename T>
void List<T>::remove(int index) {
    if (index < 0 || index >= size) throw out_of_range("Index out of range");  // Check for valid index

    Node* temp = firstNode;  // Start at the first node
    Node* prev = nullptr;    // Keep track of the previous node

    for (int i = 0; i < index; i++) {
        prev = temp;         // Move previous pointer
        temp = temp->next;   // Move current pointer
    }

    if (prev) {
        prev->next = temp->next;  // Bypass the node to be removed
    }
    else {
        firstNode = temp->next;   // Update head if first node is removed
    }

    if constexpr (is_pointer<T>::value) {
        delete temp->item;  // Delete the object pointed to by the pointer if T is a pointer
    }

    delete temp;  // Delete the node itself
    size--;       // Decrement the size of the list
}

// Retrieves an item at a specific index
// Throws out_of_range exception if index is invalid
template <typename T>
const T& List<T>::get(int index) const {
    if (index < 0 || index >= size) throw out_of_range("Index out of range");  // Check for valid index

    Node* temp = firstNode;  // Start at the first node
    for (int i = 0; i < index; i++) {
        temp = temp->next;  // Traverse to the desired index
    }

    return temp->item;  // Return the item at the index
}

// Checks if an item exists in the list
// Returns true if item is found, otherwise false
template <typename T>
bool List<T>::contains(const T& item) const {
    Node* temp = firstNode;  // Start at the first node
    while (temp) {
        if (temp->item == item) {
            return true;  // Item found
        }
        temp = temp->next;  // Move to the next node
    }
    return false;  // Item not found
}

// Prints all items in the list
// Assumes T is a pointer and the pointed-to type has operator<< defined
template <typename T>
void List<T>::print() const {
    Node* temp = firstNode;  // Start at the first node
    while (temp) {
        cout << *temp->item << endl;  // Dereference and print the item
        temp = temp->next;  // Move to the next node
    }
}

// Checks if the list is empty
// Returns true if size is 0
template <typename T>
bool List<T>::isEmpty() const {
    return size == 0;  // Check if size is zero
}

// Gets the number of items in the list
// Returns the size of the list
template <typename T>
int List<T>::getLength() const {
    return size;  // Return the size of the list
}
