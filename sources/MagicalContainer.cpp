#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "MagicalContainer.hpp"

using namespace std;

using namespace ariel;
bool isPrime(int number)  {
    // Function to check whether a number is prime.
    // Returns true if the number is prime, false otherwise.
    if (number < 2)
        return false;
    for (int i = 2; i <= sqrt(number); ++i) {
        if (number % i == 0)
            return false;
    }
    return true;
}
void MagicalContainer::removeElement(int element) {
    // Removes an element from the container.
    int index = -1;
    for (std::vector<int>::size_type i = 0; i < elements.size(); ++i) {
        if (elements[i] == element) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        // If the element exists in the container
        // Erase the element from the container
        elements.erase(elements.begin() + index);
        // Clear the vector of pointers to prime elements
        point_to_elements_prime.clear();
        // Rebuild the vector of pointers to prime elements
        for (std::vector<int>::size_type i = 0; i < elements.size(); ++i) {
            if (isPrime(elements[i])) {
                point_to_elements_prime.push_back(&elements[i]);
            }
        }
    } else {
        // If the element doesn't exist in the container
        throw std::runtime_error("Can't remove element that does not exist");
    }
}
void MagicalContainer::addElement(int element) {
    // Adds an element to the container.
    // Check if the element already exists in the container
    bool exists = false;
    for (std::vector<int>::size_type i = 0; i < elements.size(); ++i) {
        if (elements[i] == element) {
            exists = true;
            break;
        }
    }
    if (!exists) {
        // If the element doesn't already exist in the container
        // Add the element to the container
        elements.push_back(element);
        // Sort the elements in ascending order
        sort(elements.begin(), elements.end());
        // Clear the vector of pointers to prime elements
        point_to_elements_prime.clear();
        // Rebuild the vector of pointers to prime elements
        for (std::vector<int>::size_type i = 0; i < elements.size(); ++i) {
            if (isPrime(elements[i])) {
                point_to_elements_prime.push_back(&elements[i]);
            }
        }
    }
}
int MagicalContainer::size() const {
    // Returns the number of elements in the container.
    return elements.size();
}

bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator& other) const {
    // Check if two AscendingIterator objects are equal.
    return &cont == &other.cont && index == other.index;
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const {
    // Check if two AscendingIterator objects are not equal.
    return !(*this == other);
}

bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other) const {
    // Check if this AscendingIterator is greater than another AscendingIterator.
    return index > other.index;
}

bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other) const {
    // Check if this AscendingIterator is less than another AscendingIterator.
    return index < other.index;
}

int MagicalContainer::AscendingIterator::operator*() const {
    // Dereference the AscendingIterator to get the value it points to.
    return cont.elements[(vector<int>::size_type)index];
}

bool MagicalContainer::AscendingIterator::operator>=(const AscendingIterator& other) const {
    // Check if this AscendingIterator is greater than or equal to another AscendingIterator.
    return (*this > other) || (*this == other);
}

bool MagicalContainer::AscendingIterator::operator<=(const AscendingIterator& other) const {
    // Check if this AscendingIterator is less than or equal to another AscendingIterator.
    return (*this < other) || (*this == other);
}

MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(AscendingIterator const &other) {
    // Assignment operator for AscendingIterator.
    // Check if the containers of the iterators are the same.
    // If not, throw a runtime error.
    if(&this->cont != &other.cont)
        throw runtime_error("Can't assign iterators from different containers");
    if (this != &other) {
        cont = other.cont;
        index = other.index;
    }
    return *this;
}

MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() {
    // Pre-increment operator for AscendingIterator.
    // Move the iterator to the next element.
    // If the iterator reaches the end, throw a runtime error.
    if(index==this->cont.size())
        throw runtime_error("Iterator reached the end");
    ++index;
    return *this;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
    // Get an iterator pointing to the first element in the container.
    return AscendingIterator(cont);
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
    // Get an iterator pointing to the end of the container.
    AscendingIterator iterator(cont);
    iterator.index = cont.elements.size();
    return iterator;
}

bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator& other) const {
    // Check if two SideCrossIterator objects are equal.
    return &cont == &other.cont && index == other.index;
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const {
    // Check if two SideCrossIterator objects are not equal.
    return !(*this == other);
}

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const {
    // Check if this SideCrossIterator is greater than another SideCrossIterator.
    return index > other.index;
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const {
    // Check if this SideCrossIterator is less than another SideCrossIterator.
    return index < other.index;
}

int MagicalContainer::SideCrossIterator::operator*() const {
    // Dereference the SideCrossIterator to get the value it points to.
    return cont.elements[(vector<int>::size_type)index];
}

bool MagicalContainer::SideCrossIterator::operator>=(const SideCrossIterator& other) const {
    // Check if this SideCrossIterator is greater than or equal to another SideCrossIterator.
    return (*this > other) || (*this == other);
}

bool MagicalContainer::SideCrossIterator::operator<=(const SideCrossIterator& other) const {
    // Check if this SideCrossIterator is less than or equal to another SideCrossIterator.
    return (*this < other) || (*this == other);
}

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(SideCrossIterator const &other) {
    // Assignment operator for SideCrossIterator.
    // Check if the containers of the iterators are the same.
    // If not, throw a runtime error.
    if(&this->cont != &other.cont)
        throw runtime_error("Can't assign iterators from different containers");
    if (this != &other) {
        cont = other.cont;
        index = other.index;
    }
    return *this;
}

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() {
    // Pre-increment operator for SideCrossIterator.
    // Move the iterator to the next element.
    // If the iterator reaches the end, throw a runtime error.
    if(*this == this->end())
        throw runtime_error("Iterator reached the end");
    if (start_index == end_index)
        index = this->cont.size();
    else if (this->index < this->cont.size()/2) {
        index = end_index;
        end_index--;
    } else {
        start_index++;
        index = start_index;
    }
    return *this;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
    // Get an iterator pointing to the first element in the container.
    return SideCrossIterator(cont);
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
    // Get an iterator pointing to the end of the container.
    SideCrossIterator iterator(cont);
    iterator.index = cont.elements.size();
    return iterator;
}

bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator& other) const {
    // Check if two PrimeIterator objects are equal.
    return &cont == &other.cont && index == other.index;
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& other) const {
    // Check if two PrimeIterator objects are not equal.
    return !(*this == other);
}

bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& other) const {
    // Check if this PrimeIterator is greater than another PrimeIterator.
    return index > other.index;
}

bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& other) const {
    // Check if this PrimeIterator is less than another PrimeIterator.
    return index < other.index;
}

int MagicalContainer::PrimeIterator::operator*() const {
    // Dereference the PrimeIterator to get the value it points to.
    return *(this->cont.point_to_elements_prime[(vector<int>::size_type)index]);
}

bool MagicalContainer::PrimeIterator::operator>=(const PrimeIterator& other) const {
    // Check if this PrimeIterator is greater than or equal to another PrimeIterator.
    return (*this > other) || (*this == other);
}

bool MagicalContainer::PrimeIterator::operator<=(const PrimeIterator& other) const {
    // Check if this PrimeIterator is less than or equal to another PrimeIterator.
    return (*this < other) || (*this == other);
}

MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(PrimeIterator const &other) {
    // Assignment operator for PrimeIterator.
    // Check if the containers of the iterators are the same.
    // If not, throw a runtime error.
    if(&this->cont != &other.cont)
        throw runtime_error("Can't assign iterators from different containers");
    if (this != &other) {
        cont = other.cont;
        index = other.index;
    }
    return *this;
}

MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() {
    // Pre-increment operator for PrimeIterator.
    // Move the iterator to the next element.
    // If the iterator reaches the end, throw a runtime error.
    if(*this == this->end())
        throw runtime_error("Iterator reached the end");
    this->index++;
    return  *this;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
    // Get an iterator pointing to the first prime element in the container.
    return PrimeIterator(cont);
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
    // Get an iterator pointing to the end of the prime elements in the container.
    PrimeIterator iterator(cont);
    iterator.index = cont.point_to_elements_prime.size();
    return iterator;
}
