#pragma once

template <typename T>
class LIFO {

public:
    // Push: Adds an item to the collection
    virtual void push(T item) = 0;

    // Pop: Removes the item most recently added to the collection
    virtual void pop() = 0;

    // Top: Returns the item most recently added to the collection
    virtual T top() const = 0;

    // Empty: Returns true if the collection is empty
    virtual bool empty() const = 0;

    // Size: Returns the number of items in the collection
    virtual int size() const = 0;
};

