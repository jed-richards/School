#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cassert>

using namespace std;


// Make a student class
class Student {

  public:
    string fName;
    string lName;
    string year;
    float gpa;

    // Constructor
    Student(string first, string last, string tempYear, float GPA) {
      fName = first;
      lName = last;
      year = tempYear;
      gpa = GPA;
    }

    // Print Student Info Function
    void printInfo() {
      cout << fName << " " << lName << " " << year << " " <<  gpa << endl;
    }

    // Overwrite < operator for sort
    friend bool operator< (const Student& a, const Student& b) {
      return (a.gpa > b.gpa);
    }

};


// Print function
void printData(vector<Student> list) {

  for (Student a : list) {
    a.printInfo();
  }

}


// Average GPA function
float computeAverageGPA(vector<Student> list) {

  float temp = 0;

  for (auto student : list) {
    temp += student.gpa;
  }

  return temp/list.size();

}


// getTopK function
vector<Student> getTopK(vector<Student> list, int k) {
 
  assert(k >= 0);

  // Sort user defined vector with overwritten operator
  sort(list.begin(), list.end());

  if (k > list.size()) {
    vector<Student> tempList = {list.begin(), list.end()};
    return tempList;
  }
  else {
    vector<Student> tempList = {list.begin(), list.begin() + k};
    return tempList;
  }

  // Lambda function to sort with defined function
  //sort(tempList.begin(), tempList.end(), [](Student a, Student b) {
  //  return a.gpa > b.gpa;
  //});

}


// getTopKYear function
vector<Student> getTopKYear(vector<Student> list, int k, string year) {

  vector<Student> tempList = list;
  
  // Remove if will shift all elements of a given vector to the front of the vector and return an integer value to the number of elements that were moved.
  // Then, we use the erase function to erase that number of elements from the first element.
  tempList.erase(remove_if(
                  tempList.begin(),
                  tempList.end(),
                  [year](Student a) {return (a.year != year);}
                ),
                tempList.end()
  );

  return (getTopK(tempList,k)); 
}


int main() {

  // Make Vector of Students
  vector<Student> studentList;

  // Read From gradebook.txt file
  ifstream fin("gradebook_2.txt");

  string fName;
  string lName;
  string year;
  float gpa;

  while (fin >> fName >> lName >> year >> gpa) {
    Student student(fName, lName, year, gpa); 
    studentList.push_back(student);
  }

  // Print Data 
  printData(studentList);
  cout << endl;

  // Compute Average GPA
  cout << computeAverageGPA(studentList) << endl;
  cout << endl;

  // Call getTopK Function
  vector<Student> topKList = getTopK(studentList, 3);

  // Print Data after getTopK
  printData(topKList);
  cout << endl;

  // Call getTopKYear Function
  vector<Student> topKYearList = getTopKYear(studentList, 3, "Jr");

  // Print Data after getTopK
  printData(topKYearList);

  return 0;

}
