#pragma once

#include <stack>
using namespace std;





stack<int> stackSort(stack<int> input) {

    // make two stacks and a variable to track the number of items moved
    stack<int> output;
    stack<int> tempStack;
    int numItemsMoved = 0;
    int tempVal;
    int currVal;

    while (!input.empty()) {

      // store inputs top value and pop it 
      currVal = input.top();  
      input.pop();                

      // First move always goes to output
      if (numItemsMoved == 0) {
        output.push(currVal);   // on the first item always move it to output
        numItemsMoved++;
      }

      // Second move ensures that we will have an item in tempStack and output
      else if (numItemsMoved == 1) {
        // move output.top if it is less than currVal
        if (currVal > output.top()) {
          tempVal = output.top();
          output.pop();
          tempStack.push(tempVal);
          output.push(currVal);
        } 
        // push currVal onto tempStack
        else {
          tempStack.push(currVal);
        }
        numItemsMoved++;
      }

      // After the first and second move the moves will always be the same.
      // Check the value against the top value of output and tempStack to find where it goes
      else {
        // if currVal is smaller or equal to tempStack.top(), move tempStack.top() onto output and put currVal onto tempStack
        if (currVal <= tempStack.top()) {
          while (!tempStack.empty() && currVal <= tempStack.top()) {
            tempVal = tempStack.top();
            tempStack.pop();
            output.push(tempVal);
          }
          tempStack.push(currVal);
        }
        // else currVal is greater than tempStack.top(), so move it on output always checking the top value  
        else {
          // always check if output is empty
          while (!output.empty() && currVal > output.top()) {
            tempVal = output.top();
            output.pop();
            tempStack.push(tempVal);
          }
          output.push(currVal);
        }
      }
    }

    // move everything from tempStack to output and then return  
    while (!tempStack.empty()) {
      tempVal = tempStack.top();
      tempStack.pop();
      output.push(tempVal);
    }

    return output;
}

