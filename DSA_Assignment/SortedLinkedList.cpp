#include "SortedLinkedList.h"

SortedLinkedList::SortedLinkedList(int (*comparator)(void*, void*)) : firstNode(nullptr), size(0), compare(comparator) {}

SortedLinkedList::~SortedLinkedList() {
    while (firstNode) {
        Node* temp = firstNode;
        firstNode = firstNode->next;
        delete temp;                        // Only delete the node, not the item itself
    }
}

bool SortedLinkedList::add(void* item) {
    Node* newNode = new Node{ item, nullptr };

    // Insert at the firstnode if list is empty or new item is smaller
    if (!firstNode || compare(item, firstNode->item) < 0) {
        newNode->next = firstNode;
        firstNode = newNode;
    }
    else {
        // find the correct position
        Node* current = firstNode;
        while (current->next && compare(item, current->next->item) >= 0) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    size++;
    return true;
}

void SortedLinkedList::display(void (*print)(void*)) {
    Node* current = firstNode;
    while (current) {
        print(current->item);
        current = current->next;
    }
}

int SortedLinkedList::getLength() {
    return size;
}
