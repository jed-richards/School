#pragma once

#include "FIFO.h"
#include <cassert>

template <typename T>
class Queue : public FIFO<T> {

  private:
    // private member variables 
    int arrSize;
    int arrCapacity;
    T* data;
    int first;  // keeps track of the first position
    int last;   // keeps track of the last position 
    
  public:
    // constructor
    Queue() {
      arrSize = 0;
      arrCapacity = 8;
      data = new T[arrCapacity];
      first = 0;
      last = 0;
    }

    // Push: Adds an item to the collection
    void push(T item) {
      // inside of grow function, it reorders the data to be from front to back and sets back to the next available spot
      if (arrSize == arrCapacity) {
        grow();
      }
      // if last is equal to the end and size != capacity then set last to 0 because it means the first was moved up by pop
      if (last == arrCapacity) {
        last = 0;
      }
      // finally put the item at last position and increment back (back is the next available position) increment size
      data[last] = item;
      last++;
      arrSize++;
    }

    // Pop: Removes the item that has been in the collection the longest
    void pop() {
      assert(arrSize > 0 && "Can't pop() on an empty queue"); /*the queue is empty*/
      first++;
      arrSize--;
      if (first == arrCapacity) {
        first = 0;
      }
    }

    // Front: Returns the item that has been in the collection the longest
    T front() const {
      // if empty it should crash
      assert (arrSize > 0 &&  "Can't use front() on an empty queue"); /*the queue is empty*/
      return data[first];
    }

    // Empty: Returns true if the collection is empty
    bool empty() const {
      if (arrSize > 0) 
        return false;
      else 
        return true;
    }

    // Size: Returns the number of items in the collection
    int size() const {
      return arrSize;
    }

    // destructor
    ~Queue() {
      if (data != nullptr) {
        delete[] data;
      }
    }

    // my print function
    void print() {
      std::cout << "[ ";
      if (arrSize == 0) {
        std::cout << "empty ";
      }
      else if (first >= last) {
        for (int i=first; i<arrCapacity; i++) {
          std::cout << data[i] << " ";
        }
        for (int i=0; i < last; i++) {
          std::cout << data[i] << " ";
        }
      } 
      else {
        for (int i=first; i<last; i++) {
          std::cout << data[i] << " ";
        }
      }
      std::cout << "]";
      std::cout << std::endl;
    }

    // my own function to help with positioning
    int lastPos() {
      return last;
    }

    int firstPos() {
      return first;
    }

    int capacity() {
      return arrCapacity;
    }

    void clear() {
      while (!empty()) {
        pop();
      }
    }


  private:
    void grow() {
      arrCapacity = 2*arrCapacity;
      // allocate space for a larger array
      T* biggerData = new T[arrCapacity];  
      // copy over items
      if (first >= last) {
        for (int i=first,j=0; i<arrSize; i++,j++) {
          biggerData[j] = data[i];
        }
        for (int i=0, j = arrSize-last; i < first; i++,j++) {
          biggerData[j] = data[i];
        }
      } 
      else {
        for (int i=0; i<arrSize; i++) {
          biggerData[i] = data[i];
        }
      }
      // set first to 0 and last to the next available spot which would be arrSize 
      // finally delete data (free up space) and make data point the biggerData
      first = 0;
      last = arrSize;
      delete[] data;
      data = biggerData;
    }

};

