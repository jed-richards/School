#include <iostream>
using namespace std;

#include "Stack.h"

int main() {
    // Test your Stack code here to make sure that it works
    Stack<int> numStack;

    // Test all functions 

    // 1.) try to pop on empty list 
    cout << "Empty: " << numStack.empty() << endl;  // 1 for empty
    //numStack.pop(); // this line causes a segmentation falut because trying to pop on empty list 
                      // thats why I commented it out

    cout << endl;

    // 2.) print stack as I push values onto it also showing the size of the stack 
    cout << "test push(): " << endl;
    numStack.print();  // print while empty
    cout << "size(): " << numStack.size() << endl;
    for (int i=0; i<5; i++) {
      numStack.push(i);
      numStack.print();
      cout << "size(): " << numStack.size() << endl;
    }

    cout << endl;

    // 3.) print stacks as I pop values 
    cout << "test pop(): " << endl;
    numStack.print();  // print starting stack
    cout << "size(): " << numStack.size() << endl;
    // this for loop cycles through 3 times popping, printing, and printing size 
    for (int i=0; i<3; i++) {
      numStack.pop();
      numStack.print();  // print starting stack
      cout << "size(): " << numStack.size() << endl;
    }

    cout << endl;

    // 4.) print the stack and the current top value
    cout << "test top(): " << endl;
    numStack.print();  // print starting stack
    cout << "current top value: " << numStack.top() << endl;
    // push values onto the stack and test again
    for (int i=2; i<64; i=i*2) {
      numStack.push(i);
      numStack.print();  // print starting stack
      cout << "current top value: " << numStack.top() << endl;
    }

    cout << endl;

    // 5.) now pop all values until empty and then test top() on an empty stack
    cout << "test pop on empty stack: " << endl;
    numStack.print();
    cout << "current size: " << numStack.size() << endl;
    // this while loop pops until empty 
    while (!numStack.empty()) {
      numStack.pop();
      numStack.print();
      cout << "current size: " << numStack.size() << endl;
    }

    

  
    return 0;
}
