#pragma once

#include <iostream>
using namespace std;

template <typename T>
class List {
public:

  virtual bool add(T item) = 0;
  virtual bool clear() = 0;
  virtual bool contains(T item) = 0;
  virtual T* get(int index) = 0;
  virtual bool remove(T item) = 0;
  virtual bool removeAll(T item) = 0;
  virtual int size() = 0;
  virtual void reverse() = 0;

  // Prints the contents of the list in the following way:
  // "{ item1 item2 item3 item4 item5 }"
  friend ostream& operator<< (ostream& out, List& ll) {
    out << "{ ";
    for(int i=0; i < ll.size(); i++)
      out << *(ll.get(i)) << " ";
    out << "}";
    return out;
  }

  // Return true if "this" list has exactly the same contents
  // as the otherList, "rhs" (including ordering).
  friend bool operator== (List& lhs, List& rhs) {
    if (lhs.size() != rhs.size())
      return false;

    for(int i=0; i < lhs.size(); i++) {
      if ( *(lhs.get(i)) != *(rhs.get(i)) )
        return false;
    }

    return true;
  }
};

