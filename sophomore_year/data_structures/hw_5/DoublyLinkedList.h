#pragma once

#include "List.h"

template <typename T>
class DoublyLinkedList : public List<T> {
  private:
    class Node {
      public:
        T data;
        Node* next;
        Node* prev;

        Node(T d, Node* n, Node* p) {
          data = d;
          next = n;
          prev = p;
        }
    };

    // Add your own private member variables/methods here
    Node* head;  // represents the head pointer
    Node* tail;  // represents the tail pointer

  public:
    // Implement the List interface here


    // Counstructor settng both head and tail to nullptr (empty list)
    DoublyLinkedList() {
      head = nullptr;
      tail = nullptr;
    }


    // "add" must add the data to the end of the list.
    // Return true if the list has been modified (hint: always)
    bool add(T item) {
      // if list empty add and set head and tail to point to the new node
      if (head == nullptr && tail == nullptr) {
        Node* newData = new Node(item, nullptr, nullptr);
        head = newData;
        tail = newData;
      }
      // else add a node at the end with next=nullptr and prev=tail and then set tail->next and tail to point at the new data
      else {
        Node* newData = new Node(item, nullptr, tail);
        tail->next = newData;
        tail = newData;
      }
      return true;
    }


    // "clear" must erase the contents of the list and return true
    // if the list has been modified (hint: it wont if it's already empty!)
    bool clear() {
      // if empty return false
      if (head == nullptr && tail == nullptr) {
        return false; 
      }
      else {
        // else cycle through deleting nodes  until head == nullptr
        Node* temp;
        while (head != nullptr) {
          if (head == tail) {
            temp = head;
            head = head->next;  // points to nullptr
            tail = tail->prev;  // points to nullptr
            delete temp;  
          }
          else {
            temp = head;
            head = head->next;
            head->prev = nullptr;
            delete temp;
          }
        }
        return true;
      }
    }


  // "contains" must return true if the list contains the item
  bool contains(T item) {
    // cycle through checking curr->data
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

    //if index is negative or list is empty return nullptr
    if (index < 0 || head == nullptr) {
      cout << "nullptr (negative index or empty list)" << endl;
      return nullptr;
    }
    //else if the index is >= the size of the list then the index wanted is out of bounds
    else if (index >= size()) {
      cout << "nullptr (index out of bounds)" << endl;
      cout << "can only retrieve up to: " << (size()-1) << endl;
      return nullptr;
    }
    //else cycle through until position hits index and return the address of the data of that node
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
    // if empty can't remove
    if (head == nullptr && tail == nullptr) {
      return false;
    }
    // else cycle through list looking for item and delete first instance if item is in list 
    else { 
      Node* temp = head;
      // checks first data point
      if (head->data == item) {
        head = head->next;
        if (head == nullptr) {
          tail = nullptr;
        }
        else {
          head->prev = nullptr;
        }
        delete temp;
        return true;
      }
      else {
        while (temp->next != nullptr) {
          if (temp->next->data == item) {
            Node* delNode = temp->next;
            temp->next = delNode->next;
            if (temp->next == nullptr) {
              tail = temp;
            }
            else {
              temp->next->prev = temp;
            }
            delete delNode;
            return true;
          }
          else {
            temp = temp->next;
          }
        }
        return false;   // if item is not found return false
      }
    }
  }


  // "removeAll" must remove all occurrences of the item from the list
  // Return true if the array was modified
  bool removeAll(T item) {
    // if list is empty return false
    if (head == nullptr) {
      return false;
    }
    // else keep track of a delCount variable (# of nodes deleted) and cycle through looking for item
    // if item is found delete the node make the pointer changes and add 1 to delCount
    else {
      int delCount = 0;
      Node* temp = head;
      while (head->data == item) {
        head = head->next;
        if (head == nullptr) {
          tail = nullptr;
          delete temp;
          return true;
        }
        else {
          head->prev = nullptr;
          delete temp;
          delCount++;
          temp = head;
        }
      }
      while (temp->next != nullptr) {
        if (temp->next->data == item) {
          Node* delNode = temp->next;
          temp->next = delNode->next;
          if (temp->next == nullptr) {
            tail = temp;
          }
          else {
            temp->next->prev = temp;
          }
          delCount++;
          delete delNode;
        }
        else {
          temp = temp->next;
        }
      }
      // finally check if delCount is greater than 0
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
    // cycle through keeping track of a size variable and then return size
    // if empty it returns 0
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
    // if empty cant reverse and empty list
    if (head == nullptr && tail == nullptr) {
      cout << "cant reverse an empty list" << endl;
    }
    // else make 2 temp pointers equal to head then switch head and tail and then cycle through changing the direction of the pointers
    else {
      Node* temp1 = head;
      Node* temp2 = head;
      head = tail;
      tail = temp1;
      while (temp1 != nullptr) {
        temp2 = temp2->next;
        temp1->next = temp1->prev;
        temp1->prev = temp2;
        temp1 = temp2;
      }
    }
  }

  // personal print() function
  void print() {
    cout << "{ ";
    Node* curr = head;
    while (curr != nullptr) {
      cout << curr->data << " ";
      curr = curr->next;
    }
    cout << "}" << endl;;
  }
  
  // deconstructor
  ~DoublyLinkedList() {
    clear();
  }

};

