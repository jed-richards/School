#pragma once

#include <iostream>  // for my print function
#include "List.h"

template <typename T>
class LinkedList : public List<T> {
  private:
    class Node {
      public:
        T data;
        Node* next;

        Node(T d, Node* n) {
          data = d;
          next = n;
        }
    };

    // Add your own private member variables/methods here

    Node* head;   // make head pointer in private


  public:
    // Implement the List interface here

    // Constructor
    LinkedList() {
      head = nullptr;
    }


    // "add" must add the data to the end of the list.
    // Return true if the list has been modified (hint: always)
    bool add(T item) {
      // if empty add a node pointing at nullptr and make head point to the new node
      if (head == nullptr) {
        Node* newData = new Node(item, nullptr);
        head = newData;
        return true;
      }
      // else cycle through and add to the end
      else {
        Node* curr = head;
        while (curr->next != nullptr) {
          curr = curr->next;
        }
        Node* newData = new Node(item, nullptr);
        curr->next = newData;
        return true;
      }
    }


    // "clear" must erase the contents of the list and return true
    // if the list has been modified (hint: it wont if it's already empty!)
    bool clear() {
      // if empty cant clear an empty list
      if (head == nullptr) {
        return false;
      }
      // else cycle through deleting nodes until head == nullptr
      else {
        Node* curr = head;
        while (head != nullptr) {
          head = head->next;
          delete curr;
          curr = head;
        }
        return true;
      }
    }


    // "contains" must return true if the list contains the item
    bool contains(T item) {
      // cycle through looking for data
      Node* curr = head;
      while (curr != nullptr) {
        if (curr->data == item) {
          return true;
        }
        else {
          curr = curr->next;
        }
      }
      return false;  
    }


    // "get" must return a pointer to the i'th element in the list
    // Return nullptr if such an element doesn't exist
    T* get(int index) {
      // if negative index or list is empty return nullptr
      if (index < 0 || head == nullptr) {
        cout << "nullptr (negative index or empty list)" << endl;
        return nullptr;
      }
      // else if index is >= size then index is out of bounds
      else if (index >= size()) {
        cout << "nullptr (index out of bounds)" << endl;
        cout << "can only retrieve up to index: " << (size()-1) << endl;
        return nullptr;
      }
      // else cycle through until position gets to index and return a pointer to the data at that node
      else {
        Node* curr = head;
        int position = 0;
        while (curr != nullptr && position < index) {
          position++;
          curr = curr->next;
        }
        return &(curr->data);
      }
    }



    // "remove" must remove the first occurrence of the item from the list
    // Return true if the array was modified
    bool remove(T item) {
      // if empty return false
      if (head == nullptr) {
        return false;
      }
      // else cycle through looking for first instance of item 
      else {
        Node* curr = head;
        if (curr->data == item) {
          head = head->next;
          delete curr;
          return true;
        }
        else {
          while (curr->next != nullptr) {
            if (curr->next->data == item) {
              Node* temp = curr->next;
              curr->next = temp->next;
              delete temp;
              return true;
            }
            else {
              curr = curr->next;
            }
          }
          return false;
        }
      }
    }


    // "removeAll" must remove all occurrences of the item from the list
    // Return true if the array was modified
    bool removeAll(T item) {
      // if empty cant remove
      if (head == nullptr) {
        return false;
      }
      // else cycle through looking for all instances of item and keeping track of a delCount variable 
      else {
        int delCount = 0;
        Node* temp = head;
        while (head->data == item) {
          head = head->next;
          delete temp;
          delCount++;
          temp = head;
          if (head == nullptr) {
            return true;
          }
        }
        while (temp->next != nullptr) {
          if (temp->next->data == item) {
            Node* delNode = temp->next;
            temp->next = delNode->next;
            delCount++;
            delete delNode;
          }
          else {
            temp = temp->next;
          }
        }
        if (delCount > 0) {
          return true;
        }
        else {
          return false;
        }
      }
    }


    // "size" must return the current size of the list
    int size() {
      // cycle through keeping track of a size variable and returning size
      Node* curr = head;
      int size = 0;
      while (curr != nullptr) {
        size++;
        curr = curr->next;
      }
      return size;
    }


    // "reverse" must reverse the order of the items in the list
    void reverse() {
      // if empty cant reverse
      if (head == nullptr) {
        cout << "cant reverse an empty" << endl;
      }
      // else cycle through moving head forward one and appending onto revHead (no need to call new)
      else {
        Node* curr = head;
        Node* revHead = nullptr;
        while (head != nullptr) {
          curr = head;
          head = head->next;
          curr->next = revHead;
          revHead = curr;
        }
        // finally set head = revHead when head == nullptr 
        head = revHead;
      }
    }


    // my personal print() function
    void print() {
      cout << "{ ";
      Node* curr = head;
      while (curr != nullptr) {
        cout << curr->data << " ";
        curr = curr->next;
      }
      cout << "}" << endl;;
    }

    // Destructor (if head is not pointing to nullptr then call the member function clear()) 
    ~LinkedList() {
      if (head != nullptr) {
        clear();
      }
    }

};

