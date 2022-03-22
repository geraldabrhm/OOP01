// sample main file, replace this with your own code
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>
#include "./Item/Item.hpp"
#include "./Boxes/Boxes.hpp"

using namespace std;

int main() {
    boolean isPlaying = true;
    map<string,string> itemId;
    map<string,string> itemType;
    vector<string> listTool;
    vector<string> listNonTool;
    string configPath = "../config";
    string itemConfigPath = configPath + "/item.txt";
    string id, item_name, item_type, item_types;
    string command;
    // Initialize Inventory and Crafting
    Inventory inven = new Inventory();
    Crafting craftbox = new Crafting();


    // read item from config file
    ifstream itemConfigFile(itemConfigPath);
    while (getline(itemConfigFile, line)) {
        itemConfigFile >> id >> item_name >> item_type >> item_types;
        itemId[item_name] = id;
        itemType[item_name] = item_type;
        if (item_types == "TOOL"){
            listTool.push_back(item_name);
        }
        else if (item_types == "NONTOOL"){
            listNonTool.push_back(item_name);
        }
    }

    // read recipes
    for (const auto &entry : filesystem::directory_iterator(configPath + "/recipe")) {
        ifstream itemRecipeFile(entry.path());
        // read from file and do something
    }

    // Main program
    while (isPlaying) {
        cout << "COMMAND : ";
        cin >> command;

        if (command == "EXPORT") {
            string outputPath;
            cin >> outputPath;
            ofstream outputFile(outputPath);

            // hardcode for first test case
            outputFile << inven.exportInventory();
            cout << "Exported" << endl;
        } 
        else if (command == "CRAFT") {
            cout << "TODO" << endl;
        }
        else if (command == "GIVE") {
            string itemName;
            int itemQty;
            cin >> itemName >> itemQty;
            if (find(listTool.begin(), listTool.end(), itemName) != listTool.end()) {
                ItemTool item = new ItemTool(itemName, itemType.at(itemName), itemQty);
                inven.insertItem(item, item.getQuantity());
            }
            else if (find(listNonTool.begin(), listNonTool.end(), itemName) != listNonTool.end()) {
                ItemNonTool item = new ItemNonTool(itemName, itemType.at(itemName), itemQty);
                inven.insertItem(item, item.getQuantity());
            }
            else {
                cout << "Nama item tidak valid!!" << endl;
            }
        }
        else if (command == "MOVE") {
            string slotSrc;
            int slotQty;
            string slotDest;
            // need to handle multiple destinations
            cin >> slotSrc >> slotQty >> slotDest;
            cout << "TODO" << endl;
        } 
        else if (command == "DISCARD") {
            string dest;
            int dest_slot, itemQty;
            cin >> dest >> itemQty;
            if (dest.length() > 3 || dest[0] != 'I'){
                cout << "Harap masukkan slot inventory dengan benar!" << endl;
            }
            else {
                try{
                    dest_slot = stoi(dest.substr(1));
                    cout << dest_slot << endl;
                } catch(exception){
                    cout << "Harap masukkan slot inventory dengan benar!" << endl;
                }
                int row = 0;
                while (dest_slot >= colSize){
                    dest_slot -= (colSize -1);
                    row++;
                }
                if (row >= rowSize){
                    cout << "Indeks masukan di luar index inventory!!";
                } else {
                    inven.discardItem(row,dest_slot,itemQty);
                }
            }
        }  
        else if (command == "SHOW") {
            craftbox.displayBoxes();
            inven.displayBoxes();
        }  
        else if (command == "EXIT") {
            cout << "Terima Kasih telah bermain!!";
            isPlaying = false;
        } else {
            cout << "Command tidak valid!!" << endl;
        }
    }
    return 0;
}