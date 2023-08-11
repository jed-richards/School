#include <iostream>
#include <unistd.h> // Gives us access to the sleep(int seconds) function
#include "Timer.h"
using namespace std;

// In this I tested my timer and all its functions. I commented out all of the lines print text characters
// to the screen because I saw that some of my times were getting delayed due to printing taking too long.

int main() {
    
    Timer t;

    t.start();                  
    sleep(1);                             
    //cout << "Start: " << endl;              // Start works and then adds fractional time each time it is checked
    cout << t.getTime() << endl; 
    cout << t.getTime() << endl; 
    cout << t.getTime() << endl; 
   
    cout << endl;

    t.clear();
    //cout << "Clear: " << endl;             // Clear works while running! returns back something times 10
    cout << t.getTime() << endl;             // to the -5 or something
    cout << t.getTime() << endl; 

    cout << endl;

    //cout << "Test if still running: " << endl;      // Timer is still running after I clear!
    sleep(1);                    
    cout << t.getTime() << endl; 
    sleep(1);
    cout << t.getTime() << endl; 
    sleep(1);
    cout << t.getTime() << endl; 
    
    cout << endl;

    t.stop();
    sleep(1);
    //cout << "Stop: "  << endl;             // Stop works! It takes in a fractional time to actualy stop
    cout << t.getTime() << endl;             // then it halts there (does not compund the fractional)
    cout << t.getTime() << endl; 
    cout << t.getTime() << endl; 

    cout << endl;
    
    t.clear();
    //cout << "Clear while stopped: " << endl;          // Clear while stopped returns a value of 0. This is corect beacuse
    cout << t.getTime() << endl;                        // if a timer was not running and you cleared it, it should read 0
    cout << t.getTime() << endl;                        // because it is not running

    cout << endl;

    t.start();                  
    sleep(1);                           // Then start works again
    //cout << "Start: " << endl; 
    cout << t.getTime() << endl; 
    cout << t.getTime() << endl; 
    cout << t.getTime() << endl; 

    cout << endl;

    //cout << "More tests while running: " << endl;
    
    t.clear();
    //cout << "Clear while running: " << t.getTime() << endl; 
    
    sleep(2);
    cout << t.getTime() << endl;         // Here the timer is still running and should output 2.(somthing)

    t.stop();
    //cout << "Stop: " << endl;
    cout << t.getTime() << endl;         // These should both output 2.(something)

    //cout << "Stop again: " << endl;
    cout << t.getTime() << endl;

    t.clear();
    //cout << "Clear while stopped: " << endl; 
    cout << t.getTime() << endl;
    

    

    return 0;
}

