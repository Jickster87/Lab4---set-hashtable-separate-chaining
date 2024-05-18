#include "Set.h"
#include "SetITerator.h"
#include <stdlib.h>     /* abs */

Set::Set() {
	//SET - hashTable with separate chaining (doubly linked list)

	capacity = 16;
	hashTable = new Node* [capacity];
	for (int i = 0; i < capacity; i++)
	{
		hashTable[i] = nullptr; 
	}
	count = 0;
}


int Set::hash(int key) const {
    return abs(key) % capacity;  // *cheat gpt - LAST FIX!! why?? - Use abs to handle negative keys if necessary
}


bool Set::add(TElem elem) {
    int index = hash(elem);

    if (search(elem)) {
        return false;  // Element already exists
    }

    Node* newNode = new Node(elem);

    newNode->next = hashTable[index]; 
	newNode->prev = nullptr;

    if (hashTable[index] != nullptr) { 
        hashTable[index]->prev = newNode;
    }

	hashTable[index] = newNode;

    count++;
    return true;
}


bool Set::remove(TElem elem) {
    int index = hash(elem);
    Node* current = hashTable[index];

    while (current != nullptr && current->key != elem) {
        current = current->next;
    }

    if (current == nullptr) {
        return false;  // Element not found
    }

    if (current->prev != nullptr) {
        current->prev->next = current->next;
    }
    else {
        hashTable[index] = current->next;  // Removing head node
    }

    if (current->next != nullptr) {
        current->next->prev = current->prev;
    }

    delete current;
    count--;
    return true;
}


bool Set::search(TElem elem) const {
	int searchPos = hash(elem);  // Calculate the hash position of the element
	Node* currentNode = hashTable[searchPos];  // Get the head of the linked list at the hash position

	while (currentNode != nullptr && currentNode->key != elem) {
		currentNode = currentNode->next;  // Move to the next node in the linked list
	}
    if (currentNode != nullptr)
    {
        return true;
    }
	return false;  // Element not found
}


int Set::size() const {
	return count;
}


bool Set::isEmpty() const {
	return count == 0;
}


Set::~Set() {
	for (int i = 0; i < capacity; i++)
	{
		Node* current = hashTable[i];
		while (current != nullptr)
		{
			Node* temp = current;
			current = current->next;
			delete temp;
		}
	}
	delete[] hashTable;
}


SetIterator Set::iterator() const {
	return SetIterator(*this);
}