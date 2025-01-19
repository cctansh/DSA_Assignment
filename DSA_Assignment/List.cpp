#include "List.h"

List::List() {
    firstNode = nullptr;
    size = 0;
};			// constructor

List::~List() {
    while (!isEmpty())
        remove(0);
};		// destructor

// add an item to the back of the list (append)
// pre : size < MAX_SIZE
// post: item is added to the back of the list
//       size of list is increased by 1
bool List::add(ItemType item) {
    // check if list has reached max size
    if (size >= MAX_SIZE) {
        return false;
    }

    // create a new node with data
    Node* newNode = new Node;
    newNode->item = item;
    newNode->next = nullptr;

    // appending node to the back of the list
    if (firstNode == nullptr) { // if list is empty
        firstNode = newNode; // set head to point to new node
    }
    else {
        Node* temp = firstNode; // point to the first node
        // traversing to the end of the list
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode; // set last node to point to new node
    }
    size++;
    return true;
};

// add an item at a specified position in the list (insert)
// pre : 0 <= index <= size
// post: item is added to the specified position in the list
//       items after the position are shifted back by 1 position
//       size of list is increased by 1
bool List::add(int index, ItemType item) {
    // check if valid index
    if (index < 0 || index > size) {
        return false;
    }

    // create a new node with data
    Node* newNode = new Node;
    newNode->item = item;
    newNode->next = nullptr;

    if (index == 0) { // if adding at the start of list
        newNode->next = firstNode; // set new node to point to original first node
        firstNode = newNode; // head ref now points to new node
    }
    else {
        Node* temp = firstNode; // point to first node
        // traversing to 1 before index position
        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        newNode->next = temp->next; // have new node point to the next node
        temp->next = newNode; // set 'current' node to point to new node
    }
    size++;
    return true;
};

// remove an item at a specified position in the list
// pre : 0 <= index < size
// post: item is removed the specified position in the list
//       items after the position are shifted forward by 1 position
//       size of list is decreased by 1
void List::remove(int index) {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of range");
    }

    Node* temp = firstNode; // set a temp pointer to first node

    if (index == 0) { // if removing first node
        firstNode = temp->next; // set head to point to second node
    }
    else {
        Node* prev = nullptr; // keep track of node previous to deleted node
        // loop to traverse the list
        for (int i = 0; i < index; i++) {
            prev = temp;        // set previous node to current node
            temp = temp->next;  // set current node to next node
        }
        prev->next = temp->next; // set previous node to point to the node after deleted node
    }

    delete temp; // delete the removed node
    size--;      // decrease size by 1
};

// get an item at a specified position of the list (retrieve)
// pre : 0 <= index < size
// post: none
// return the item in the specified index of the list
ItemType List::get(int index) {
    if (index < 0 || index >= size) { // Check if the index is valid
        throw out_of_range("Index out of range");
    }

    Node* temp = firstNode; // Start from the first node

    for (int i = 0; i < index; i++) { // Traverse to the desired index
        temp = temp->next; // Move to the next node
    }

    return temp->item; // Return the item at the specified index
};

// check if the list is empty
// pre : none
// post: none
// return true if the list is empty; otherwise returns false
bool List::isEmpty() { return (size == 0) ? true : false; };

// check the size of the list
// pre : none
// post: none
// return the number of items in the list
int List::getLength() { return size; };

//------------------- Other useful functions -----------------

// display the items in the list
void List::print() {
    Node* temp = firstNode; // point to first node
    while (temp != nullptr) { // traverse through list
        cout << temp->item << " ";
        temp = temp->next;
    }
    cout << endl;
};

void List::replace(int index, ItemType item) {
    // check if valid index
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of range");
    }

    Node* temp = firstNode; // point to first node
    // loop to traverse to index position
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }

    temp->item = item; // replace the item
};