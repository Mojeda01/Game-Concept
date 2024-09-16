// trading.cpp is a script that simulates a simple trading system between players in a game.
// The program includes the following key components:
//  (1) Item Class: Represents an item with attributes such as name, ID, value, and quantity and Provides constructors for initializing items.
//  (2) Player Class:   Represents a player with attributes such as name, ID, currency, and an inventory (a map of item IDs to items).
//                      Provides methods to add and remove items from the player's inventory.
//  (3) Trade Function: Facilitates trading items between two players. Checks if the seller has enough quantity of the item and if
//                      the buyer has enough currency. Updates the inventories and currencies of both players accordingly.
//  (4) saveTradeJson:  Save the deatils of atrade to a JSON file (trade_log.json) using the nlohmann::json. Includes information about
//                         the seller, buyer, item traded, price, and timestamp.
//  (5) Main Function:  Initializes two players and some items. Demonstrates adding items to player inventories. Attempts a valid trade and
//                      displays the updated state of both players. Attempts a valid trade and displays the updated state of both players.
//                      Attempts an invalid trade to demonstrate error handling. Saves the trade details to a JSON file.
//
// The program uses the nlohmann::json library for JSON serialization and deserialization, which requires enabling C++11 or later during
// compilation.


#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include "nlohmann/json.hpp"

// Define Item class
class Item {
public:
    std::string name;
    int id;
    int value;  // value in currency
    int quantity;

    // Default constructor
    Item() : name(""), id(0), value(0), quantity(0) {}

    Item(std::string n, int i, int v, int q) : name(n), id(i), value(v), quantity(q){}
};

// Define Player class
class Player{
public:
    std::string name;
    int id;
    int currency;
    std::map<int, Item> inventory; // Inventory with item id as key

    Player(std::string n, int i, int c) : name(n), id(i), currency(c) {}

    void addItem(const Item& item){
        if(inventory.count(item.id)){
            inventory[item.id].quantity += item.quantity;
        } else {
            inventory[item.id] = item;
        }
    }

    bool removeItem(int itemId, int quantity){
        if (inventory.count(itemId) && inventory[itemId].quantity >= quantity){
            inventory[itemId].quantity -= quantity;
            if (inventory[itemId].quantity == 0){
                inventory.erase(itemId);
            }
            return true;
        }
        return false;
    }
};

// Function to trade items between two players
bool trade(Player& p1, Player& p2, int itemId, int quantity, int price){
    if (p1.inventory.count(itemId) && p1.inventory[itemId].quantity >= quantity && p2.currency >= price){
        p1.removeItem(itemId, quantity);
        p2.addItem(Item(p1.inventory[itemId].name, itemId, price, quantity));
        p2.currency -= price;
        p1.currency += price;
        return true;
    }
    return false;
}

bool saveTradeJson(const Player& seller, const Player& buyer, int itemId, int quantity, int price) {
    // Create a JSON object
    nlohmann::json tradeJson;

    // Populate the JSON object with trade details
    tradeJson["seller"] = {
        {"name", seller.name},
        {"id", seller.id}
    };
    tradeJson["buyer"] = {
        {"name", buyer.name},
        {"id", buyer.id}
    };
    tradeJson["item"] = {
        {"id", itemId},
        {"name", seller.inventory.at(itemId).name},
        {"quantity", quantity}
    };
    tradeJson["price"] = price;
    tradeJson["timestamp"] = std::time(nullptr);

    // Open a file to write the JSON
    std::ofstream file("trade_log.json", std::ios::app);
    if (file.is_open()) {
        // Write the JSON to the file
        file << tradeJson.dump(4) << std::endl;
        file.close();
        std::cout << "Trade saved to trade_log.json" << std::endl;
        return true;  // Indicate success
    } else {
        std::cerr << "Unable to open trade_log.json for writing" << std::endl;
        return false;  // Indicate failure
    }
}

int main(){
    // Initialize players
    Player player1("Alice", 1, 100);
    Player player2("Bob", 2, 200);

    // Initialize
    Item sword("Sword", 1, 50, 2);
    Item shield("Shield", 2, 30, 1);

    // Add item to player inventories
    player1.addItem(sword);
    player2.addItem(shield);

    // Display the initial state of both players
    std::cout << "Initial state:" << std::endl;
    std::cout << "Player 1 (" << player1.name << ") - Currency: " << player1.currency << std::endl;
    std::cout << "Player 2 (" << player2.name << ") - Currency: " << player2.currency << std::endl;

    // Attempt a valid trade: 1 Sword from player1 to player2 for 50 currency
    std::cout << "\nAttempting trade: 1 Sword from " << player1.name << " to " << player2.name << " for 50 currency." << std::endl;

    // Execute the trade and check if it was successful
    if (trade(player1, player2, 1, 1, 50)) {
        std::cout << "Trade successful!" << std::endl;
        
        // Display the updated state after the successful trade
        std::cout << "\nUpdated state:" << std::endl;
        // Show player1's new currency and inventory
        std::cout << player1.name << " - Currency: " << player1.currency << std::endl;
        std::cout << "Inventory:" << std::endl;
        for (std::map<int, Item>::const_iterator it = player1.inventory.begin(); it != player1.inventory.end(); ++it) {
            std::cout << "  " << it->second.name << " (ID: " << it->first << ") - Quantity: " << it->second.quantity << std::endl;
        }

        // Show player2's new currency and inventory
        std::cout << "\n" << player2.name << " - Currency: " << player2.currency << std::endl;
        std::cout << "Inventory:" << std::endl;
        for (std::map<int, Item>::const_iterator it = player2.inventory.begin(); it != player2.inventory.end(); ++it) {
            std::cout << "  " << it->second.name << " (ID: " << it->first << ") - Quantity: " << it->second.quantity << std::endl;
        }
    } else {
        // If the trade failed, display possible reasons
        std::cout << "Trade failed!" << std::endl;
        std::cout << "Possible reasons:" << std::endl;
        std::cout << "- " << player1.name << " doesn't have enough Swords" << std::endl;
        std::cout << "- " << player2.name << " doesn't have enough currency" << std::endl;
    }

    // Attempt an invalid trade to demonstrate error handling
    std::cout << "\nAttempting invalid trade: 5 Shields from " << player1.name << " to " << player2.name << " for 100 currency." << std::endl;
    if (trade(player1, player2, 2, 5, 100)) {
        std::cout << "Trade successful!" << std::endl;
    } else {
        // This trade should fail because player1 doesn't have 5 shields
        std::cout << "Trade failed as expected." << std::endl;
    }
    
    // Execute the function to save the trade to a .json file.
    if (saveTradeJson(player1, player2, 1, 1, 50)) {
        std::cout << "Trade saved to trade_log.json" << std::endl;
    } else {
        std::cout << "Failed to save trade to file" << std::endl;
    }

    return 0;
}