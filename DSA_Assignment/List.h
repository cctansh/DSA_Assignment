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

    // Add an item to the list
    bool add(const T& item);

    // Remove an item at a specific index
    void remove(int index);

    // Get an item at a specific index
    const T& get(int index) const;

    // Print all items
    void print() const;

    bool isEmpty() const;

    int getLength() const;
};

template <typename T>
List<T>::List() : firstNode(nullptr), size(0) {}

template <typename T>
List<T>::~List() {
    while (firstNode) {
        Node* temp = firstNode;
        firstNode = firstNode->next;

        if constexpr (is_pointer<T>::value) {
            delete temp->item; // Deletes the object pointed to by the pointer
        }

        delete temp; // Deletes the Node itself
    }
}

template <typename T>
bool List<T>::add(const T& item) {
    if (size >= 17000) return false;

    Node* newNode = new Node{ item, nullptr };
    if (!firstNode) {
        firstNode = newNode;
    }
    else {
        Node* temp = firstNode;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }

    size++;
    return true;
}

template <typename T>
void List<T>::remove(int index) {
    if (index < 0 || index >= size) throw out_of_range("Index out of range");

    Node* temp = firstNode;
    Node* prev = nullptr;

    for (int i = 0; i < index; i++) {
        prev = temp;
        temp = temp->next;
    }

    if (prev) {
        prev->next = temp->next;
    }
    else {
        firstNode = temp->next;
    }

    if constexpr (is_pointer<T>::value) {
        delete temp->item; // Deletes the object pointed to by the pointer
    }

    delete temp; // Delete the Node itself
    size--;
}

template <typename T>
const T& List<T>::get(int index) const {
    if (index < 0 || index >= size) throw out_of_range("Index out of range");

    Node* temp = firstNode;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }

    return temp->item;
}

template <typename T>
void List<T>::print() const {
    Node* temp = firstNode;
    while (temp) {
        cout << *temp->item << endl;  // Assuming T is a pointer and has operator<< defined
        temp = temp->next;
    }
}

template <typename T>
bool List<T>::isEmpty() const {
    return size == 0;
}

template <typename T>
int List<T>::getLength() const {
    return size;
}