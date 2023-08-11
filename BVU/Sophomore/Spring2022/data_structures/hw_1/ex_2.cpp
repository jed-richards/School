// Handling Input to Functions
// Old McDonald

#include <iostream>
using namespace std;

void singVerse(string animalName, string animalNoise) {

    cout << "Old MacDonald had a farm, E-I-E-I-O" << endl;
    cout << "And on that farm he had a " << animalName << " E-I-E-I-O" << endl;
    cout << "With a " << animalNoise << ", " << animalNoise << " here and a " << animalNoise << ", " << animalNoise << " there" << endl;
    cout << "Here a " << animalNoise << ", there a " << animalNoise << ", everywhere a " << animalNoise << ", " << animalNoise << endl;
    cout << "Old MacDonald had a farm, E-I-E-I-O" << endl;
    cout << endl;
}

int main() {

    singVerse("cow", "moo");
    singVerse("dog", "woof");
    singVerse("space walrus", "goo goo g'joob");
    
    return 0;

}
