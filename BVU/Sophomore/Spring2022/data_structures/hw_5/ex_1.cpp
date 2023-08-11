#include <iostream>
#include "LinkedList.h"
using namespace std;

int main() {

  cout << "Hello LinkedList" << endl;
  cout << endl;

/*
  LinkedList<int> ll;

  ll.add(2);
  ll.print();

  cout << "------------------------" << endl;

  ll.add(6);
  ll.print();

  cout << "------------------------" << endl;

  cout << ll.add(22) << " Add: 0 for false or 1 for true" << endl;  // this outputs a 1 because its true (meaning it added something)

  cout << "------------------------" << endl;

  ll.print();

  cout << "------------------------" << endl;

  cout << ll.clear() << " Clear: 0 for false or 1 for true" << endl;  // outputs a 1 because its true (meaning it was cleared)
  ll.print();   // this prints nothing because ll is empty

  cout << "------------------------" << endl;

  cout << ll.clear() << " Clear: 0 for false or 1 for true" << endl;  // outputs a 1 because its true (meaning it was cleared)
  ll.print();   // this prints nothing because ll is empty

  cout << "------------------------" << endl;

  cout << ll.contains(4) << " Contains: 0 for false or 1 for true" << endl; 

  cout << "------------------------" << endl;

  ll.add(2);
  ll.print();

  cout << "------------------------" << endl;

  cout << ll.contains(4) << " Contains: 0 for false or 1 for true" << endl; 

  cout << "------------------------" << endl;

  cout << ll.contains(2) << " Contains: 0 for false or 1 for true" << endl; 

  cout << "------------------------" << endl;

  cout << ll.get(0) << " Get: returns the pointer to the data at index" << endl; 

  int* numptr1 = ll.get(0);

  cout << numptr1 << endl;
  cout << *numptr1 << endl;

  cout << "------------------------" << endl;

  ll.add(5);
  ll.add(26);
  ll.add(12);

  ll.print();

  cout << "------------------------" << endl;
  
  cout << ll.get(2) << " Get: returns the pointer to the data at index" << endl; 

  int* numptr2 = ll.get(2);

  cout << numptr2 << endl;
  cout << *numptr2 << endl;

  cout << "------------------------" << endl;

  ll.print();
  
  cout << "------------------------" << endl;

  cout << ll.size() << " Size: returns the size of the list" << endl;

  cout << "------------------------" << endl;

  cout << ll.get(-1) << " Get: returns the pointer to the data at index. If 0 is returned its nullptr" << endl; 

  cout << "------------------------" << endl;
*/

  ///////////////////////////////////////////////////////////////////////

/*
  LinkedList<string> strList;

  // Here I will add stuff and then check get and remove

  cout << "Adding stuff to list" << endl;
  cout << endl;

  strList.add("Jed");
  strList.add("Kenadie");
  strList.add("Backman");

  strList.print();

  cout << endl;
  cout << "------------------------" << endl;
  cout << endl;

  // This checks the get() function 
  cout << "Checking get function" << endl;
  cout << endl;

  string* name2 = strList.get(2);   // creates a pointer to a string specifically to the string at position 2 of the list
  cout << name2 << endl;    // prints the address of the string
  cout << *name2 << endl;   // derefrences the pointer and prints out the varible its pointing to

  cout << endl;
  cout << "------------------------" << endl;
  cout << endl;

  // This checks the remove function 
  cout << "Checking the remove function" << endl;
  cout << endl;

  cout << "List before removing Backman" << endl;
  strList.print();

  cout << endl;

  cout << "List after removing Backman" << endl;
  cout << strList.remove("Backman") << endl;    // if 0 then list not modified. if 1 the list modified ("Backman" removed)
  strList.print();

  cout << endl;
  cout << "------------------------" << endl;
  cout << endl;

  // Now check if I can remove "Backman" again
  cout << "Checking to see if removing \"Backman\" outputs true or false" << endl;
  cout << endl;

  cout << strList.remove("Backman") << endl;    // This outputs a 0 because the list was not modified aka "Backman" was not in the list  
  strList.print();

  cout << endl;
  cout << "------------------------" << endl;
  cout << endl;

  // Now try to get in position 2 where there is nothing 
  cout << "Checking if you can get(2) even though there is nothing there" << endl;
  cout << endl;

  string* pos2 = strList.get(2);
  cout << pos2 << endl;    // returns 0 because its pointing at nullptr
  //cout << *pos2 << endl; // terminates code because you can't dereference a nullptr

  cout << endl;
  cout << "------------------------" << endl;
  cout << endl;

  // Now try clear the whole list
  cout << "Clear the whole list" << endl;
  cout << endl;

  strList.clear();
  strList.print();  // returns { } because the list is empty

  cout << endl;
  cout << "------------------------" << endl;
  cout << endl;
 
  // Now check remove on an empty list
  cout << "Checking remove on empty list" << endl;
  cout << endl;

  cout << strList.remove("Jed") << endl;
  strList.print();

  cout << endl;
  cout << "------------------------" << endl;
  cout << endl;

  // Now add a name and remove it to check if remove works on the first item 
  cout << "Add a name and remove" << endl;
  cout << endl;

  strList.add("name");
  strList.print();

  strList.remove("name");
  strList.print();


  cout << endl;
  cout << "------------------------" << endl;
  cout << endl;

  // Now add 2 names and remove the first to check if remove works on the first item when there is other stuff in the list still
  cout << "Add 2 names and remove the first" << endl;
  cout << endl;

  strList.add("name");
  strList.add("name2");
  strList.print();

  strList.remove("name");
  strList.print();


  cout << endl;
  cout << "------------------------" << endl;
  cout << endl;
  
  // check contains()
  cout << "Check contains() function: 0 for false  1 for true" << endl;
  cout << endl;

  cout << strList.contains("name") << endl;    // outputs 0 because "name" is not in strList
  cout << strList.contains("name2") << endl;   // outputs 1 because "name2" is in strList


  cout << endl;
  cout << "------------------------" << endl;
  cout << endl;

  // check size()
  cout << "Check size()" << endl;
  cout << endl;

  cout << strList.size() << endl;
  strList.add("Jed");
  cout << strList.size() << endl;
  strList.clear();
  cout << strList.size() << endl;
*/

  //////////////////////////////////
  //////////////////////////////////

  // Here I will test the functions one at a time
  
  // Constructor
  LinkedList<string> strList;

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
  LinkedList<int> intList;
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
  LinkedList<int> intList2;
  intList2.reverse();
  
  cout << endl;

  // reverse() again pt3
  cout << "reverse() again pt3" << endl; 
  LinkedList<int> intList3;
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
