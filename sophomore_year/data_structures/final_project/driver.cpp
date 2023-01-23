// This is the driver for the game. It includes all the header files.
// This is where the game loop happens.

// Creator: Jed Richards
// Date Created: 4/25/2022
// Last updated: 4/29/2022

// Compile with g++ -std=c++20 filename.cpp

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "Item.h"
#include "Room.h"
#include "Character.h"
#include "Functions.h"


using namespace std;

// Vector of functions
vector<string> helpList {
  "help",   
  "look",  
  "bag or inventory", 
  "go to *location*",
  "take *item*",    
  "drop *item* or drop all",   
  "quit or exit", 
};

// Help function
void getHelp() {
  for (auto func : helpList) {
    cout << func << endl;
  }
}

// Function to get the command of the user
string getCommand() {
  string command;
  cout << "Enter a command: " << endl;
  getline(cin,command);
  return command;
}

// Function to be true or false to run the game until all items are in the Lobby
bool solved() {
  if (Rooms.at("Lobby").roomItems.size() == 10) {
    cout << endl;
    cout << "You solved the case!" << endl;
    cout << "Thanks for playing! Major upgrades coming over Summer 2022!" << endl;
    return true;
  }
  else {
    return false;
  }
}


// main code
int main() {

  // Allows the player to enter there own name
  player.getCharacterName();

  // Setting
  cout << "You have been brought to this mansion to look for clues. You are to look for" << endl;
  cout << "clues that may lead us to find the real suspect that murdered Mr. Stoherdman." << endl;
  cout << "You must bring whatever clues to me here in the Lobby. Get on it! We have a" << endl;
  cout << "murderer to catch." << endl;

  cout << endl;
  cout << "How to Play: " << endl;
  getHelp();
  cout << endl;


  // Orient the player 
  look();

  while (!solved()) {
    
    cout << endl;
    string command = getCommand(); 
    cout << endl;
    
    if (command.starts_with("hello")) {
      cout << "Hello friend! Thanks for playing my game!" << endl;
    }
    else if (command == "look") {
      look();
    }
    else if (command == "bag" || command == "inventory") {
      player.printInv(); 
    }
    else if (command.starts_with("take")) {
      string item = command.substr(5,(command.size()-1));
      take(item);
    }
    else if (command.starts_with("drop")) {
      string item = command.substr(5,(command.size()-1));
      drop(item);
    }
    else if (command.starts_with("go to")) {
      string newLocation = command.substr(6,(command.size()-1));
      move(newLocation);
      look();
    }
    else if (command == "help") {
      getHelp();
    }
    else if (command == "exit" || command == "quit") {
      break;
    }
    else {
      cout << "I don't know that command. Try again." << endl;
    }

    cout << "-----------------------------------------------------------" << endl;

  }


  return 0;
}
