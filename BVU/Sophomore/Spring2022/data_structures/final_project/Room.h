// This file contains the Room class and the global variables
// to initialize the Room objects in the Functions.h header file.

// Creator: Jed Richards
// Date Created: 4/25/2022
// Last updated: 4/29/2022

#pragma once

#include <iostream>
#include <vector>
#include <unordered_map> 
#include <unordered_set>

using namespace std;

class Room {

  // I made all variables public that way I could access them 
  // and change them directly throughout the other files.
  public:

    // Each room will have string for the name and description. 
    // Each room will also have two unordered sets of strings 
    // containing the rooms exits and the items within the room. 
    string roomName;
    string roomDesc;
    unordered_set<string> roomExits;  
    unordered_set<string> roomItems;

    // Room constuctor
    Room(string name, string desc, unordered_set<string> exits, unordered_set<string> items) {
      roomName = name;
      roomDesc = desc;
      roomExits = exits;
      roomItems = items;
    }

    // This functions prints out the room's details when called.
    void getRoomDetails() {
      //cout << "Room Details: " << endl;
      //cout << "Name: " << roomName << endl;
      cout << "Description: " << roomDesc << endl;
      cout << "Room's Exits:  ";
      for (string room : roomExits) {
        cout << room << " | ";  
      }
      cout << endl;
      cout << "Room's Items:  ";
      for (string item : roomItems) {
        cout << item << " | "; 
      }
      cout << endl;
    }


};


// All of the below code pre-allocates the global room data variables
// so they can be accessed in the Functions.h file with ease.

// Room Names    
string room1Name  = "Lobby";
string room2Name  = "Hall";
string room3Name  = "Lounge";
string room4Name  = "Dining Room";
string room5Name  = "Kitchen";
string room6Name  = "Ballroom";
string room7Name  = "Conservatory";
string room8Name  = "Billiard Room";
string room9Name  = "Library";
string room10Name = "Study";


// Room Descriptions
string room1Desc  = "Lobby Desc";
string room2Desc  = "Hall Desc";
string room3Desc  = "Lounge Desc";
string room4Desc  = "Dining Room Desc";
string room5Desc  = "Kitchen Desc";
string room6Desc  = "Ballroom Desc";
string room7Desc  = "Conservatory Desc";
string room8Desc  = "Billiard Room Desc";
string room9Desc  = "Library Desc";
string room10Desc = "Study Desc";


// Room Exits
unordered_set<string> room1Exits  = {room2Name, room4Name, room6Name, room8Name, room9Name};
unordered_set<string> room2Exits  = {room1Name, room3Name, room10Name};
unordered_set<string> room3Exits  = {room2Name, room4Name, room7Name};
unordered_set<string> room4Exits  = {room1Name, room3Name, room5Name};
unordered_set<string> room5Exits  = {room4Name, room6Name, room10Name};
unordered_set<string> room6Exits  = {room1Name, room5Name, room7Name};
unordered_set<string> room7Exits  = {room3Name, room6Name, room8Name};
unordered_set<string> room8Exits  = {room1Name, room7Name, room9Name};
unordered_set<string> room9Exits  = {room1Name, room8Name, room10Name};
unordered_set<string> room10Exits = {room2Name, room5Name, room9Name};


// Room Items
unordered_set<string> room1Items;
unordered_set<string> room2Items = {"Candle Stick"};
unordered_set<string> room3Items = {"Cheese and Crackers"};
unordered_set<string> room4Items = {"Shark Fin Soup", "Cake"};
unordered_set<string> room5Items = {"Chicken", "Dagger"};
unordered_set<string> room6Items;
unordered_set<string> room7Items = {"Rope", "Wrench"};
unordered_set<string> room8Items = {"Lead Pipe"};
unordered_set<string> room9Items; 
unordered_set<string> room10Items = {"Revolver"};
