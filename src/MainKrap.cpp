#include "./MainKrap.hpp"

MainKrap::MainKrap(){}

MainKrap* MainKrap::getInstance(){
    if (instance == nullptr){
      instance = new MainKrap;
      return instance;
   }
}

void MainKrap::initialize(string configPath, string itemFile, string recipeFolder){
   this->setupConfig(configPath, itemFile);
   this->setupRecipe(configPath, recipeFolder);
}

void MainKrap::setupConfig(string configPath, string itemFile){
   string itemConfigPath = configPath + itemFile;
   // * input -> membaca linenya
   string input;

   string id, item_name, item_type, item_istool;
   ifstream itemConfigFile(itemConfigPath);

   if(itemConfigFile.is_open()){
      while(getline(itemConfigFile, input)){
         itemConfigFile >> id >> item_name >> item_type >> item_istool;

         this->itemId[item_name] = id;
         this->itemType[item_name] = item_type;

         if(item_istool == "TOOL"){
            this->listTool.push_back(item_name);
         }else{
            this->listNonTool.push_back(item_name);
         }
      }

   }else{
      cout << "Failed to open file" << endl;
   }
}


