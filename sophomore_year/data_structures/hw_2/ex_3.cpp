#include <iostream>
#include "pen.h"
using namespace std;

int main() {

// Creates the object p from class Pen
    Pen p; 

// Initial move
    p.moveLeft(12);
    p.moveUp(5);

// Start drawing J
    p.lowerPen();
    p.moveRight(8);

    p.raisePen();

    p.moveLeft(4);

    p.lowerPen();

    p.moveDown(8);
    p.moveLeft(4);

    p.raisePen();

// Move pen w/out drawing
    p.moveUp(8);
    p.moveRight(12);

// Start drawing R
    p.lowerPen();

    p.moveDown(8);
  
    p.raisePen();

    p.moveUp(8);

    p.lowerPen();

    p.moveRight(4);
    p.moveDown(4);
    p.moveLeft(4);

// Make the diagonal for the R in a loop
    for (int i = 0; i < 4; i++) {
        p.raisePen();

        p.moveDown();
        p.moveRight();

        p.lowerPen();
    }
   
// Move to make exclamation points
    p.raisePen();

    p.moveUp(8);
    p.moveRight(6);

// Make exclamation points !!!
    for (int i = 0; i <= 2 ; i++) {

        p.lowerPen();
        p.moveDown(6);
        p.raisePen();
        p.moveDown(2);
        p.lowerPen();

        p.raisePen();
        p.moveUp(8);
        p.moveRight(2);

    }

// Underline twice
    p.moveDown(10);
    p.moveLeft(2);
    p.lowerPen();
    p.moveLeft(26);
    p.raisePen();
    p.moveDown(2);
    p.lowerPen();
    p.moveRight(26);
    p.raisePen();

// Draw to the canvas
    p.drawCanvas();
    
    return 0;
}
