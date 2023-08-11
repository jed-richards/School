#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

void sum(vector<int> v) {
  int sum = 0;
  for (int i=0; i<v.size(); i++) {
    sum += v[i];
  }
  cout << sum << endl;
}

void max(vector<int> v) {
  sort(v.begin(), v.end());
  cout << v.back() << endl;
}

void smallest_sum(vector<int> v) {
  sort(v.begin(), v.end());
  int smallSum = (v[0] + v[1]);
  cout << smallSum << endl;
}

void smallest_difference(vector<int> v) {
  sort(v.begin(), v.end());
  int smallDiff = v.back()*2;  // initialize a number that is greater than any number in the vector 
  for (int i=0; i<v.size()-1; i++) {
    int tempDiff = v[i+1]-v[i];
    if (tempDiff < smallDiff) {
      smallDiff = tempDiff;
    }
  }
  cout << smallDiff << endl;
}

void count_even(vector<int> v) {
  int evenCount = 0;
  for (auto number : v) {
    if (number%2 == 0) {
      evenCount++;
    }
  }
  cout << evenCount << endl;
}

void count_distinct(vector<int> v) {
  map<int,int> numberCount;
  for (auto number : v) {
    numberCount[number] += 1;
  }
  cout << numberCount.size() << endl;
}

void digit_counts(vector<int> v) {
  map<int,int> digitCount;
  for (auto number : v) {
    while (number != 0) {
      int digit = number%10;
      digitCount[digit]++;
      number = number/10;
    }
  }
  // print out 
  for (auto [digit,count] : digitCount) {
    cout << digit << ": " << count << endl;
  }
}

int main() {

  ifstream fin("/courses/cmsc182/hw_7/numbers.txt");
  vector<int> numbers;

  int num;
  while(fin >> num)
    numbers.push_back(num);
  
  sum(numbers);
  max(numbers);
  smallest_sum(numbers);
  smallest_difference(numbers);
  count_even(numbers);
  count_distinct(numbers);
  digit_counts(numbers);

  return 0;
}
