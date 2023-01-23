// This file contains the Functions that will be used in the 
// driver.cpp file. It also creates some global variables that
// will be used in the driver.cpp file.

// Creator: Jed Richards
// Date Created: 4/25/2022
// Last updated: 5/3/2022

#pragma once

#include <iostream>
#include <vector>
#include <unordered_map> 
#include <unordered_set>
#include "Character.h"
#include "Item.h"
#include "Room.h"

using namespace std;



//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// Create Rooms Function ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
                                                                                    // 
// This is a function to create instances of the Room class and store               //  
// them in a unordered_map to be accessed globally. The key is a string             //
// corresponding to the rooms name. The value is a Room object corresponding        //
// to the room.                                                                     //
                                                                                    //
unordered_map<string,Room> createRooms() {                                          //
                                                                                    //
  // This creates the unordered map and names it Rooms                              //
  unordered_map<string,Room> Rooms;                                                 //
                                                                                    //
  // Construct the room objects                                                     //
  Room room1(room1Name, room1Desc, room1Exits, room1Items);                         //
  Room room2(room2Name, room2Desc, room2Exits, room2Items);                         //
  Room room3(room3Name, room3Desc, room3Exits, room3Items);                         //
  Room room4(room4Name, room4Desc, room4Exits, room4Items);                         //
  Room room5(room5Name, room5Desc, room5Exits, room5Items);                         //
  Room room6(room6Name, room6Desc, room6Exits, room6Items);                         //
  Room room7(room7Name, room7Desc, room7Exits, room7Items);                         //
  Room room8(room8Name, room8Desc, room8Exits, room8Items);                         //
  Room room9(room9Name, room9Desc, room9Exits, room9Items);                         //
  Room room10(room10Name, room10Desc, room10Exits, room10Items);                    //
                                                                                    //
  // Insert the roomName and the room objects to the Rooms unordered map            //  
  Rooms.insert({room1Name, room1});                                                 //
  Rooms.insert({room2Name, room2});                                                 //  
  Rooms.insert({room3Name, room3});                                                 //  
  Rooms.insert({room4Name, room4});                                                 //
  Rooms.insert({room5Name, room5});                                                 //
  Rooms.insert({room6Name, room6});                                                 //
  Rooms.insert({room7Name, room7});                                                 //
  Rooms.insert({room8Name, room8});                                                 //
  Rooms.insert({room9Name, room9});                                                 //
  Rooms.insert({room10Name, room10});                                               //
                                                                                    //
  // Finally return the unordered map so that it will be a global variable able to  //
  // be accessed after the createRooms function is called.                          //
  return Rooms;                                                                     //
                                                                                    //
}                                                                                   //
                                                                                    //
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// Create Items Function ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
                                                                                    // 
// This is a function to create instances of the Room class and store               //  
// them in a unordered_map to be accessed globally. The key is a string             //
// corresponding to the rooms name. The value is a Room object corresponding        //
// to the room.                                                                     //
                                                                                    //
unordered_map<string,Item> createItems() {                                          //
                                                                                    //
  // This creates the unordered map and names it Rooms                              //
  unordered_map<string,Item> Items;                                                 //
                                                                                    //
  // Construct the room objects                                                     //
  Item item1(item1Name, item1Type, item1Desc, item1Damage, item1Heal);              //
  Item item2(item2Name, item2Type, item2Desc, item2Damage, item2Heal);              //
  Item item3(item3Name, item3Type, item3Desc, item3Damage, item3Heal);              //
  Item item4(item4Name, item4Type, item4Desc, item4Damage, item4Heal);              //
  Item item5(item5Name, item5Type, item5Desc, item5Damage, item5Heal);              //
  Item item6(item6Name, item6Type, item6Desc, item6Damage, item6Heal);              //
  Item item7(item7Name, item7Type, item7Desc, item7Damage, item7Heal);              //
  Item item8(item8Name, item7Type, item8Desc, item8Damage, item8Heal);              //
  Item item9(item9Name, item9Type, item9Desc, item9Damage, item9Heal);              //
  Item item10(item10Name, item10Type, item10Desc, item10Damage, item10Heal);        //
                                                                                    //
  // Insert the roomName and the room objects to the Rooms unordered map            //  
  Items.insert({item1Name, item1});                                                 //
  Items.insert({item2Name, item2});                                                 //  
  Items.insert({item3Name, item3});                                                 //  
  Items.insert({item4Name, item4});                                                 //
  Items.insert({item5Name, item5});                                                 //
  Items.insert({item6Name, item6});                                                 //
  Items.insert({item7Name, item7});                                                 //
  Items.insert({item8Name, item8});                                                 //
  Items.insert({item9Name, item9});                                                 //
  Items.insert({item10Name, item10});                                               //
                                                                                    //
  // Finally return the unordered map so that it will be a global variable able to  //
  // be accessed after the createRooms function is called.                          //
  return Items;                                                                     //
                                                                                    //
}                                                                                   //
                                                                                    //
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// Create Player Function //////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
                                                                                    //
// This function allows the creation of the player with a temporary                 //
// name, the player's starting location, health, and inventory                      //
                                                                                    //
Character createPlayer() {                                                          //
  unordered_set<string> inv;                                                        //
  Character player("Name", "Lobby", 10, inv);                                       //
  return player;                                                                    //
}                                                                                   //
                                                                                    //
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////
/////////////////////// Initialize Player, Items and Rooms ///////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
                                                                                    //
// Here, I initialize the global varibles player and Rooms that way they            //
// be accessed in this file and the driver file                                     //
                                                                                    //
Character player = createPlayer();                                                  //
unordered_map<string,Room> Rooms = createRooms();                                   //
unordered_map<string,Item> Items = createItems();                                   //
                                                                                    //
// create enemies here                                                              //
// Character enemy1("EnemyName", "LocationName", health, )                          //
                                                                                    //
                                                                                    //
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// Move Player Function ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
                                                                                    //
// This function will "move" the player to a the specified new location             //
// if the new location is an exit of the players current location.                  //
// If the the new location is not an exit the players location does                 //
// not change.                                                                      //
                                                                                    //
void move(string newLocation) {                                                     //
  string currLocation = player.getLocation();                                       //
  if (Rooms.at(currLocation).roomExits.contains(newLocation)) {                     //
    player.currentLocation = newLocation;                                           //
    cout << "You have moved to: " << newLocation << endl;                           //
  }                                                                                 //
  else {                                                                            //
    cout << newLocation << " is not an exit of " << currLocation << endl;           //
  }                                                                                 //
}                                                                                   //
                                                                                    //
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// Take Item Function //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
                                                                                    //
                                                                                    //
void take(string item) {                                                            //
  string currLocation = player.getLocation();                                       //
  if (Rooms.at(currLocation).roomItems.contains(item)) {                            //
    player.inventory.insert(item);                                                  //
    Rooms.at(currLocation).roomItems.erase(item);                                   //
    cout << "You have picked up: " << item << endl;                                 //
    cout << Items.at(item).itemDesc << endl;                                        //
  }                                                                                 //
  else {                                                                            //
    cout << item  << " is not here." << endl;                                       //
  }                                                                                 //
}                                                                                   //
                                                                                    //
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// Drop Item Function ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
                                                                                                 //
                                                                                                 //
void drop(string item) {                                                                         //
  string currLocation = player.getLocation();                                                    //
  if (player.inventory.contains(item)) {                                                         //
    player.inventory.erase(item);                                                                //
    Rooms.at(currLocation).roomItems.insert(item);                                               //
    cout << "You have dropped the: " << item << endl;                                            //
  }                                                                                              //
  else if (item == "all") {                                                                      //
    if (player.inventory.size() > 0) {                                                           //
      Rooms.at(currLocation).roomItems.insert(player.inventory.begin(), player.inventory.end()); //
      player.inventory.clear();                                                                  //
      cout << "You have dropped all items in your inventory." << endl;                           //
    }                                                                                            //
    else {                                                                                       //
      cout << "You don't have anything in your inventory to drop." << endl;                      //
    }                                                                                            //
  }                                                                                              //
  else {                                                                                         //
    cout << item  << " is not in inventory." << endl;                                            //
  }                                                                                              //
}                                                                                                //
                                                                                                 //
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// Look Function //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
                                                                                    //
// This function prints out the details of the players current location.            //
                                                                                    //
void look() {                                                                       //
  string currLocation = player.getLocation();                                       //
  cout << "You are currently at the " << currLocation << endl;                      //
  Rooms.at(currLocation).getRoomDetails();                                          //
}                                                                                   //
                                                                                    //
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////











