#ifndef SELECT_H
#define SELECT_H

#include "Operator.h"
#include <vector>
#include <algorithm>

class Select : public Operator {

  private:
    // Private member variables
    Operator* input;
    FileReader fr;

  public:
    
    // Set up select pedicate variables
    string p_attr;
    string p_op;    // p_op can only be on of these operators ('<', '>', '=', '!=')
    string p_val;
    int int_p_val;
    double double_p_val;
    
    // Set up vectors of records for pages as member variables
    vector<Record> inPage;
    vector<Record> outPage;

    // Set up indexes for execution when calling next 
    int inPageIndex = 0;
    int attrIndex;     // This variable is going to be the index of p_attr in the vector inPage

    // This is a dummy variable to check if the operator has called next. It is used in next()
    // to get the first inPage.
    bool called = false;

    // This is a variable that is used as a flag to check if p_attr was found in records of inPage
    bool isFound = false;

    // This is a varibale used to help with select predicate.
    string attr_type;

    // Select constructors
    Select(string fileName, string in_p_attr, string in_p_op, string in_p_val) {
      fr = FileReader(fileName);
      input = &fr;
      p_attr = in_p_attr;
      p_op = in_p_op;
      p_val = in_p_val;
    }

    Select(Operator *op, string in_p_attr, string in_p_op, string in_p_val) {
      input = op; 
      p_attr = in_p_attr;
      p_op = in_p_op;
      p_val = in_p_val;
    }

    void open() {
      input->open();
    }

    vector<Record> next() {

      // This if statement checks if next has been called. If it has not been called, call input->next() and do the following
      if (!called) {
        called = true;
        inPage = input->next();

        // If inPage is empty we hit end of file
        if (inPage.empty()) {
          return outPage;
        }

        // Get attrIndex and attr_type so we can easily check the select predicate
        Record firstRecord = inPage[0];
        for (int i=0; i < firstRecord.attributes.size(); i++) {
          if (firstRecord.attributes[i].attrName == p_attr) {
            attrIndex = i;
            attr_type = firstRecord.attributes[attrIndex].type;
            isFound = true;
            break;
          }
        }

        // If isFound flag is false, then p_attr is not in records of inPage
        if (!isFound) {
          return outPage;
        }
      }


      // 
      while (outPage.size() < pageSize) {

        // This if statement checks if we have reached the end of a incoming page and if so set inPage index to 0 and then call for next page.
        if (inPageIndex == pageSize) {
          inPageIndex = 0;
          inPage = input->next();
        }

        // This if statement will only be true when the inPageIndex is less than pageSize and inPageIndex is '>=" to inPage.size().
        // This would mean inPage is not at full capacity which means we have hit the end of the file. Therefore if inPageIndex is
        // equal to the size of inPage, we return outPage.
        if (inPageIndex >= inPage.size()) {
          vector<Record> temp = outPage;
          outPage.clear();
          return temp;
        }
        
        Record r = inPage[inPageIndex];

        // Here is a chain of if's and else if's to determine what operation we are doing and also what type to do the operation on.
        if (p_op == "<") {
          if (attr_type == "String") {
            if (r.attributes[attrIndex].S < p_val) {
              outPage.push_back(r);
            }
          }
          else if(attr_type == "Double") {
            double_p_val = stod(p_val);  // string to double
            if (r.attributes[attrIndex].D < double_p_val) {
              outPage.push_back(r);
            }
          }
          else if(attr_type == "Integer") {
            int_p_val = stoi(p_val);  // string to int
            if (r.attributes[attrIndex].I < int_p_val) {
              outPage.push_back(r);
            }
          }
        }

        else if (p_op == ">") {
          if (attr_type == "String") {
            if (r.attributes[attrIndex].S > p_val) {
              outPage.push_back(r);
            }
          }
          else if(attr_type == "Double") {
            double_p_val = stod(p_val);  // string to double
            if (r.attributes[attrIndex].D > double_p_val) {
              outPage.push_back(r);
            }
          }
          else if(attr_type == "Integer") {
            int_p_val = stoi(p_val);  // string to int
            if (r.attributes[attrIndex].I > int_p_val) {
              outPage.push_back(r);
            }
          }
        }

        else if (p_op == "=") {
          if (attr_type == "String") {
            if (r.attributes[attrIndex].S == p_val) {
              outPage.push_back(r);
            }
          }
          else if(attr_type == "Double") {
            double_p_val = stod(p_val);  // string to double
            if (r.attributes[attrIndex].D == double_p_val) {
              outPage.push_back(r);
            }
          }
          else if(attr_type == "Integer") {
            int_p_val = stoi(p_val);  // string to int
            if (r.attributes[attrIndex].I == int_p_val) {
              outPage.push_back(r);
            }
          }
        }

        else if (p_op == "!=") {
          if (attr_type == "String") {
            if (r.attributes[attrIndex].S != p_val) {
              outPage.push_back(r);
            }
          }
          else if(attr_type == "Double") {
            double_p_val = stod(p_val);  // string to double
            if (r.attributes[attrIndex].D != double_p_val) {
              outPage.push_back(r);
            }
          }
          else if(attr_type == "Integer") {
            int_p_val = stoi(p_val);  // string to int
            if (r.attributes[attrIndex].I != int_p_val) {
              outPage.push_back(r);
            }
          }
        }

        else {
          return outPage;
        }

        inPageIndex++;
      }
      
      // Here we make a temporary vector to hold outPage that way we can clear outPage and return temp. 
      // This is done because if we are returning a page that has undergone the select predicate and we
      // are here, then the page is either full or we are at end of file. If it is full we need to clear 
      // outPage that way when next() is called again we have a fresh outPage (empty) to work with. This
      // is becasue we made outPage a member variable.
      vector<Record> temp = outPage;
      outPage.clear();
      return temp;
    }

    void close() {
      input->close();
    }
};

#endif
