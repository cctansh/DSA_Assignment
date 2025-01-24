#pragma once
#include <iostream>
#include <iomanip>
#include "List.h"
#include "KeyValue.h"
#include<string>
#include "Movie.h"
#include "Actor.h"
using namespace std;

const int MAX_SIZE = 101;

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

	// Add an item with a key
	bool add(const KeyType& key, ValueType* newItem);

	// Remove an item by key
	bool remove(const KeyType& key);

	// Get an item by key
	ValueType* get(const KeyType& key) const;

	// Check if dictionary is empty
	bool isEmpty() const;

	// Get the number of items in the dictionary
	int getLength() const;

	// Retrieve all key-value pairs in the dictionary
	List<KeyValue<KeyType, ValueType>> getAllItemsWithKeys() const;

    void print();

    bool replace(const KeyType& key, ValueType* newItem);
};

// Constructor
template <typename ValueType>
Dictionary<ValueType>::Dictionary() {
    size = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        items[i] = nullptr;
    }
}

// Destructor
template <typename ValueType>
Dictionary<ValueType>::~Dictionary() {
    for (int i = 0; i < MAX_SIZE; i++) {
        Node* current = items[i];
        while (current) {
            Node* toDelete = current;
            current = current->next;
            delete toDelete->item;
            delete toDelete;
        }
    }
}

// Hash function
template <typename ValueType>
int Dictionary<ValueType>::hash(const KeyType& key) const {
    return key % MAX_SIZE;
}

// Add an item with a key
template <typename ValueType>
bool Dictionary<ValueType>::add(const KeyType& key, ValueType* newItem) {
    int index = hash(key);
    ValueType* allocatedItem = newItem ? newItem : new ValueType(*newItem);

    Node* newNode = new Node{ key, allocatedItem, nullptr };

    Node* current = items[index];
    if (!current) {
        items[index] = newNode;
    }
    else {
        while (current) {
            if (current->key == key) {
                // Key already exists, clean up and return false
                delete newNode->item;  // Free allocated item
                delete newNode;        // Free allocated node
                return false;
            }
            if (!current->next) break;  // Stop at the last node
            current = current->next;
        }
        current->next = newNode;
    }

    size++;
    return true;
}

// Remove an item by key
template <typename ValueType>
bool Dictionary<ValueType>::remove(const KeyType& key) {
    int index = hash(key);
    Node* current = items[index];
    Node* prev = nullptr;

    while (current) {
        if (current->key == key) {
            if (prev) {
                prev->next = current->next;
            }
            else {
                items[index] = current->next;
            }
            delete current->item;
            delete current;
            size--;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

// Get an item by key
template <typename ValueType>
ValueType* Dictionary<ValueType>::get(const KeyType& key) const {
    int index = hash(key);
    Node* current = items[index];
    while (current) {
        if (current->key == key) {
            return current->item;
        }
        current = current->next;
    }
    return nullptr;
}

// Check if dictionary is empty
template <typename ValueType>
bool Dictionary<ValueType>::isEmpty() const {
    return size == 0;
}

// Get the number of items in the dictionary
template <typename ValueType>
int Dictionary<ValueType>::getLength() const {
    return size;
}

// Retrieve all key-value pairs in the dictionary
template <typename ValueType>
List<KeyValue<KeyType, ValueType>> Dictionary<ValueType>::getAllItemsWithKeys() const {
    List<KeyValue<KeyType, ValueType>> allItemsWithKeys;
    for (int i = 0; i < MAX_SIZE; ++i) {
        Node* current = items[i];
        while (current) {
            KeyValue<KeyType, ValueType> kv{ current->key, current->item };
            allItemsWithKeys.add(kv);
            current = current->next;
        }
    }
    return allItemsWithKeys;
}

template <typename ValueType>
void Dictionary<ValueType>::print() {
    for (int i = 0; i < MAX_SIZE; ++i) {
        Node* current = items[i];
        while (current) {
            if (current->item) {
                cout << setw(6) << left << current->key << ". ";
                current->item->print();
            }
            
            current = current->next;
        }
    }
}

// Replace an item at a given key with a new item
template <typename ValueType>
bool Dictionary<ValueType>::replace(const KeyType& key, ValueType* newItem) {
    int index = hash(key);
    Node* current = items[index];

    while (current) {
        if (current->key == key) {
            delete current->item;       // Free the memory of the old item
            current->item = newItem;    // Assign the new item
            return true;
        }
        current = current->next;
    }
    return false; // Key not found
}