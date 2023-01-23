// This file contains the Item class

// Creator: Jed Richards
// Date Created: 4/25/2022
// Last updated: 4/29/2022

#pragma once

#include <iostream>

using namespace std;


class Item {
  
  private:
    int itemDamage;
    int itemHeal;
    string itemType;

  public:
    string itemName;
    string itemDesc;
    
    // Item constructor
    Item(string type, string name, string desc, int damage, int heal) {
      itemName = name;
      itemType = type;
      itemDesc = desc;
      itemDamage = damage;
      itemHeal = heal;
    }

    // Prints the items details
    void getItemDetails() {
      cout << endl;
      cout << "Item Details: " << endl;
      cout << endl;
      cout << "Name: " << itemName << endl;
      cout << "Type: " << itemType << endl;
      cout << "Description: " << itemType << endl;
      if (itemType == "Weapon") {
        cout << "Damage: " << itemDamage << endl;
      }
      else if (itemType == "Consumable") {
        cout << "Heal: " << itemHeal << endl;
      }
      cout << endl;
    }

    // Returns the integer value of the item's damage
    int getDamage() {
      return itemDamage;
    }

    // Returns the integer value of the item's heal
    int getHeal() {
      return itemHeal;
    }

    // Returns the string value of the item's type
    string getType() {
      return itemType;
    }

};


// All of the below code pre-allocates the global room data variables
// so they can be accessed in the Functions.h file with ease.

// Item Names
string item1Name = "Revolver";
string item2Name = "Dagger";
string item3Name = "Lead Pipe";
string item4Name = "Rope";
string item5Name = "Candle Stick";
string item6Name = "Wrench";
string item7Name = "Shark Fin Soup";
string item8Name = "Chicken";
string item9Name = "Cheese and Crackers";
string item10Name = "Cake";

// Item Type
string item1Type = "Weapon";
string item2Type = "Weapon";
string item3Type = "Weapon";
string item4Type = "Weapon";
string item5Type = "Weapon";
string item6Type = "Weapon";
string item7Type = "Consumable";
string item8Type = "Consumable";
string item9Type = "Consumable";
string item10Type = "Consumable";

// Item Description
string item1Desc = "Revolver desc";
string item2Desc = "Dagger desc";
string item3Desc = "Lead Pipe desc";
string item4Desc = "Rope desc";
string item5Desc = "Candle Stick desc";
string item6Desc = "Wrench desc";
string item7Desc = "Shark Fin Soup desc";
string item8Desc = "Chicken desc";
string item9Desc = "Cheese and Crackers desc";
string item10Desc = "Cake desc";

// Item Damage
int item1Damage = 10;
int item2Damage = 10;
int item3Damage = 5;
int item4Damage = 10;
int item5Damage = 5;
int item6Damage = 5;
int item7Damage = 0;
int item8Damage = 0;
int item9Damage = 0;
int item10Damage = 0;

// Item Heal
int item1Heal = 0;
int item2Heal = 0;
int item3Heal = 0;
int item4Heal = 0;
int item5Heal = 0;
int item6Heal = 0;
int item7Heal = 10;
int item8Heal = 10;
int item9Heal = 5;
int item10Heal = 5;


