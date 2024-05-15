#include "Set.h"
#include "SetITerator.h"

Set::Set() {
	//SET - hashtable with separate chaining (doubly linked list)

	initial_capacity = 16;
	table = new Node* [initial_capacity];
	for (int i = 0; i < initial_capacity; i++)
	{
		table[i] = nullptr; 
	}
	count = 0;
}


int Set::hash(int key) const {
    return key % initial_capacity;
}


bool Set::add(TElem elem) {
    int index = hash(elem);  // Calculate the index for element

    if (search(elem)) {
        return false;  // Element already exists
    }

    Node* newNode = new Node(elem);  // newNode = Node(5)

    newNode->next = table[index];  // newNode.next = table[x]
    if (table[index] != nullptr) {  //
        table[index]->prev = newNode;
    }

    count++;
    // Element added successfully
    return true;
}

bool Set::remove(TElem elem) {
    int index = hash(elem);  // Calculate the index for the element

    // Search for the element in the linked list at the calculated index
    Node* currentNode = table[index];
    while (currentNode != nullptr) {
        if (currentNode->key == elem) {
            // Remove the node containing the element
            if (currentNode->prev != nullptr) {
                currentNode->prev->next = currentNode->next;
            }
            else {
                table[index] = currentNode->next;
            }
            if (currentNode->next != nullptr) {
                currentNode->next->prev = currentNode->prev;
            }

            delete currentNode;
            count--;
            return true; 
        }
        currentNode = currentNode->next;  // Move to the next node
    }

    return false;  // Element not found, so cannot be removed
}


bool Set::search(TElem elem) const {
	int searchPos = hash(elem);  // Calculate the hash position of the element
	Node* currentNode = table[searchPos];  // Get the head of the linked list at the hash position

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
	for (int i = 0; i < initial_capacity; i++)
	{
		Node* current = table[i];
		while (current != nullptr)
		{
			Node* temp = current;
			current = current->next;
			delete temp;
		}
	}
	delete[] table;
}


SetIterator Set::iterator() const {
	return SetIterator(*this);
}