#include <iostream>
#include <mysql/mysql.h>
#include <cstdlib>

#include "appFunctions.h"

using namespace std;

int main() {

  cout << "Hello" << endl;
  cout << endl;

  while(1) {
    printChoiceOptions();
    cout << endl;
  }

  return 0;
} 
