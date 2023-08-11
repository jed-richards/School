#pragma once
#include <iostream>
#include "sqlFunctions.h"
using namespace std;


void printOptions() {
  cout << "---------------------------------------------------------" << endl;
  cout << "Here are our app's options. What would you like to do?" << endl;
  cout << "1 - Look at information" << endl;
  cout << "2 - Add information" << endl;
  cout << "3 - Update information" << endl;
  cout << "4 - Delete information" << endl;
  cout << "0 - Exit app" << endl;
  cout << "---------------------------------------------------------" << endl;
}

void printSelectFunctions() {
  cout << "---------------------------------------------------------" << endl;
  cout << "What option do you want to use?" << endl;
  cout << "1 - Team names and the number of bots they have built" << endl;
  cout << "2 - List of team names with the teams members" << endl;
  cout << "---------------------------------------------------------" << endl;
}

void printTables() {
  cout << "1 - Members" << endl;
  cout << "2 - Teams" << endl;
  cout << "3 - Robots" << endl;
  cout << "4 - Events" << endl;
  cout << "---------------------------------------------------------" << endl;
}

void printSelectTables() {
  cout << "1 - Members" << endl;
  cout << "2 - Teams" << endl;
  cout << "3 - Robots" << endl;
  cout << "4 - Events" << endl;
  cout << "5 - Special Options" << endl;
  cout << "---------------------------------------------------------" << endl;
}
void printMemberColumns(){
  cout << "1 - Member IDs" << endl;
  cout << "2 - Member Names" << endl;
  cout << "3 - Team IDs" << endl;
  cout << "0 - All Information" << endl;
  cout << "---------------------------------------------------------" << endl;
}

void printMemberColumnsUD(){  //update/delete
  cout << "1 - Member IDs" << endl;
  cout << "2 - Member Names" << endl;
  cout << "3 - Team IDs" << endl;
  cout << "---------------------------------------------------------" << endl;
}

void printTeamColumns(){
  cout << "1 - Team IDs" << endl;
  cout << "2 - Team Names" << endl;
  cout << "0 - All Information" << endl;
  cout << "---------------------------------------------------------" << endl;
}

void printTeamColumnsUD(){
  cout << "1 - Team IDs" << endl;
  cout << "2 - Team Names" << endl;
  cout << "---------------------------------------------------------" << endl;
}

void printRobotColumns(){
  cout << "1 - Robot IDs" << endl;
  cout << "2 - Robot Names" << endl;
  cout << "3 - Years Robots Were Built" << endl;
  cout << "4 - Team IDs" << endl;
  cout << "5 - Event IDs" << endl;
  cout << "0 - All Information" << endl;
  cout << "---------------------------------------------------------" << endl;
}

void printRobotColumnsUD(){
  cout << "1 - Robot IDs" << endl;
  cout << "2 - Robot Names" << endl;
  cout << "3 - Years Robots Were Built" << endl;
  cout << "4 - Team IDs" << endl;
  cout << "5 - Event IDs" << endl;
  cout << "---------------------------------------------------------" << endl;
}

void printEventColumns(){
  cout << "1 - Event IDs" << endl;
  cout << "2 - Event Names" << endl;
  cout << "3 - Years of Events" << endl;
  cout << "0 - All Information" << endl;
  cout << "---------------------------------------------------------" << endl;
}

void printEventColumnsUD(){
  cout << "1 - Event IDs" << endl;
  cout << "2 - Event Names" << endl;
  cout << "3 - Years of Events" << endl;
  cout << "---------------------------------------------------------" << endl;
}

// This function is used periodically below to get user input
int getChoice() {
  cout << endl;
  int choice;
  cin >> choice;
  return choice;
}

// This function prints and runs all things dealing with a select query
void printSelectOptions() {
  cout << "---------------------------------------------------------" << endl;
  cout << "What information do you want to look at?" << endl;
  printSelectTables();
  int choice1 = getChoice();
  int choice2;
  string attr;
  string table;

  if (choice1 == 1) {      // members
    table = "members";
    cout << "---------------------------------------------------------" << endl;
    cout << "What specific information do you want to look at?" << endl;
    printMemberColumns();
    choice2 = getChoice();
    if (choice2 == 1) {
      attr = "memberid";
    }
    else if (choice2 == 2) {
      attr = "membername";
    }
    else if (choice2 == 2) {
      attr = "teamid";
    }
    else if (choice2 == 0) {
      attr = "*";
    }
  }
  else if (choice1 == 2) { // teams
    table = "teams";
    cout << "---------------------------------------------------------" << endl;
    cout << "What specific information do you want to look at?" << endl;
    printTeamColumns();
    choice2 = getChoice();
    if (choice2 == 1) {
      attr = "teamid";
    }
    else if (choice2 == 2) {
      attr = "teamname";
    }
    else if (choice2 == 0) {
      attr = "*";
    }
  }
  else if (choice1 == 3) { // robots
    table = "robots";
    cout << "---------------------------------------------------------" << endl;
    cout << "What specific information do you want to look at?" << endl;
    printRobotColumns();
    choice2 = getChoice();
    if (choice2 == 1) {
      attr = "robotid";
    }
    else if (choice2 == 2) {
      attr = "robotname";
    }
    else if (choice2 == 3) {
      attr = "yearbuilt";
    }
    else if (choice2 == 4) {
      attr = "teamid";
    }
    else if (choice2 == 5) {
      attr = "eventid";
    }
    else if (choice2 == 0) {
      attr = "*";
    }
  }
  else if (choice1 == 4) { // events
    table = "events";
    cout << "---------------------------------------------------------" << endl;
    cout << "What specific information do you want to look at?" << endl;
    printEventColumns();
    choice2 = getChoice();
    if (choice2 == 1) {
      attr = "eventid";
    }
    else if (choice2 == 2) {
      attr = "eventname";
    }
    else if (choice2 == 3) {
      attr = "eventyear";
    }
    else if (choice2 == 0) {
      attr = "*";
    }
  }

  else if (choice1 == 5) { // special functions
    printSelectFunctions();
    choice2 = getChoice();
    if (choice2 == 1) {
      cout << "Here is the data you requested." << endl;
      select1();
      return;
    }
    else if (choice2 == 2) {
      cout << "Here is the data you requested." << endl;
      select2();
      return;
    }
  }
  
  cout << "Here is the data you requested." << endl;

  select(attr, table);
}

// This function prints and runs all things dealing with an insert query
void printInsertOptions() {
  cout << "---------------------------------------------------------" << endl;
  cout << "What type of information would you like to add?" << endl;
  printTables();
  int choice1 = getChoice();
  string value;
  string table;

  if (choice1 == 1) {      // Members
    table = "members";
    string mID, mName, tID;
    cout << "Input new member's ID: " << endl;
    cin >> ws;  // white space
    getline(cin, mID);
    cout << "Input new member's name: " << endl;
    getline(cin, mName);
    cout << "Input new member's team ID: " << endl;
    getline(cin, tID);
    value = "'" + mID + "', '" + mName + "', '" + tID + "'";
  }
  else if (choice1 == 2) { // Teams
    table = "teams";
    string tID, tName;
    cout << "Input new team's ID: " << endl;
    cin >> ws;
    getline(cin, tID);
    cout << "Input new team's name: " << endl;
    getline(cin, tName);
    value = "'" + tID + "', '" + tName + "'";
  }
  else if (choice1 == 3) { // Robots
    table = "robots";
    string rID, rName, yearBuilt, tID, eID;
    cout << "Input new robot's ID: " << endl;
    cin >> ws;
    getline(cin, rID);
    cout << "Input new robot's name: " << endl;
    getline(cin, rName);
    cout << "Enter the year the robot was built: " << endl;
    cin >> yearBuilt;
    cout << "Enter the team ID of the team that built the robot: " << endl;
    cin >> ws;
    getline(cin, tID);
    cout << "If the robot has particpated in an event enter the event ID. Otherwise enter: none" << endl;
    getline(cin, eID);
    if (eID == "none") {
      eID = "NULL";
      value = "'" + rID + "', '" + rName + "', '" + yearBuilt + "', '" + tID + "', "  + eID;
    }
    else {
      value = "'" + rID + "', '" + rName + "', '" + yearBuilt + "', '" + tID + "', '" + eID + "'";
    }
  }
  else if (choice1 == 4) { // Events
    table = "events";
    string eID, eName, eYear;
    cout << "Input new event's ID: " << endl;
    cin >> eID;
    cout << "Input new event's name: " << endl;
    cin >> ws;
    getline(cin, eName);
    cout << "Input the year the event took place: " << endl;
    cin >> eYear;
    value = "'" + eID + "', '" + eName + "', '" + eYear + "'";
  }
  
  insert(table, value);
}

// This function prints and runs all things dealing with an update query
void printUpdateOptions() {
  cout << "---------------------------------------------------------" << endl;
  cout << "What type of information would you like to update?" << endl;
  printTables();
  int choice1 = getChoice();
  int choice2;
  string attr;
  string table;
  string oldValue;
  string newValue;

  if (choice1 == 1) {      // members
    table = "members";
    cout << "---------------------------------------------------------" << endl;
    cout << "What specific information would you like to update?" << endl;
    printMemberColumnsUD();
    choice2 = getChoice();
    if (choice2 == 1) {
      attr = "memberid";
    }
    else if (choice2 == 2) {
      attr = "membername";
    }
    else if (choice2 == 2) {
      attr = "teamid";
    }
    cout << "Enter the value to be changed: " << endl;
    cin >> ws;
    getline(cin, oldValue);
    cout << "Enter the new value: " << endl;
    getline(cin, newValue);
  }
  else if (choice1 == 2) { // teams
    table = "teams";
    cout << "---------------------------------------------------------" << endl;
    cout << "What specific information would you like to update?" << endl;
    printTeamColumnsUD();
    choice2 = getChoice();
    if (choice2 == 1) {
      attr = "teamid";
    }
    else if (choice2 == 2) {
      attr = "teamname";
    }
    cout << "Enter the value to be changed: " << endl;
    cin >> ws;
    getline(cin, oldValue);
    cout << "Enter the new value: " << endl;
    getline(cin, newValue);
  }
  else if (choice1 == 3) { // robots
    table = "robots";
    cout << "---------------------------------------------------------" << endl;
    cout << "What specific information would you like to update?" << endl;
    printRobotColumnsUD();
    choice2 = getChoice();
    if (choice2 == 1) {
      attr = "robotid";
    }
    else if (choice2 == 2) {
      attr = "robotname";
    }
    else if (choice2 == 3) {
      attr = "yearbuilt";
    }
    else if (choice2 == 4) {
      attr = "teamid";
    }
    else if (choice2 == 5) {
      attr = "eventid";
    }
    cout << "Enter the value to be changed: " << endl;
    cin >> ws;
    getline(cin, oldValue);
    cout << "Enter the new value: " << endl;
    getline(cin, newValue);
  }
  else if (choice1 == 4) { // events
    table = "events";
    cout << "---------------------------------------------------------" << endl;
    cout << "What specific information would you like to update?" << endl;
    printEventColumnsUD();
    choice2 = getChoice();
    if (choice2 == 1) {
      attr = "eventid";
    }
    else if (choice2 == 2) {
      attr = "eventname";
    }
    else if (choice2 == 3) {
      attr = "eventyear";
    }
    cout << "Enter the value to be changed: " << endl;
    cin >> ws;
    getline(cin, oldValue);
    cout << "Enter the new value: " << endl;
    getline(cin, newValue);
  }
  
  update(table, attr, oldValue, newValue);
}

// This function prints and runs all things dealing with a delete query
void printDeleteOptions() {
  cout << "---------------------------------------------------------" << endl;
  cout << "What type of information would you like to delete?" << endl;
  printTables();
  int choice1 = getChoice();
  int choice2;
  string attr;
  string table;
  string value;

  if (choice1 == 1) {      // members
    table = "members";
    cout << "---------------------------------------------------------" << endl;
    cout << "What specific information would you like to delete?" << endl;
    printMemberColumnsUD();
    choice2 = getChoice();
    if (choice2 == 1) {
      attr = "memberid";
    }
    else if (choice2 == 2) {
      attr = "membername";
    }
    else if (choice2 == 2) {
      attr = "teamid";
    }
    cout << "Enter the value to be deleted: " << endl;
    cin >> ws;
    getline(cin, value);
  }
  else if (choice1 == 2) { // teams
    table = "teams";
    cout << "---------------------------------------------------------" << endl;
    cout << "What specific information would you like to delete?" << endl;
    printTeamColumnsUD();
    choice2 = getChoice();
    if (choice2 == 1) {
      attr = "teamid";
    }
    else if (choice2 == 2) {
      attr = "teamname";
    }
    cout << "Enter the value to be deleted: " << endl;
    cin >> ws;
    getline(cin, value);
  }
  else if (choice1 == 3) { // robots
    table = "robots";
    cout << "---------------------------------------------------------" << endl;
    cout << "What specific information would you like to delete?" << endl;
    printRobotColumnsUD();
    choice2 = getChoice();
    if (choice2 == 1) {
      attr = "robotid";
    }
    else if (choice2 == 2) {
      attr = "robotname";
    }
    else if (choice2 == 3) {
      attr = "yearbuilt";
    }
    else if (choice2 == 4) {
      attr = "teamid";
    }
    else if (choice2 == 5) {
      attr = "eventid";
    }
    cout << "Enter the value to be deleted: " << endl;
    cin >> ws;
    getline(cin, value);
  }
  else if (choice1 == 4) { // events
    table = "events";
    cout << "---------------------------------------------------------" << endl;
    cout << "What specific information would you like to delete?" << endl;
    printEventColumnsUD();
    choice2 = getChoice();
    if (choice2 == 1) {
      attr = "eventid";
    }
    else if (choice2 == 2) {
      attr = "eventname";
    }
    else if (choice2 == 3) {
      attr = "eventyear";
    }
    cout << "Enter the value to be deleted: " << endl;
    cin >> ws;
    getline(cin, value);
  }
  
  delete_(table, attr, value);
}

// This function is the main function that operates based on user input
void printChoiceOptions() {
  printOptions();
  int choice = getChoice();
  if (choice == 1) {      // Select
    printSelectOptions(); 
  }
  else if (choice == 2) { // Insert
    printInsertOptions();
  }
  else if (choice == 3) { // Update
    printUpdateOptions();
  }
  else if (choice == 4) { // Delete
    printDeleteOptions();
  }
  else if (choice == 0) { // End program
    cout << "Thank you for using our app." << endl;
    exit(0);
  }
  else {
    cout << choice << " is not an option. Please select again." << endl;
    printChoiceOptions();
  }
}
