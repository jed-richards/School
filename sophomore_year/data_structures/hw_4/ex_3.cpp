// Seive of Eratosthenes using vectors 

#include <iostream>
#include <vector> 

using namespace std;

int main() {

  
  cout << "Hello Prime Numbers!" << endl;


  // Allows the user to input a number they want all primes before
  int userNum;
  cout << "Enter a number that you want all primes less than that number: " << endl;
  cin >> userNum;
 

  // Creates allNumbers vector of initialSize = userNum and sets all to zeros
  vector<int> allNumbers(userNum,0);  


  // Populates allNumbers vector with numbers 0-userNum but not including userNum
  for (int i=0; i < userNum; i++) {
    allNumbers[i] = i;
  }


  // Initialize an empty vecotr that we can push_back() prime numbers to
  vector<int> primeNumbers;  
 

  // This for loop cycles through the numbers of allNumbers up to its size starting at 2
  // becuase 0 and 1 are not prime. Therefore, I hardcoded the loop to start at 2.
  // It then iterates and checks if the current number is not 0 and if it is not 0 it
  // can push_back() that number to primeNumbers (meaning that it is a prime number).
  // Finally we jump into another for loop that cycles through the multiples of i 
  // (the current number that the first for loop is on) and changes all those multiples 
  // to 0 so that they get passed by (not looked at again). 
  for (int i=2; i < allNumbers.size(); i++) {
    if (allNumbers[i] != 0) {         
      primeNumbers.push_back(allNumbers[i]);
      for (int j=2*i; j < allNumbers.capacity(); j=j+i) {    // j=2*i starts j at the first multiple of i
                                                             // j=j+i increments j to the next multiple of i
        if (allNumbers[j] != 0) {
          allNumbers[j] = 0;
        } 
      }
    }
  }

  // Since vector does not have a print() fucntion, I will use a for loop to print out the primes
  for (int i=0; i < primeNumbers.size(); i++) {
    cout << i << ": " << primeNumbers[i] << endl;
  }


  return 0;
}
