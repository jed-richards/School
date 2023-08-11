// Noise Pollution (If, Else If, Else)

#include <iostream>
using namespace std;

string checkNoisePollution(int loudness, int hour) {
    
    string response;
    if (loudness > 90) {
        response = "Quiet down or I'll call the cops!";
    }
    else if (hour >= 20 || hour < 8) {
        if (loudness > 65){
            response = "Quiet down or I'll call the cops!";
        }
        else {
            response = "Oh, they're just kids being kids.";
        }
    }
    else {
        response = "Oh, they're just kids being kids.";
    } 
    return response;
}

int main() {
    
    cout << checkNoisePollution(50, 18) << endl;
    cout << checkNoisePollution(20, 3)  << endl;
    cout << checkNoisePollution(95, 14) << endl;
    cout << checkNoisePollution(80, 10) << endl;
    cout << checkNoisePollution(80, 20) << endl;

    return 0;
}

