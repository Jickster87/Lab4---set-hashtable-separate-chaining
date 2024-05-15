#include "SetIterator.h"
#include "Set.h"

SetIterator::SetIterator(const Set& m) : set(m)
{
    // Initialize the iterator
    currentIndex = -1;
    current = nullptr;
    findNextValid(); // Move to the first valid element
}

void SetIterator::first() {
    // Move to the first valid element
    currentIndex = -1;
    findNextValid();
}

void SetIterator::next() {
    // Move to the next valid element
    if (valid()) {
        current = current->next;
        findNextValid();
    }
}

TElem SetIterator::getCurrent() {
    // Return the current element
    if (valid()) {
        return current->key;
    }
    return NULL_TELEM;
}

bool SetIterator::valid() const {
    // Check if the iterator is valid
    return current != nullptr;
}

void SetIterator::findNextValid() {
    // Move to the next valid element in the set
    currentIndex++;
    while (currentIndex < set.initial_capacity) {
        if (set.table[currentIndex] != nullptr) {
            current = set.table[currentIndex];
            return;
        }
        currentIndex++;
    }
    current = nullptr; // Reached the end of the set
}
