#include <iostream>
#include <stack>
using namespace std;

#include "ex_3.h"

int main() {

    // Create a stack
    stack<int> unsorted;

    // Populate the stack with values
    unsorted.push(44);
    unsorted.push(3);
    unsorted.push(1);
    unsorted.push(16);
    unsorted.push(21);
    unsorted.push(2);
    unsorted.push(7);
    unsorted.push(12);
    unsorted.push(41);
    

    // Call the stackSort function and get the return value
    stack<int> sorted = stackSort(unsorted);

    // Check to make sure that the resulting stack is sorted.
     
    // I popped the values so I could print
    // The values get printed top to bottom
    cout << "[ ";
    while (!sorted.empty()) {
      cout << sorted.top() << " ";
      sorted.pop();
    }
    cout << "]";


    return 0;
}
