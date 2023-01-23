#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;


// Make a student class
class Student {

  public:
    string fName;
    string lName;
    float gpa;

    // Constructor
    Student(string first, string last, float GPA) {
      fName = first;
      lName = last;
      gpa = GPA;
    }

    // Print Student Info Function
    void printInfo() {
      cout << fName << " " << lName << " " << gpa << endl;
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
 
  // I wrote this if statement as a check in case the use asked for a negative number or 0, but I get a warning because I am not returning anything of type vector<Student>
  if (k <= 0) {
    cout << "Sorry, you can't do that." << endl;
  }
  else {
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
}


int main() {

  // Make Vector of Students
  vector<Student> studentList;

  // Read From gradebook.txt file
  ifstream fin("gradebook.txt");

  string fName;
  string lName;
  float gpa;

  while (fin >> fName >> lName >> gpa) {
    Student student(fName, lName, gpa); 
    studentList.push_back(student);
  }

  // Print Data 
  printData(studentList);

  // Compute Average GPA
  cout << computeAverageGPA(studentList) << endl;
  
  // Call getTopK Function
  vector<Student> topKList = getTopK(studentList, 3);

  // Print Data after getTopK
  printData(topKList);

  return 0;

}
