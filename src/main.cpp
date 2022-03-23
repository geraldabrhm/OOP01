// sample main file, replace this with your own code
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>
#include <bits/stdc++.h>
#include "./Item/Item.hpp"
#include "./Boxes/Boxes.hpp"

using namespace std;

int main() {
    bool isPlaying = true;
    map<int,vector<Recipe>> listRecipe;
    map<string,string> itemId;
    map<string,string> itemType;
    vector<string> listTool;
    vector<string> listNonTool;
    vector<string> listType = {"LOG","PLANK","STONE"};
    string configPath = "../config";
    string itemConfigPath = configPath + "/item.txt";
    string id, item_name, item_type, item_types;
    string command;
    // Initialize Inventory and Crafting
    Inventory* inven = new Inventory();
    Crafting* craftbox = new Crafting();


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
        string rec_line, elmt, result;
        char space_char = ' ';
        int rec_row, rec_col;
        int res_quantity, i, j, blockCount;
        itemRecipeFile >> rec_row >> rec_col;
        Item* recipe;
        getline(itemRecipeFile, rec_line);
        Recipe rec(rec_row,rec_col);
        blockCount = 0;
        for (i = 0; i < rec_row; i++){
            getline(itemRecipeFile,rec_line);
            stringstream sstream(rec_line);
            j = 0;
            while (getline(sstream, elmt, space_char)){
                if(find(listType.begin(), listType.end(), elmt) != listType.end()){
                    //Create item only have type
                    Item* recipe = new Item("-", elmt, 0, false);
                    blockCount++;
                }
                else if (find(listTool.begin(), listTool.end(), elmt) != listTool.end()) {
                    ItemTool* recipe = new ItemTool(elmt,itemType.at(elmt));
                    (Item*)recipe;
                    blockCount++;
                }
                else if (find(listNonTool.begin(), listNonTool.end(), elmt) != listNonTool.end()) {
                    ItemNonTool* recipe = new ItemNonTool(elmt, itemType.at(elmt), 0);
                    (Item*)recipe;
                    blockCount++;
                } else { // "-"
                    Item* recipe = new Item();
                }
                rec.setItemByIndex(recipe,i,j);
                j++;
            }
        }
        itemRecipeFile >> result >> res_quantity;
        if (find(listTool.begin(), listTool.end(), result) != listTool.end()) {
            ItemTool* itemResult = new ItemTool(result,itemType.at(result));
        }
        else if (find(listNonTool.begin(), listNonTool.end(), result) != listNonTool.end()) {
            ItemNonTool* itemResult = new ItemNonTool(result, itemType.at(result), res_quantity);
        }
        Item* itemResult = new Item(*itemResult);
        rec.insertItem(itemResult);
        listRecipe[blockCount].push_back(rec);
    }

    // Main program
    while (isPlaying) {
        cout << "COMMAND : ";
        cin >> command;

        if (command == "EXPORT") {
            string outputPath;
            cout << "Masukkan nama file baru : " << endl;
            cin >> outputPath;
            ifstream  checkfile;
            checkfile.open(outputPath);
            while (checkfile){
                string confirmation;
                cout << "Terdapat file dengan nama yang sama!" << endl;
                cout << "Apakah ingin melakukan overwrite? (Yy)" << endl;
                cout << "(Ketik apapun untuk input nama file baru!)" << endl;
                cin >> confirmation;
                if (confirmation.compare("Y") == 0 || confirmation.compare("y") == 0){
                    checkfile.close();
                    break;
                }
                else {
                    checkfile.close();
                    cout << "Masukkan nama file baru : " << endl;
                    cin >> outputPath;
                    checkfile.open(outputPath);
                }
            }
            ofstream outputFile;
            outputFile.open(outputPath);
            int row = (*inven).getRowSize();
            int col = (*inven).getColSize();
 
            // Do export
            for (int i = 0; i < row; i++){
                for (int j = 0; j < col; j++){
                    Item* elmt = (*inven).getElmt(i,j);
                    if (elmt->getTool()){
                        ItemTool* elmt = static_cast<ItemTool*>(elmt);
                        outputFile << itemId.at(elmt->getName()) << ":" << elmt->getDurability() << endl;
                    }
                    else{
                        outputFile << itemId.at(elmt->getName()) << ":" << elmt->getQuantity() << endl;
                    }
                }
            }
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
                cout << "Tidak dapat melakukan command GIVE untuk item Tool!" << endl;
            }
            else if (find(listNonTool.begin(), listNonTool.end(), itemName) != listNonTool.end()) {
                ItemNonTool* item = new ItemNonTool(itemName, itemType.at(itemName), itemQty);
                (Item*)item;
                (*inven).insertItem(item);
            }
            else {
                cout << "Nama item tidak valid!!" << endl;
            }
        }
        else if (command == "MOVE") {
            string slotSrc;
            int slotQty, dest_slot;

            cin >> slotSrc >> slotQty;
            if (slotSrc.length() > 3 || slotSrc[0] != 'I' || slotSrc[0] != 'C'){
                cout << "Masukan slot inventory tidak sesuai!" << endl;
            }
            else {
                int rowDest, colDest;
                if (slotSrc[0] != 'I'){
                    rowDest = (*inven).getRowSize();
                    colDest = (*inven).getColSize();
                } else if (slotSrc[0] != 'C'){
                    rowDest = (*craftbox).getRowSize();
                    colDest = (*craftbox).getColSize();
                }
                try{
                    dest_slot = stoi(slotSrc.substr(1));
                    cout << dest_slot << endl;
                } catch(exception){
                    cout << "Masukan slot inventory tidak sesuai!" << endl;
                }
                int row = 0;
                while (dest_slot >= colDest){
                    dest_slot -= (colDest -1);
                    row++;
                }
                if (row >= rowDest){
                    cout << "Indeks masukan di luar index inventory!!";
                } else {
                    for (int inputCount = 0; inputCount < slotQty; inputCount++){
                        string slotDest;
                        cin >> slotDest;
                        //moveTo
                    }
                }
            }
        } 
        else if (command == "DISCARD") {
            string dest;
            int dest_slot, itemQty;
            cin >> dest >> itemQty;
            if (dest.length() > 3 || dest[0] != 'I'){
                cout << "Masukan slot inventory tidak sesuai!" << endl;
            }
            else {
                try{
                    dest_slot = stoi(dest.substr(1));
                    cout << dest_slot << endl;
                } catch(exception){
                    cout << "Masukan slot inventory tidak sesuai!" << endl;
                }
                int row = 0;
                while (dest_slot >= (*inven).getColSize()){
                    dest_slot -= ((*inven).getColSize() -1);
                    row++;
                }
                if (row >= (*inven).getRowSize()){
                    cout << "Indeks masukan di luar index inventory!!";
                } else {
                    (*inven).discardItem(row,dest_slot,itemQty);
                }
            }
        }
        else if (command == "USE"){
            string dest;
            int dest_slot;
            cin >> dest;
            if (dest.length() > 3 || dest[0] != 'I'){
                cout << "Masukan slot inventory tidak sesuai!" << endl;
            }
            else {
                try{
                    dest_slot = stoi(dest.substr(1));
                    cout << dest_slot << endl;
                } catch(exception){
                    cout << "Masukan slot inventory tidak sesuai!" << endl;
                }
                int row = 0;
                while (dest_slot >= (*inven).getColSize()){
                    dest_slot -= ((*inven).getColSize() -1);
                    row++;
                }
                if (row >= (*inven).getRowSize()){
                    cout << "Indeks masukan di luar index inventory!!";
                } else {
                    (*inven).useItem(row,dest_slot);
                }
            }
        }  
        else if (command == "SHOW") {
            (*craftbox).displayBoxes();
            (*inven).displayBoxes();
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