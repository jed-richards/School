#ifndef FILEREADER_H
#define FILEREADER_H

#include <vector>
#include <sstream>
using namespace std;
#include "Record.h"
#include "Operator.h"
#include <fstream>


// This function takes in a string with items delimited by commas
// and returns a vector of those items.
// Example - input: "str1,str2,str3,str4"
//          output: {"str1", "str2", "str3", "str4"}
vector<string> split(string line) {
  vector<string> v;
  string s;
  istringstream is(line);
  while (getline(is, s, ','))
    v.push_back(s);
  return v;
}


// Here we define a class "FileReader" that is a child of the "Operator" class
class FileReader : public Operator {
  public:
    // Member Variables
    fstream dbFile; 
    string fileName; 
    vector<string> attributeNames;
    vector<string> types;


    // Default Constructor
    FileReader() {
    }


    // Constructor that takes in a fileName
    FileReader(string _fileName) {
      fileName = _fileName;
    }


    // This method opens the file and reads in the first 3 lines. 
    // Line1 is the line that contains the attribute names
    // Line2 is the line that contains the attribute types
    // Line3 is just junk
    // We then use out string split function to store line1 and line2 in vectors of strings for
    // later use.
    void open() {
      dbFile.open(fileName, ios::in);

      string line1;
      string line2;
      string junk;

      getline(dbFile, line1);
      getline(dbFile, line2);
      getline(dbFile, junk);

      attributeNames = split(line1);
      types = split(line2);
    }


    // This method returns a page with pageSize based on the number of records we can store on 
    // one page. This page has records with all attributes listed in the file. There has been no
    // project yet.
    vector<Record> next() {
      vector<Record> outPage;
      string line;
      while (outPage.size() < pageSize && getline(dbFile, line)) {
        vector<string> values = split(line);
        Record record(types, values, attributeNames);
        outPage.push_back(record);
      }
      return outPage;
    }


    // This method closes the fstream object
    void close() {
      dbFile.close();
    }
};

#endif
