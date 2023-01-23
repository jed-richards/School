#pragma once

//#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include "Record.h"
#include "Page.h"

using namespace std;

// This is a class that can open a file and write a specified block size of records to file
class TaxRecordWriter {
  private:
    fstream dbFile;
    Page page;

  public:
    long long int block_size;
    long long int pagesWritten = 0;

    TaxRecordWriter(string fileName, long long int blockSize) {

      // Open fileName for writing in binary and delete all prior contents of file 
      dbFile.open(fileName, ios::out | ios::binary | ios::trunc);  

      block_size = blockSize;

      // Make the page object have capacity block_size to store records and then flush/write all at once 
      page.pageCapacity = block_size;

    }

    // Function call to write a record to the file. The function calls the write record function 
    void writeRecord(int ssn, string name, int income, string state) {
      writeRecord( Record (ssn, name, income, state) );
    }
    
    void writeRecord(Record r) {
      // If page is not full and can fit another record then add record
      if (page.pageSize + r.recordBytes <= page.pageCapacity) {
        page.addRecord(r);
      }
      // Else page is full and can't fit another, so write page and add the record to cleared page
      else {
        writePage(page);
        page.clear();
        page.addRecord(r);
      }
    }

    // Write page to file
    void writePage(Page p) {

      // Place cursor in the file to where the start of the block we are writing page to 
      dbFile.seekp(block_size * pagesWritten);

      // Write a string of length block_size to the file for debugging purposes
      string lines(block_size, '-');
      dbFile.write(lines.c_str(), lines.size());

      // Place cursor back at beginning of block
      dbFile.seekp(block_size * pagesWritten);

      // Write metadata (int numRecords)
      dbFile.write((char*)&p.numRecords, sizeof(p.numRecords));
      
      // Write each record
      for (int i=0; i < p.numRecords; i++) {
        // Write SSN first
        dbFile.write((char*)&p.records[i].ssn, sizeof(p.records[i].ssn));
        // Write income second
        dbFile.write((char*)&p.records[i].income, sizeof(p.records[i].income));
        // Write state third
        dbFile.write(p.records[i].state.c_str(), 2);
        // Write name last (end of record at null byte)
        dbFile.write(p.records[i].name.c_str(), p.records[i].name.size()+1);
      }

      // Increment the number of pages written by one
      pagesWritten++;

    }


    // Close the file and write the last page if it is not empty
    void close() {
      if (!page.empty())
        writePage(page);
      dbFile.close();
    }

    ~TaxRecordWriter() {
    }

};

