#pragma once

#include <iostream>   // for my print function
#include "LIFO.h"


template <typename T>
class Stack : public LIFO<T> {

  private:

    // Create my own node class
    class Node {
      public:
        T data;
        Node* next;

        Node(T d, Node* n) {
          data = d;
          next = n;
        }
    };

    // Private member varibles of Stack
    Node* topPtr;   // same as head pointer
    int itemCount;    // keep track of size

  public:
      // Stack Contructor
      Stack() {
        topPtr = nullptr;
        itemCount = 0;
      }
      
      // Push: Adds an item to the collection
      void push(T item) {
        // When creating the new node, it stores data (item) and points to next
        // (whatever top is pointing at even if top is pointing to nullptr)
        // Then set top to point at the the new node and increment size.
        Node* newData = new Node(item, topPtr); 
        topPtr = newData;
        itemCount++;
      }

      // Pop: Removes the item most recently added to the collection
      void pop() {
        // Crashes if trying to pop on an empty stack. Thats a no-no.
        Node* temp = topPtr;
        topPtr = topPtr->next;
        delete temp;
        itemCount--;
      }

      // Top: Returns the item most recently added to the collection
      T top() const {
        // Crashes if empty
        return topPtr->data;
      }

      // Empty: Returns true if the collection is empty
      bool empty() const {
        if (topPtr == nullptr)
          return true;
        else
          return false;
      }

      // Size: Returns the number of items in the collection
      int size() const {
        return itemCount;
      }

      // My personal print if not empty it will print from top to bottom else if it is empty 
      // print empty
      void print() {
        if (!empty()) {
          std::cout << "top { ";
          Node* curr = topPtr;
          while (curr != nullptr) {
            std::cout << curr->data << " ";
            curr = curr->next;
          }
          std::cout << "} bottom" << std::endl;;
        }
        else {
          std::cout << "stack is empty" << std::endl;
        }
      }

      // Destructor
      ~Stack() {
        clear();
      }


  private:
    // private method that is used in the destructor to delete all items (no memory leak)
    void clear() {
      while (!empty()) {
        pop();
      }
    }
};
