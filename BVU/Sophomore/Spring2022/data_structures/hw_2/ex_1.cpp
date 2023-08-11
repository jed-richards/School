//  Identifying Palindromic Numbers

#include <iostream>
using namespace std;

// This function finds the length of the given number without turning it into a string and returns its length in a variable called length
int findLength(int yourNumber) {
    
    int length = 0;
    int temp = yourNumber;
    
    while(temp > 0) {
        temp = temp/10;
        length++;
    }
    return length;

}

// This functions says if a number is a palindrome or not
bool isPalindrome(int yourNumber) {
    
    // Call findLength function for yourNumber which returns the variable length
    int length = findLength(yourNumber);

    // make variables for the reverse (rev), temp1, and temp2 
    int temp1;
    int temp2 = yourNumber;
    int rev = 0;   

    // take the last digit of yourNumber and put it in rev
    for(int i = 0; i < length; i++) {

        temp1 = temp2%10;
        rev = (rev*10) + temp1;
        temp2 = temp2/10;
    
    }
    
    if (rev == yourNumber) {
        return true;
    }
    
    else {
        return false;
    }
}

int main() {
    
    for(int i = 0; i < 150; i++) {
        
        if (isPalindrome(i) == true) {
            cout << i << " is a palindrome." << endl;
        }
    }

    return 0;
}
