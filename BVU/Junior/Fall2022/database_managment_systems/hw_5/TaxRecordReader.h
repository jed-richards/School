#pragma once

#include <vector>
#include <fstream>
#include <cstring>
using namespace std;

#include "Record.h"
#include "Page.h"

// This class is allows the creation of an object to read the files written 
// by object from TaxRecordWriter.h
class TaxRecordReader {
  private:
    fstream dbFile;

  public:
    long long int block_size;
    long long int pagesRead = 0;
    long long int length;

    // Constuctor that takes in the desired filename to be opened and the size of the blocks to read
    TaxRecordReader(string fileName, long long int blockSize) {
      dbFile.open(fileName, ios::in | ios::binary);
      block_size = blockSize;

      // Here I had to do some finagling (idk if that is spelled right) 
      // to get an integer value that describes the number of bytes in the file
      dbFile.seekg (0, dbFile.end);
      length = dbFile.tellg();
      dbFile.seekg(0);
    }


    vector<Record> readPage() {

      // Seek the cursor in the file to the next block to read
      dbFile.seekg(block_size * pagesRead);

      // If we are not at the end of the file read a block
      if ((block_size * pagesRead) < length) {
        vector<Record> page;

        char block[block_size];

        dbFile.read(block, block_size);

        char *cursor = block;

        uint16_t numRecords = *(uint16_t*)cursor;
        cursor += sizeof(uint16_t);

        for (int i=0; i < numRecords; i++) {
          int ssn, income;
          string state = "xx";
          
          ssn = *(int*)cursor;
          cursor += sizeof(int);
          income = *(int*)cursor;
          cursor += sizeof(int);
          state[0] = cursor[0];
          state[1] = cursor[1];
          cursor += 2;
          string name = cursor;
          cursor += name.size() + 1;

          Record r(ssn, name, income, state);
          page.push_back(r);
        }
        pagesRead++;

        return page;
      }

      // if at the end of the file return an empty vector of records
      else {
        vector<Record> r;
        return r;
      }
    }

    void close() {
      dbFile.close();
    }

    ~TaxRecordReader() {
    }

};

