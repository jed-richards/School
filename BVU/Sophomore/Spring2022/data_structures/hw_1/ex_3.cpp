// Create a function that prints a line

#include <iostream>
using namespace std;

void printLine(int length, char symbol) {
    
    for (int i = 0; i < length; i++) {
        cout << symbol;
    }
    cout << endl;
}

int main() {

    printLine(5, 'a');
    printLine(10, '#');
    printLine(20, '&');

    return 0;

}
