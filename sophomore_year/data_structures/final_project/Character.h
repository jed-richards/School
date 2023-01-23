// This header file contains the Character class. 

// Creator: Jed Richards
// Date Created: 4/25/2022
// Last updated: 4/29/2022

#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;


class Character {

  public:

    string characterName;
    string currentLocation;
    int currentHealth;
    unordered_set<string> inventory; 

    // Constructor that takes in characters name, starting location, starting health, starting inventory
    Character(string name, string location, int health, unordered_set<string> inv) {
      characterName = name;
      currentLocation = location;
      currentHealth = health;
      inventory = inv;
    }

    // Member function that allows to print out the characters current inventory
    void printInv() {
      cout << "Your Inventory: " << endl;
      for (string item : inventory) {
        cout << "  " << item << endl;
      }
    }

    // Member function that returns the characters current health
    int getHealth() {
      return currentHealth;
    }

    // Member function that returns the characters current location
    string getLocation() {
      return currentLocation;
    }

    // Returns the character name
    string getName() {
      return characterName;
    }

    // Member function that allows the user to change the charaters name
    void getCharacterName() {
      cout << "Enter your character's name: " << endl;
      string newName;
      getline(cin, newName);
      characterName = newName;
      cout << endl;
      cout << "Hello " << newName << endl;
    }


};






