#include <iostream>
#include <vector>
using namespace std;

#include "TaxRecordWriter.h"
#include "TaxRecordReader.h"
#include "Record.h"
#include "Page.h"


int main() {

  TaxRecordWriter writer("file.data", 64);

  writer.writeRecord(Record (987654322, "backman", 2012, "CA"));
  writer.writeRecord(Record (987654322, "backman", 2012, "CA"));
  writer.writeRecord(Record (987654321, "stone", 1999, "MN"));
  writer.writeRecord(Record (555555555, "shepherd", 2017, "IA"));
  writer.writeRecord(Record (111111111, "richards", 2022, "CO"));
  writer.writeRecord(Record (987654321, "stone", 1999, "MN"));
  writer.writeRecord(Record (555555555, "shepherd", 2017, "IA"));
  writer.writeRecord(Record (111111111, "richards", 2022, "CO"));
  writer.writeRecord(Record (111421317, "stuff", 2028, "AL"));
  writer.writeRecord(Record (111421317, "stuff", 2028, "AL"));
  writer.writeRecord(Record (111421317, "stuff", 2028, "AL"));
  writer.writeRecord(Record (111421317, "stuff", 2028, "AL"));
  writer.writeRecord(Record (987654322, "backman", 2012, "CA"));
  writer.writeRecord(Record (987654322, "backman", 2012, "CA"));
  writer.writeRecord(Record (987654322, "backman", 2012, "CA"));
  writer.writeRecord(Record (987654322, "backman", 2012, "CA"));
  writer.writeRecord(Record (987654321, "stone", 1999, "MN"));
  writer.writeRecord(Record (555555555, "shepherd", 2017, "IA"));
  writer.writeRecord(Record (111111111, "richards", 2022, "CO"));
  writer.writeRecord(Record (987654321, "stone", 1999, "MN"));
  writer.writeRecord(Record (555555555, "shepherd", 2017, "IA"));
  writer.writeRecord(Record (111111111, "richards", 2022, "CO"));
  writer.writeRecord(Record (111421317, "stuff", 2028, "AL"));
  writer.writeRecord(Record (111421317, "stuff", 2028, "AL"));
  writer.writeRecord(Record (111421317, "stuff", 2028, "AL"));
  writer.writeRecord(Record (111421317, "stuff", 2028, "AL"));
  writer.writeRecord(Record (987654322, "backman", 2012, "CA"));
  writer.writeRecord(Record (987654321, "stone", 1999, "MN"));
  writer.writeRecord(Record (555555555, "shepherd", 2017, "IA"));
  writer.writeRecord(Record (111111111, "richards", 2022, "CO"));
  writer.writeRecord(Record (987654321, "stone", 1999, "MN"));
  writer.writeRecord(Record (555555555, "shepherd", 2017, "IA"));
  writer.writeRecord(Record (111111111, "richards", 2022, "CO"));
  writer.writeRecord(Record (111421317, "stuff", 2028, "AL"));
  writer.writeRecord(Record (111421317, "stuff", 2028, "AL"));
  writer.writeRecord(Record (111421317, "stuff", 2028, "AL"));
  writer.writeRecord(Record (111421317, "stuff", 2028, "AL"));
  writer.writeRecord(Record (987654322, "backman", 2012, "CA"));
  writer.writeRecord(Record (987654321, "stone", 1999, "MN"));
  writer.writeRecord(Record (555555555, "shepherd", 2017, "IA"));
  writer.writeRecord(Record (111111111, "richards", 2022, "CO"));
  writer.writeRecord(Record (987654321, "stone", 1999, "MN"));
  writer.writeRecord(Record (555555555, "shepherd", 2017, "IA"));
  writer.writeRecord(Record (111111111, "richards", 2022, "CO"));
  writer.writeRecord(Record (111421317, "stuff", 2028, "AL"));
  writer.writeRecord(Record (111421317, "stuff", 2028, "AL"));
  writer.writeRecord(Record (111421317, "stuff", 2028, "AL"));
  writer.writeRecord(Record (111421317, "stuff", 2028, "AL"));


  writer.close();

  
  cout << endl;
  cout << "----------------DONE WRITING----------------" << endl;
  cout << endl;


  TaxRecordReader reader("file.data", 64);

  int numBlocks = 0;
  for(vector<Record> page = reader.readPage(); !page.empty(); page = reader.readPage()) {
    cout << "[BLOCK]" << endl;
    for(Record record : page) {
      cout << record << endl;
    }
    numBlocks++;
  }
  reader.close();

  cout << "[" << numBlocks << " blocks read]" << endl;

  return 0;
}

