#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

// outputs the number of strings in the vector passed to the function
void word_count(vector<string> v) {
  cout << v.size() << endl;
}

// outputs the number of distinct number of strings in the vector passed
void distinct_words(vector<string> v) {
  set<string> distinctWords;
  for (auto word : v) {
    distinctWords.insert(word);
  }
  cout << distinctWords.size() << endl;
}

// outputs the top ten words in the vector along with how many times they are in the vector
void top10_words(vector<string> v) {
  map<string,int> wordCount;
  for (auto word : v) {
    wordCount[word]++;
  }
  for (int i=0; i<10; i++) { 
    int currNum = 0;
    string currWord;
    for (auto [word,count] : wordCount) {
      if (count > currNum) {
        currNum = count;
        currWord = word;
      }
    }
    wordCount.erase(currWord);
    cout << currWord << ": " << currNum << endl;
  }
}

// outputs the length of the strings and the count of how many strings of that number
void word_lengths(vector<string> v) {
  map<int,int> wordLengthCount;
  for (auto word : v) {
    int length = word.size();
    wordLengthCount[length]++;
  }
  for (auto count : wordLengthCount) {
    cout << count.first << ": " << count.second << endl;
  }
}

// outputs the length of the distinct strings and how many strings had that same length
void word_lengths_distinct(vector<string> v) {
  set<string> distinctSet;
  map<int,int> distinctMap;
  for (auto word : v) {
    distinctSet.insert(word);
  }
  for (auto word : distinctSet) {
    int length = word.size();
    distinctMap[length]++;
  }
  for (auto count : distinctMap) {
    cout << count.first << ": " << count.second << endl;
  }
}

// outputs the distinct strings that have length of 16
void words_of_length_16(vector<string> v) {
  set<string> distinctWordLength;
  for (auto word : v) {
    if (word.size() == 16)
      distinctWordLength.insert(word);
  }
  for (auto word : distinctWordLength)
    cout << word << endl;
}

void words_with_most_repeating_letters(vector<string> v) {

  set<string> distinctWords;
  for (auto word : v) {
    distinctWords.insert(word);
  }

  map<string,map<char,int>> wordLetterCount;
  for (auto word : distinctWords) {
    wordLetterCount[word];
    for (int i=0; i < word.size(); i++) {
      char letter = word[i];
      wordLetterCount.at(word)[letter]++;
    }
  }
 
  char maxLetter;
  int maxCount = 0;
  for (auto [word, charMap] : wordLetterCount) {
    for (auto [character, count] : charMap) {
      if (count > maxCount) {
        maxCount = count;
        maxLetter = character;
      }
    }
  }

  // This gets s with the max count of 5
  //cout << maxLetter << endl;
  //cout << maxCount << endl;

  for (auto [word, charMap] : wordLetterCount) {
    for (auto [character, count] : charMap) {
      if (character == maxLetter && count == maxCount) {
        cout << word << endl; 
      }
    }
  }

}

int main() {

  ifstream fin("/courses/cmsc182/hw_7/crime_and_punishment.txt");
  vector<string> words;

  string word;
  while(fin >> word)
    words.push_back(word);

  cout << "Ex2.1" << endl;
  word_count(words);
  cout << endl;

  cout << "Ex2.2" << endl;
  distinct_words(words);
  cout << endl;

  cout << "Ex2.3" << endl;
  top10_words(words);
  cout << endl;

  cout << "Ex2.4" << endl;
  word_lengths(words);
  cout << endl;

  cout << "Ex2.5" << endl;
  word_lengths_distinct(words);
  cout << endl;

  cout << "Ex2.5" << endl;
  words_of_length_16(words); 
  cout << endl;

  cout << "Ex2.6" << endl;
  words_with_most_repeating_letters(words);
  cout << endl;

  return 0;
}
