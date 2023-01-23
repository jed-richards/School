// Create  function that prints a rectangle

#include <iostream>
using namespace std;

void printRectangle(int width, int height, char symbol) {

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            cout << symbol;
        }
        cout << endl;
    }
}

int main() {

    printRectangle(5, 5, 'a');
    printRectangle(20, 4, '#');
    printRectangle(6, 6, '0');

    return 0;

}

