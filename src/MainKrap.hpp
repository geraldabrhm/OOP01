#include "./Item/Item.hpp"
#include "./Exception/Exception.hpp"
#include "./Boxes/Boxes.hpp"
//#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;
// using namespace filesystem;


class MainKrap{
private:
    static MainKrap *instance;
protected:

    map<int,vector<Recipe>> listRecipe;
    map<string,string> itemId;
    map<string,string> itemType;
    vector<string> listTool;
    vector<string> listNonTool;
    string command;

    // Initialize Inventory and Crafting
    Inventory* inventory;
    Crafting* craftbox;

    MainKrap();
public:
    static MainKrap* getInstance();

    //Btw ini aku gak tau bener gak gini pakenya jadi ya wkkwkw
    /**
     * @brief Setup kondisi game sebelum dimulai 
     * 
     * @param configPath-string path ke folder yang menyimpan config 
     * @param itemFile-string nama file yang menyompan config item 
     * @param recipeFolder-string folder yang menyimpan data configRecipe
     * 
     */
    void initialize(string configPath, string itemFile, string recipeFolder);

    /**
     * @brief Membaca config file untuk item dan menyimpannya dalam variabel
     * 
     * @param configPath-string path ke folder yang menyimpan config s
     * @param itemFile-string nama file yang menyompan config item 
     */
    void setupConfig(string configPath, string itemFile);
    
    /**
     * @brief 
     * 
     * @param configPath-string path ke folder yang menyimpan config s 
     * @param recipeFolder-string folder yang menyimpan data configRecipe
     */
    void setupRecipe(string configPath, string recipeFolder);

    void GIVE();
    void MOVE();
    void CRAFT();
    void USE();
    void DISCARD();
    void SHOW();
    void EXPORT();
    void HELP();
    // Main program cek command
    void COMMAND();

    string checkInput(char toMatch, int rowMatch, int colMatch, int& row, int& col);
};