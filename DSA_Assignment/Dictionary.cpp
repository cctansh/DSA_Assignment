#include "Dictionary.h"
#include <iostream>
using namespace std;

Dictionary::Dictionary()
{
    size = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        items[i] = nullptr;
    }
}

Dictionary::~Dictionary()
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        Node* current = items[i];
        while (current != nullptr)
        {
            Node* toDelete = current;
            current = current->next;

            delete static_cast<int*>(toDelete->item); // Free the memory of the item
            delete toDelete;                         // Free the Node itself
        }
    }
}

// TO EDIT LATER FOR BETTER HASHING
int Dictionary::hash(KeyType key)
{
    return (key * 2654435761 % 2 ^ 32) % MAX_SIZE; // Knuth's Multiplicative Hashing
}

bool Dictionary::add(KeyType newKey, void* newItem)
{
    int index = hash(newKey);
    Node* current = items[index];

    // Check for duplicate key
    while (current != nullptr)
    {
        if (current->key == newKey)
            return false; // Duplicate key found
        current = current->next;
    }

    Node* newNode = new Node{ newKey, newItem, items[index] };
    items[index] = newNode;
    ++size;
    return true;
}

void Dictionary::remove(KeyType key)
{
    int index = hash(key);
    Node* current = items[index];
    Node* prev = nullptr;

    while (current != nullptr)
    {
        if (current->key == key)
        {
            if (prev == nullptr)
            {
                items[index] = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            delete static_cast<int*>(current->item);
            delete current;
            size--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void* Dictionary::get(KeyType key)
{
    int index = hash(key);
    Node* current = items[index];

    while (current != nullptr)
    {
        if (current->key == key)
            return current->item;
        current = current->next;
    }
    return nullptr;
}

// Check if the Dictionary is empty
bool Dictionary::isEmpty()
{
    return size == 0;
}

// Check the size of the Dictionary
int Dictionary::getLength()
{
    return size;
}
void Dictionary::getActorsByAge(int x, int y, SortedLinkedList& list, int currentYear) {
    for (int i = 0; i < MAX_SIZE; ++i) {
        Node* current = items[i];
        while (current != nullptr) {
            Actor* actor = static_cast<Actor*>(current->item);
            int age = currentYear - actor->getBirthYear();
            if (age >= x && age <= y) {
                list.add(actor);                    // add to the sorted list
            }
            current = current->next;
        }
    }
}

void Dictionary::getMoviesWithinYearRange(int yearThreshold, SortedLinkedList& sortedList) {
    for (int i = 0; i < MAX_SIZE; ++i) {
        Node* current = items[i];
        while (current != nullptr) {
            Movie* movie = static_cast<Movie*>(current->item);
            if (movie->getYear() >= yearThreshold) { // movie within past 3 years
                sortedList.add(movie);               // add to the sorted list
            }
            current = current->next;
        }
    }
}
