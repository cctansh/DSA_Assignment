#pragma once
#include <iostream>
#include <functional>
using namespace std;

template <typename T>
class SortedLinkedList {
private:
    struct Node {
        T item;
        Node* next;
    };

    Node* head;
    int size;

    // Comparison function for sorting
    function<bool(const T&, const T&)> compare;

public:
    // Constructor
    SortedLinkedList(function<bool(const T&, const T&)> comp)
        : head(nullptr), size(0), compare(comp) {
    }

    // Destructor
    ~SortedLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Add an item in sorted order
    void add(const T& item) {
        Node* newNode = new Node{ item, nullptr };
        if (!head || compare(item, head->item)) {
            newNode->next = head;
            head = newNode;
        }
        else {
            Node* current = head;
            while (current->next && !compare(item, current->next->item)) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        size++;
    }

    // Print all items
    void print(function<void(const T&)> printFunction = nullptr) const {
        Node* current = head;
        while (current) {
            if (printFunction) {
                printFunction(current->item); // Use the custom print function
            }
            else {
                // Default printing behavior
                if constexpr (std::is_pointer<T>::value) {
                    cout << *current->item << endl; // Dereference the pointer
                }
                else {
                    cout << current->item << endl;
                }
            }
            current = current->next;
        }
    }

    // Get the size of the list
    int getSize() const {
        return size;
    }
};
