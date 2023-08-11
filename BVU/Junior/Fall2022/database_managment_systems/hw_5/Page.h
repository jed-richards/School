#pragma once

#include <iostream>
#include <vector>
#include "Record.h"
#include <cstring>
using namespace std;

// This is a class I made to signify a page/block with all of its metadata.
// It keeps track of the number of records in the page and the bytes capactiy 
// and the current byte count
class Page { 
  public:
    vector<Record> records;
    uint16_t numRecords;
    long long int pageCapacity; 
    long long int pageSize; 

    // Default Constructor
    Page() {
      numRecords = 0;
      pageSize = sizeof(numRecords);
    }

    void addRecord(Record r) {
      records.push_back(r);
      numRecords++;
      pageSize += r.recordBytes;
    }

    bool empty() {
      if (numRecords == 0) {
        return true;
      }
      else {
        return false;
      }
    }

    // Use vector clear function and set pageSize back to just the size of numRecords (4) and set numRecords back to 0
    void clear() {
      records.clear(); 
      numRecords = 0;
      pageSize = sizeof(numRecords);
    }


};
