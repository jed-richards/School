#ifndef PROJECT_H
#define PROJECT_H

#include <vector>
#include <algorithm>
using namespace std;
#include "Record.h"
#include "Operator.h"
#include "FileReader.h"


class Project : public Operator {
  private:
    // Private member variables
    Operator* input;
    FileReader fr;


  public:
    // Public member variable 
    vector<string> fieldNames;


    // Project constructor for a project straight from file (disk)
    Project(string fileName, vector<string> inFieldNames) {
      fr = FileReader(fileName);
      input = &fr;
      fieldNames = inFieldNames;
    }


    // Project constructor from another project operator
    Project(Operator *op, vector<string> inFieldNames) {
      input = op; 
      fieldNames = inFieldNames;
    }


    // Member Function to open operator which calls open on the next previous project
    // operator
    void open() {
      input->open();
    }



    // Method that returns the next page for the current operator. This method calls next
    // on the previous operator
    vector<Record> next() {
      vector<Record> outPage;  // Create a vector for the outPage  
      vector<Record> inPage;   // Create a vector for the inPage 
      inPage = input->next();  // Call input->next() to return the next page from previous operator 

      // If inPage is empty we hit end of file
      if (inPage.empty()) {
        return outPage;
      }

      // Else grab first record and make a vector of ints that will hold the index of the attributes
      // we are projecting over
      Record firstRecord = inPage[0];
      vector<int> attrIndex;
      int count = 0;
      for (Attribute a : firstRecord.attributes) {
        if (find(fieldNames.begin(), fieldNames.end(), a.attrName) != fieldNames.end()) {
          attrIndex.push_back(count);
        }
        count++;
      }

      // If our vector of attribute indexes is empty, then we are projecting over something that is 
      // not in the inPage, so return an empty outPage
      if (attrIndex.empty()) {
        return outPage;
      }
  
      // Else for each record in the inPage, make a new vector of attrbutes that will be the updated
      // record with only attributes we projected over. Then make a new record based on the newAttrs 
      // of the inRecord
      for (Record r : inPage) {
        vector<Attribute> newAttrs;
        for (int index : attrIndex) {
          Attribute attr = r.attributes[index];
          newAttrs.push_back(attr);
        }
        Record outRecord(newAttrs);
        outPage.push_back(outRecord);
      }

      // Finally return the outPage of records with only attributes that were projected over
      return outPage;
    }


    // Method that calls close on the previous operator
    void close() {
      input->close();
    }
};

#endif
