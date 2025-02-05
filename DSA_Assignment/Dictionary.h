#pragma once
#include <iostream>
#include <iomanip>
#include "List.h"
#include "KeyValue.h"
#include<string>
#include "Movie.h"
#include "Actor.h"
using namespace std;

const int MAX_SIZE = 17000;

typedef int KeyType;

template <typename ValueType>
class Dictionary {
private:
	struct Node {
		KeyType key;
		ValueType* item;  // Raw pointer to the value
		Node* next;
	};

	Node* items[MAX_SIZE];
	int size;

	int hash(const KeyType& key) const;

public:
    // Constructor
    Dictionary();

    // Destructor
    ~Dictionary();

    // Adds an item with a specified key to the dictionary
    // Parameters: const KeyType& key - key for the item, ValueType* newItem - pointer to the new item
    // Pre : key should be unique in the dictionary
    // Post: Item is added to the dictionary if key is unique
    // Returns: bool - true if item is added, false if key exists
    bool add(const KeyType& key, ValueType* newItem);

    // Removes an item by key from the dictionary
    // Parameter: const KeyType& key - key of the item to remove
    // Pre : key should exist in the dictionary
    // Post: Item is removed if key exists
    // Returns: bool - true if item is removed, false otherwise
    bool remove(const KeyType& key);

    // Gets an item by key from the dictionary
    // Parameter: KeyType& key - key of item to retrieve
    // Pre : key should exist in the dictionary
    // Post: None
    // Returns: ValueType* - pointer to the item at the key
    ValueType* get(const KeyType& key) const;

    // Checks if the dictionary is empty
    // Pre : None
    // Post: None
    // Returns: bool - true if dictionary is empty, false otherwise
    bool isEmpty() const;

    // Gets the number of items in the dictionary
    // Pre : None
    // Post: None
    // Returns: int - number of items in the dictionary
    int getLength() const;

    // Retrieve all key-value pairs in the dictionary
    // Pre : Dictionary should not be empty
    // Post: None
    // Returns: List<KeyValue<KeyType, ValueType>> - List of KeyValue items
    List<KeyValue<KeyType, ValueType>> getAllItemsWithKeys() const;

    // Prints all items in the dictionary
    // Pre : None
    // Post: All items are printed to the console
    void print();

    // Replaces an item at a given key with a new item
    // Parameters: const KeyType& key - key of the item to replace, ValueType* newItem - pointer to the new item
    // Pre : key should exist in the dictionary
    // Post: Item at the specified key is replaced with newItem
    // Returns: bool - true if item is replaced, false otherwise
    bool replace(const KeyType& key, ValueType* newItem);
};

// Constructor
// Initializes the dictionary by setting all item pointers to nullptr and size to 0
template <typename ValueType>
Dictionary<ValueType>::Dictionary() {
    size = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        items[i] = nullptr;  // Initialize each bucket to nullptr
    }
}

// Destructor
// Frees all allocated memory by deleting each node and its corresponding item
template <typename ValueType>
Dictionary<ValueType>::~Dictionary() {
    for (int i = 0; i < MAX_SIZE; i++) {
        Node* current = items[i];  // Start at the first node in the bucket
        while (current) {
            Node* toDelete = current;  // Store the current node to delete
            current = current->next;  // Move to the next node
            delete toDelete->item;    // Free memory of the item
            delete toDelete;          // Free memory of the node
        }
    }
}

// Hash function
// Computes the hash index based on the key
template <typename ValueType>
int Dictionary<ValueType>::hash(const KeyType& key) const {
    return key % MAX_SIZE;  // Simple modulus hash function
}

// Add an item with a key
// Inserts a new key-item pair into the dictionary
// Returns false if the key already exists
template <typename ValueType>
bool Dictionary<ValueType>::add(const KeyType& key, ValueType* newItem) {
    int index = hash(key);  // Get the hash index for the key
    ValueType* allocatedItem = newItem ? newItem : new ValueType(*newItem);  // Allocate item if needed

    Node* newNode = new Node{ key, allocatedItem, nullptr };  // Create new node

    Node* current = items[index];  // Start at the bucket index
    if (!current) {
        items[index] = newNode;  // Insert node if bucket is empty
    }
    else {
        while (current) {
            if (current->key == key) {
                // Key already exists, clean up and return false
                delete newNode->item;  // Free allocated item
                delete newNode;        // Free allocated node
                return false;  // Duplicate key found
            }
            if (!current->next) break;  // Stop at the last node
            current = current->next;  // Move to the next node
        }
        current->next = newNode;  // Add new node to the end of the list
    }

    size++;  // Increment dictionary size
    return true;  // Successfully added
}

// Remove an item by key
// Deletes the key-item pair from the dictionary if found
template <typename ValueType>
bool Dictionary<ValueType>::remove(const KeyType& key) {
    int index = hash(key);  // Get the hash index for the key
    Node* current = items[index];  // Start at the bucket index
    Node* prev = nullptr;  // Keep track of the previous node

    while (current) {
        if (current->key == key) {
            if (prev) {
                prev->next = current->next;  // Bypass current node
            }
            else {
                items[index] = current->next;  // Update head if first node matches
            }
            delete current->item;  // Free memory of the item
            delete current;  // Free memory of the node
            size--;  // Decrement dictionary size
            return true;  // Successfully removed
        }
        prev = current;  // Move to the next node
        current = current->next;
    }
    return false;  // Key not found
}

// Get an item by key
// Retrieves the item associated with the key if found
template <typename ValueType>
ValueType* Dictionary<ValueType>::get(const KeyType& key) const {
    int index = hash(key);  // Get the hash index for the key
    Node* current = items[index];  // Start at the bucket index
    while (current) {
        if (current->key == key) {
            return current->item;  // Return the item if key matches
        }
        current = current->next;  // Move to the next node
    }
    return nullptr;  // Key not found
}

// Check if dictionary is empty
// Returns true if the dictionary contains no items
template <typename ValueType>
bool Dictionary<ValueType>::isEmpty() const {
    return size == 0;  // Check if size is zero
}

// Get the number of items in the dictionary
// Returns the total number of items
template <typename ValueType>
int Dictionary<ValueType>::getLength() const {
    return size;  // Return the current size
}

// Retrieve all key-value pairs in the dictionary
// Returns a list of all key-value pairs
template <typename ValueType>
List<KeyValue<KeyType, ValueType>> Dictionary<ValueType>::getAllItemsWithKeys() const {
    List<KeyValue<KeyType, ValueType>> allItemsWithKeys;
    for (int i = 0; i < MAX_SIZE; ++i) {
        Node* current = items[i];  // Start at the bucket index
        while (current) {
            KeyValue<KeyType, ValueType> kv{ current->key, current->item };  // Create key-value pair
            allItemsWithKeys.add(kv);  // Add to list
            current = current->next;  // Move to the next node
        }
    }
    return allItemsWithKeys;  // Return list of key-value pairs
}

// Print all items in the dictionary
// Displays each key and its associated item
template <typename ValueType>
void Dictionary<ValueType>::print() {
    for (int i = 0; i < MAX_SIZE; ++i) {
        Node* current = items[i];  // Start at the bucket index
        while (current) {
            if (current->item) {
                cout << setw(6) << left << current->key << ". ";  // Print key
                current->item->print();  // Call the print function of the item
            }
            current = current->next;  // Move to the next node
        }
    }
}

// Replace an item at a given key with a new item
// Updates the item if the key exists
template <typename ValueType>
bool Dictionary<ValueType>::replace(const KeyType& key, ValueType* newItem) {
    int index = hash(key);  // Get the hash index for the key
    Node* current = items[index];  // Start at the bucket index

    while (current) {
        if (current->key == key) {
            delete current->item;  // Free the memory of the old item
            current->item = newItem;  // Assign the new item
            return true;  // Successfully replaced
        }
        current = current->next;  // Move to the next node
    }
    return false;  // Key not found
}
