#include <iostream>
#include "DynamicArray.h"
using namespace std;

int main() {
  cout << "[Hello DynamicArray!]" << endl;


  // In this file, I am running tests on my DynamicArray class
  
  // In this block of code I test the 
  // 1.) default constructor
  // 2.) push_back()
  // 3.) pop_back()
  // 4.) size()
  // 5.) capacity()
  // 6.) my print() function
  // 7.) reverse() 
  // All of this works

/*
  DynamicArray<int> da;

  // push_back() works!
  da.push_back(5);  
  da.push_back(16);
  da.push_back(1);
  da.push_back(98);
  cout << "Size: " << da.size() << endl;
  cout << "Capacity: " << da.capacity() << endl;
  da.print();

  cout << endl;
  cout << "Now I am going to test my reverse function" << endl;
  cout << endl;

  // reverse() works!!
  da.reverse();    
  cout << "Size: " << da.size() << endl;
  cout << "Capacity: " << da.capacity() << endl;
  da.print(); 

  cout << endl;
  cout << "Now I am going to pop_back()" << endl;
  cout << endl;

  // pop_back() works!!!
  da.pop_back();
  da.pop_back();
  cout << "Size: " << da.size() << endl;
  cout << "Capacity: " << da.capacity() << endl;
  da.print(); 
 
  cout << endl;
  cout << "Now I can write over the stuff I pop_backed" << endl;
  cout << endl;

  da.push_back(12);
  da.push_back(35);
  cout << "Size: " << da.size() << endl;
  cout << "Capacity: " << da.capacity() << endl;
  da.print(); 
*/


  // Now I will test my grow function
  
  // In this block of code I test the 
  // 1.) constructor(initialSize, defaultValue) with a different type than above
  // 2.) grow() The grow() function takes place after the user tries to push_back and the size == capacity  
  // 3.) clear() 
  // 4.) the copy constructor 
  // All of this works
  
  DynamicArray<string> strArr(2,"Jed");

  strArr.print();
  strArr.push_back("Hello");
  strArr.push_back("Dr. Backman");
  
  cout << "Size: " << strArr.size() << endl;
  cout << "Capacity: " << strArr.capacity() << endl;
  strArr.print();

  cout << endl;
  cout << "Now I will push back one more time to check my grow() function" << endl;
  cout << endl;

  strArr.push_back("ComSci");
  cout << "Size: " << strArr.size() << endl;
  cout << "Capacity: " << strArr.capacity() << endl;
  strArr.print();

/*  
  cout << endl;
  cout << "Now I will test my clear() function" << endl;
  cout << endl;

  
  // Size reads as 0 after clear (so it works)!!!!!

  strArr.clear();
  cout << "Size: " << strArr.size() << endl;
  cout << "Capacity: " << strArr.capacity() << endl;
  strArr.print();
*/


  // Here I test the copy constructor

  cout << endl;
  cout << "Here is the copyOfStrArr" << endl;
  cout << endl;

  DynamicArray<string> copyOfStrArr(strArr);
  cout << "Size: " << copyOfStrArr.size() << endl;
  cout << "Capacity: " << copyOfStrArr.capacity() << endl;
  copyOfStrArr.print();


  return 0;
}
