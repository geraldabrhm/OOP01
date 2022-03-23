#include "./Item/Item.hpp"
#include "./Exception/Exception.hpp"
#include "./Boxes/Boxes.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>
#include <thread>
using namespace std;


class MainKrap{
private:
    static MainKrap *instance;
protected:
    map<int,vector<Recipe>> listRecipe;
    map<string,string> itemId;
    map<string,string> itemType;
    vector<string> listTool;
    vector<string> listNonTool;

    MainKrap();
public:
    static MainKrap* getInstance();

    // Isi method lainnya disini , misal getter setter
    /**
     * @brief Program dibagi 2 bagian
     *      1. Inisialiasi -> Pembacaan config
     *      2. Waktu mainnya -> 
     */ 
};