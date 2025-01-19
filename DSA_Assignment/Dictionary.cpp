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
            delete toDelete;
        }
    }
}

// TO EDIT LATER FOR BETTER HASHING
int Dictionary::hash(KeyType key)
{
    return key % MAX_SIZE;
}

bool Dictionary::add(KeyType newKey, void* newItem)
{
    int index = hash(newKey);
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