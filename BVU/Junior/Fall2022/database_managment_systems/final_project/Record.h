#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


// A class for Attributes
class Attribute {
  public:
    int I;
    double D;
    string S;
    string type;
    string attrName;
    
    Attribute(string inType, string value, string _attrName) {
      type = inType;
      attrName = _attrName;
      if (type == "String") {
        S = value;
      }
      else if(type == "Double") {
        D = stod(value);  // string to double
      }
      else if(type == "Integer") {
        I = stoi(value);  // string to int
      }
    }
};


// A class for Records
class Record {
  public:
    // Record class member variables
    vector<Attribute> attributes;


    // Default Constuctor
    Record() {
    }


    // Constructor that stores attributes
    Record (vector<string> types, vector<string> values , vector<string> inAttrName) {
      for (int i=0; i<types.size(); i++) {
        Attribute attr(types[i], values[i], inAttrName[i]);
        attributes.push_back(attr);
      }
    }


    // Constructor that takes in a vector of attributes
    Record (vector<Attribute> inAttributes) {
      attributes = inAttributes;
    }


    // Concatenate function for join operator
    Record concatenate (Record r1, Record r2) {
      for (Attribute attribute : r2.attributes) {
        r1.attributes.push_back(attribute);
      }
      return r1;
    }


    friend ostream& operator<< (ostream& os, const Record& r) {
      // Print a space-delimited list of attribute vals with a space after
      // each of the values. Example: "val1 val2 val3 "

      for (int i=0; i < r.attributes.size(); i++) {
        if (r.attributes[i].type == "Integer")
          os << r.attributes[i].I << " ";
        else if (r.attributes[i].type == "Double")
          os << r.attributes[i].D << " ";
        else if (r.attributes[i].type == "String")
          os << r.attributes[i].S << " ";
      }

      // Finally, return os
      return os;
    }
};

#endif
