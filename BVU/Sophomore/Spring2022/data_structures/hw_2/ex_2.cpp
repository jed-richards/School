// Simple Calculator

#include <iostream>
using namespace std;

void Calculator() {

    // Make variables for num1, num2, answer, and the operator (sign)
    float num1, num2, answer;
    string sign;
    
    // Asks the user for input and stores it in variables
    cout << "Enter your first number: " << endl;
    cin >> num1;

    cout << "Enter an operator (+, -, *, /): " << endl;
    cin >> sign;

    cout << "Enter your second number: " << endl;
    cin >> num2;

    if (sign == "+") {
        answer = num1 + num2;
    }
    else if (sign == "-") {
        answer = num1 - num2;
    }
    else if (sign == "*") {
        answer = num1 * num2;
    }
    else if (sign == "/") {
        answer = num1 / num2;
    }
    else {
        cout << "That sign is not available." << endl;
    }
    cout << "Your answer is: " << answer << endl;
}

int main() {
    
    Calculator();

    return 0;
}
