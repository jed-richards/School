#include <iostream>
#include "DoublyLinkedList.h"
using namespace std;

int main() {
  cout << "Hello DoublyLinkedList" << endl;
  
  /*
  DoublyLinkedList<int> dll;

  dll.add(1);
  dll.add(22);

  dll.print();

  cout << dll.clear() << endl;
  
  dll.print();

  cout << dll.clear() << endl;

  dll.print();

  dll.add(1);
  dll.add(1);
  dll.add(1);
  dll.print();
  cout << "contains(1):   " << dll.contains(1) << endl;   // 1 for true 0 for false
  cout << "contains(5):   " << dll.contains(5) << endl;   // 1 for true 0 for false
  */

  // DoublyLinkedList<int> intList;
  
  /*
  // add
  intList.add(1);
  intList.add(2);
  intList.add(3);
  
  // print
  cout << intList << endl;
  intList.print();

  cout << endl;

  // reverse 
  cout << "reverse()" << endl;
  cout << intList << endl;
  intList.reverse();
  cout << intList << endl;

  cout << endl;

  // size()
  cout << "size()" << endl;
  cout << intList.size() << endl;
  intList.clear();
  cout << "size() after clear" << endl;
  cout << intList.size() << endl;  // returns 0 because the list is empty

  cout << endl;

  // get() and reverse()
  intList.add(1);
  intList.add(2);
  intList.add(3);
  intList.add(4);
  intList.add(5);
  intList.add(6);
  intList.add(7);
  intList.add(8);
  cout << "before reverse()" << endl;
  intList.print();
  intList.reverse();
  cout << "after reverse()" << endl;
  intList.print();

  cout << endl;
  
  cout << "get(5)" << endl;       
  int* intPtr1 = intList.get(5);   // returns a pointer to the data at index 5 which is currently 3
  cout << intPtr1 << endl;    // prints address of pointer
  cout << *intPtr1 << endl;   // dereferences pointer prints out 3

  cout << endl;

  cout << "get(-1)" << endl;       
  int* intPtr2 = intList.get(-1);   // returns nullptr because negative index
  cout << intPtr2 << endl;    // prints 0 because nullptr was returned 
  // cout << *intPtr2 << endl;   // cant dereference nullptr

  cout << endl;

  cout << "get(10)" << endl;       
  int* intPtr3 = intList.get(10);   // returns nullptr because index out of bounds
  cout << intPtr3 << endl;    // prints 0 because nullptr was returned 
  // cout << *intPtr3 << endl;   // cant dereference nullptr
  */

  /*
  for (int i=0; i<5; i++) {
    intList.add(i);
  }

  intList.print();

  cout << endl;

  cout << "remove(10) which isnt in the list" << endl;
  cout << intList.remove(10) << endl;
  intList.print();

  cout << endl;

  cout << "remove(0) the first item" << endl;
  cout << intList.remove(0) << endl;
  intList.print();

  cout << endl;

  cout << "remove(4) the last item" << endl;
  cout << intList.remove(4) << endl;
  intList.print();

  cout << endl;

  cout << "remove(2) the middle item" << endl;
  cout << intList.remove(2) << endl;
  intList.print();

  cout << endl;

  cout << "clear()" << endl;
  intList.clear();
  intList.print();

  cout << endl;
  */

  /*
  for (int i=0; i<5; i++) {
    intList.add(i);
  }

  intList.print();
  intList.reverse();
  intList.print();
  */

  /*
  for (int i=0; i<5; i++) {
    intList.add(22);
  }
  intList.print();
  cout << "removeAll(22)" << endl;
  intList.removeAll(22);
  intList.print();

  cout << endl;

  intList.add(2);
  intList.add(2);
  intList.add(3);
  intList.add(2);
  intList.add(4);

  intList.print();
  cout << "removeAll(2)" << endl;
  intList.removeAll(2);
  intList.print();

  cout << endl;

  intList.print();
  cout << "removeAll(4)" << endl;
  intList.removeAll(4);
  intList.print();

  cout << endl;
  */

  // Here I will test the functions one at a time
  
  // Constructor
  DoublyLinkedList<string> strList;

  // add()
  cout << "add(\"Jed\")" << endl;
  cout << strList.add("Jed") << endl;  // Shows 1 for true 

  cout << endl;

  // print()
  cout << "print after add" << endl;   
  strList.print();          // my function
  cout << strList << endl;  // provided function 

  cout << endl;

  // clear()
  cout << "after clear()" << endl;
  cout << strList.clear() << endl;    // clears list and displays 1 for true (it did clear stuff)
  strList.print();
  cout << strList.clear() << endl;    // trys to clear an empty list so displays 0 for false

  cout << endl;

  // Contains()
  cout << "contains()" << endl;
  cout << strList.contains("Jed") << endl;  // displays 0 for false, the list is empty
  strList.add("Jed");
  cout << strList.contains("Jed") << endl;  // displays 1 for true, the list contains 'Jed'
  cout << strList.contains("Marshmallow") << endl;  // displays 0 for false, the list does not contain 'Marshmallow'

  cout << endl;
  
  // get()  return a pointer to data at nth element
  cout << "get()" << endl;
  string* strPtr1 = strList.get(0);
  cout << strPtr1 << endl;   // prints the address of the data
  cout << *strPtr1 << endl;  // dereferences and prints the data the pointer is pointing to 

  string* strPtr2 = strList.get(10);
  cout << strPtr2 << endl;      // prints 0 (zero) because the pointer returned is nullptr
  // cout << *strPtr2 << endl;  // cant dereference a nullptr, so the program is terminated
  
  string* strPtr3 = strList.get(-5);
  cout << strPtr3 << endl;      // prints 0 (zero) because the pointer returned is nullptr
  // cout << *strPtr3 << endl;  // cant dereference a nullptr, so the program is terminated

  cout << endl;

  // remove()
  strList.print();
  cout << "remove(\"Marshmallow\")" << endl;
  cout << strList.remove("Marshmallow") << endl;  // outputs 0 becuase 'Marshmallow' is not found in the list
  strList.print();
  cout << "remove(\"Jed\")" << endl;
  cout << strList.remove("Jed") << endl;  // outputs 1 because 'Jed' is found in the list and deleted (removed)
  strList.print();
  cout << "remove(\"Jed\")" << endl;
  cout << strList.remove("Jed") << endl;  // outputs 1 because 'Jed' is found in the list and deleted (removed)
  strList.print();

  cout << endl;

  // still need to show removeAll(), size(), and reverse()  
  cout << "removeAll(\"Jed\")" << endl;
  strList.add("Jed");
  strList.add("Jed");
  strList.add("Cookie");
  strList.add("Jed");
  strList.print();
  cout << strList.removeAll("Jed") << endl;
  strList.print();
  cout << strList.removeAll("Jed") << endl;
  strList.print();

  cout << endl;

  // size() 
  cout << "size()" << endl;
  strList.clear();
  cout << strList.size() << endl;
  strList.print();
  strList.add("Cookies");
  cout << strList.size() << endl;
  strList.print();
  strList.add("Ate");
  cout << strList.size() << endl;
  strList.print();
  strList.add("Jed");
  cout << strList.size() << endl;
  strList.print();

  cout << endl;

  // reverse()
  cout << "reverse()" << endl;
  strList.print();
  strList.reverse();
  strList.print();

  cout << endl;

  // reverse() again
  cout << "reverse() again" << endl;
  DoublyLinkedList<int> intList;
  intList.add(5);
  intList.add(4);
  intList.add(3);
  intList.add(2);
  intList.add(1);
  intList.print();
  intList.reverse();
  intList.print();

  cout << endl;

  // reverse() again pt2
  cout << "reverse() again pt2" << endl; 
  DoublyLinkedList<int> intList2;
  intList2.reverse();
  
  cout << endl;

  // reverse() again pt3
  cout << "reverse() again pt3" << endl; 
  DoublyLinkedList<int> intList3;
  intList3.add(22);
  intList3.reverse();
  intList3.print();

  cout << endl;
  
  cout << "removeAll() after adding a couple of the same item" << endl;
  intList.clear();
  for (int i=0; i<5; i++) {
    intList.add(232);
  }
  intList.print();
  intList.removeAll(232);
  intList.print();


  return 0;
}
