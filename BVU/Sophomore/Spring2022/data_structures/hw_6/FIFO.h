#pragma once

template <typename T>
class FIFO {
public:
    // Push: Adds an item to the collection
    virtual void push(T item) = 0;

    // Pop: Removes the item that has been in the collection the longest
    virtual void pop() = 0;

    // Front: Returns the item that has been in the collection the longest
    virtual T front() const = 0;

    // Empty: Returns true if the collection is empty
    virtual bool empty() const = 0;

    // Size: Returns the number of items in the collection
    virtual int size() const = 0;
};

