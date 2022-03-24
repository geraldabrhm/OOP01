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
        rec.setResult(itemResult);
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
            pair<int,int> idx_src;
            vector<pair<int,int>> idx_dest;
            int row_src, col_src, slotQty, row_dest, col_dest;
            int row = (*inven).getRowSize();
            int col = (*inven).getColSize();

            string out = checkInput('I',row,col,row_src,col_src);
            if (out.empty()){
                idx_src = make_pair(row_src,col_src);
                cin >> slotQty;
                row = (*craftbox).getRowSize();
                col = (*craftbox).getColSize();
                for (int iterator = 0; iterator < slotQty; iterator++) {
                    string out = checkInput('C',row,col,row_dest,col_dest);
                    if (out.empty()){
                        idx_dest.push_back(make_pair(row_dest,col_dest));
                    } else {
                        cout << out << endl;
                        break;
                    }
                }
                if (idx_dest.size() == slotQty){
                    inven->moveTo((*craftbox), idx_src, idx_dest);
                }
            } else {
                row = (*craftbox).getRowSize();
                col = (*craftbox).getColSize();
                string out = checkInput('C',row,col,row_src,col_src);
                if (out.empty()){
                    idx_src = make_pair(row_src,col_src);
                    cin >> slotQty;
                    if (slotQty == 1){
                        row = (*inven).getRowSize();
                        col = (*inven).getColSize();

                        string out = checkInput('I',row,col,row_dest,col_dest);
                        if (out.empty()){
                            idx_dest.push_back(make_pair(row_dest,col_dest));
                            craftbox->moveTo((*inven),idx_src,idx_dest);
                        } else {
                            cout << out << endl;
                        }
                    }
                    else {
                        cout << "Hanya dapat memindahkan ke 1 slot inventory" << endl;
                    }
                } else {
                    cout << out << endl;
                }
            }
        } 
        else if (command == "DISCARD") {
            int row_dest, col_dest, itemQty;
            int row = (*inven).getRowSize();
            int col = (*inven).getColSize();

            string out = checkInput('I',row,col,row_dest,col_dest);
            if (out.empty()){
                cin >> itemQty;
                (*inven).discardItem(row_dest,col_dest,itemQty);
            } else {
                cout << out << endl;
            }
        }
        else if (command == "USE"){
            int row_dest, col_dest;
            int row = (*inven).getRowSize();
            int col = (*inven).getColSize();

            string out = checkInput('I',row,col,row_dest,col_dest);
            if (out.empty()){
                (*inven).useItem(row_dest,col_dest);
            } else {
                cout << out << endl;
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

string checkInput(char toMatch, int rowMatch, int colMatch, int& row, int& col){
    string dest, out;
    cin >> dest;
    out = "";
    col = -1;
    row = 0;
    if (dest.length() > 3 || dest[0] != toMatch){
        out = "Masukan slot inventory tidak sesuai!\n";
    }
    else {
        try{
            col = stoi(dest.substr(1));
        } catch(exception){
            out = "Masukan slot inventory tidak sesuai!\n";
        }
        while (col >= colMatch){
            col -= colMatch;
            row++;
        }
        if (row >= rowMatch){
            out = "Indeks masukan di luar index inventory!!\n";
        } else {
            //do nothing (input valid then out = "")
        }
    }
    return out;
}