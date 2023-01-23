#pragma once

//#include <string>
#include <iostream>
#include <cstring>
using namespace std;

class Record {
  public:
    int ssn;
    string name;
    int income;
    string state;
    int recordBytes;

    // Default constructor has to stay so we can initialize vector<Record> v;
    Record() {
    }

    // Name is of variable length with nullbyte
    // string state => fixed length of 2 chars => 2bytes (1 byte/ 1 char) 
    // Using uint16_t (unsigned 16 bit int) 2 bytes 
    Record(int _ssn, string _name, int _income, string _state) {
      ssn = _ssn; 
      name = _name;
      income = _income;
      state = _state;
      recordBytes = (name.size() + 1) + 2*sizeof(int) + 2;  
    }

    void printInfo() {
      cout << "Record info: " << endl;
      cout << " ssn: " << ssn << endl;
      cout << " name: " << name << endl;
      cout << " income: " << income << endl;
      cout << " state: " << state << endl;
      cout << " recordBytes: " << recordBytes << endl;
    }

    // Add additional and more useful constructors if you'd like.
    // But please make sure the above default constructor continues to exist

    friend ostream& operator<< (ostream& os, const Record &r) {
      os << "(" <<  r.ssn << ", " << r.name << ", " << r.income << ", " << r.state << ")";
      return os;
    }
};

