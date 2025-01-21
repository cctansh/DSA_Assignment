#pragma once
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
