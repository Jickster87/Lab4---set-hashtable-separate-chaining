#include "SetIterator.h"
#include "Set.h"
#include <stdexcept> // For std::exception

SetIterator::SetIterator(const Set& m) : set(m)
{
    first();
}

void SetIterator::first() {
    // Move to the first valid element
    currentIndex = 0;
    current = nullptr;
    while (currentIndex < set.capacity && set.hashTable[currentIndex] == nullptr) {
        currentIndex++;
    }
    if (currentIndex < set.capacity) {
        current = set.hashTable[currentIndex];
    }

}

void SetIterator::next() {
    // Move to the next valid element
    if (!valid()) {
        throw std::exception(); // Invalid state
    }
    current = current->next;
    if (current == nullptr) {
        currentIndex++;
        while (currentIndex < set.capacity && set.hashTable[currentIndex] == nullptr) {
            currentIndex++;
        }
        if (currentIndex < set.capacity) {
            current = set.hashTable[currentIndex];
        }
    }
}

TElem SetIterator::getCurrent() {
    if (!valid()) {
        throw std::exception();
    }
    return current->key;
}

bool SetIterator::valid() const {
    // Check if the iterator is valid
    return current != nullptr;
}
