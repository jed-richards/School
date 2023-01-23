#ifndef JOIN_H
#define JOIN_H

#include "Operator.h"

class Join : public Operator {
  public:
    Join(Operator *op1, Operator *op2, string pAttr1, string pAttr2) {
      // Implement this
    }
    Join(Operator *op, string fileName, string pAttr1, string pAttr2) {
      // Implement this
    }

    Join(string fileName1, string fileName2, string pAttr1, string pAttr2) {
      // Implement this FIRST
      //
      // for (vector<Record> page1 : fileName1) {
      //   for (vector<Record> page2 : fileName1) 
    }

    void open() {
      // Implement this
    }

    vector<Record> next() {
      vector<Record> outPage;
      // Implement this
      return outPage;
    }

    void close() {
      // Implement this
    }
};


#endif
