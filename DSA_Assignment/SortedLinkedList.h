/*#pragma once
#include <iostream>
using namespace std;

class SortedLinkedList {
private:
    struct Node {
        void* item;  // generic item could be actor or movie
        Node* next;
    };
    Node* firstNode;
    int size;

    // Comparator function for sorting
    int (*compare)(void*, void*);

public:
    SortedLinkedList(int (*comparator)(void*, void*)); // constructor with comparator
    ~SortedLinkedList();

	// Add an item to the list
	// pre : none
	// post: new item is added to the list at the correct position
	//       size of list is increased by 1
	// return true if the item is added successfully otherwise return false
    bool add(void* item);

    // display the items in the sorted list using provided print function
	// pre : print function is defined
    // post : items are displayed in a sorted order (asc)
    void display(void (*print)(void*));

    // retrieves number of items currently in the sorted linked list
    // pre : none
	// post : length of the list is returned
	// return the number of items in the list
    int getLength();
};
*/

#pragma once
#include <iostream>
using namespace std;

template <typename T>
class SortedList {
private:
    struct Node {
        T item;
        Node* next;
    };

    Node* firstNode;
    int size;

public:
    SortedList() : firstNode(nullptr) {}

    ~SortedList() {
        while (firstNode) {
            Node* temp = firstNode;
            firstNode = firstNode->next;
            delete temp; // Deletes the Node itself
        }
    }

    void add(const T& item) {
        Node* newNode = new Node{ item, nullptr };

        if (!firstNode || *item < *firstNode->item) { 
            newNode->next = firstNode;
            firstNode = newNode;
        }
        else {
            Node* current = firstNode;
            while (current->next && *current->next->item < *item) { 
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    void print() const {
        Node* current = firstNode;
        while (current) {
            if (current->item) {
                current->item->print();
            }
            else {
                cout << "Null item" << endl;
            }
            current = current->next;
        }
    }
};