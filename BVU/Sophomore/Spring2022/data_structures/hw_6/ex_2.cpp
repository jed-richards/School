#include <iostream>
using namespace std;

#include "Queue.h"

int main() {

    // Test your Queue code here to make sure that it works
    Queue<int> numQueue;

    // Test all functions 

    // 1.) try to pop on empty list 
    cout << "Empty: " << numQueue.empty() << endl;  // 1 for empty
    //numQueue.pop(); // Trying to pop() on an empty queue causes the program to crash

    cout << endl;

    // 2.) print queue as I push values onto it without popping 
    cout << "test push() w/out popping: " << endl;
    numQueue.print();  // print while empty
    cout << "Size: " << numQueue.size() << endl;
    cout << "Capacity: " << numQueue.capacity() << endl;
    for (int i=0; i<9; i++) {  // here is push values from 0 to 8 so that I can show that the grow will work
      numQueue.push(i);
      numQueue.print();
      cout << "Size: " << numQueue.size() << endl;
      cout << "Capacity: " << numQueue.capacity() << endl;
    }
    
    cout << endl;

    // 3.) clear queue so I can push and pop values 
    cout << "Clear and print to show empty" << endl;
    numQueue.clear();
    numQueue.print();
    cout << "Size: " <<  numQueue.size() << endl;
    cout << "Capacity: " << numQueue.capacity() << endl;

    cout << endl;

    // 4.)  
    cout << "test test push() and pop() at same time: " << endl;
    numQueue.print();  // print starting queue
    cout << "size(): " << numQueue.size() << endl;
    cout << "capactity(): " << numQueue.capacity() << endl;
    // this for loop cycles and pushes values on  
    for (int i=2; i<256; i=i*2) {
      numQueue.push(i);
      numQueue.print();  // print starting queue
      cout << "size(): " << numQueue.size() << endl;
      cout << "capactity(): " << numQueue.capacity() << endl;
    }
    // pop() 3 times 
    numQueue.pop();
    numQueue.pop();
    numQueue.pop();
    // print/size/capacity
    numQueue.print();  // print starting queue
    cout << "size(): " << numQueue.size() << endl;
    cout << "capactity(): " << numQueue.capacity() << endl;
    // push more values so the queue has to grow again and fix itself to have first at 0 and last and arrSize
    for (int i=1; i<14; i++) {
      numQueue.push(i);
      numQueue.print();  // print starting queue
      cout << "size(): " << numQueue.size() << endl;
      cout << "capactity(): " << numQueue.capacity() << endl;
    }

    cout << endl;

    // 5.) print the queue, current front value, and pop()
    cout << "test front() while popping()" << endl;
    while (!numQueue.empty()) {
      numQueue.print();
      cout << "current front value: " << numQueue.front() << endl;
      cout << "size: " << numQueue.size() << endl;
      numQueue.pop();
    }

    return 0;
}

