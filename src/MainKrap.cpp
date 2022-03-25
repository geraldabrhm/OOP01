#include "./MainKrap.hpp"

MainKrap::MainKrap(){
   for(int i = 1; i <= 9; i ++){
      vector<Recipe>emptyVector;
      this->listRecipe[i] = emptyVector;
   }
}

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

void MainKrap::setupRecipe(string configPath, string recipeFolder){
   string recipePath = configPath + recipeFolder;

   for(const auto& entry: directory_iterator(recipePath)){
      ifstream itemRecipeFile(entry.path());
      if(itemRecipeFile.is_open()){
         int row, column, res_quantity;
         int blockCount = 0;
         string result;

         itemRecipeFile >> row >> column;
         Recipe rec(row, column);
         
         for(int i = 0; i < row; i ++ ){
            for(int j = 0; j < column; j ++){
               string name;
               itemRecipeFile >> name;

               Item* recipe = new Item;
               if(find(listTool.begin(), listTool.end(), name) != listTool.end()){
                  recipe = (Item*)(new ItemTool(name, itemType[name]));
                  blockCount ++;
               }else if(find(listNonTool.begin(), listNonTool.end(), name) != listNonTool.end()){
                  recipe = (Item*)(new ItemNonTool(name, itemType[name], 0));
                  blockCount ++;
               }else if(name != "-"){
                  recipe = new Item("-", name, 0, false);
                  blockCount ++;
               }

               rec.setItemByIndex(recipe, i, j);
            }
         }
         
         itemRecipeFile >> result >> res_quantity;

         Item* itemResult = new Item;
         if (find(listTool.begin(), listTool.end(), result) != listTool.end()) {
            itemResult =(Item*)(new ItemTool(result,itemType[result]));
         }
         else{
            itemResult =(Item*)(new ItemNonTool(result, itemType[result], res_quantity));
         }

         rec.setResult(itemResult);
         this->listRecipe[blockCount].push_back(rec);
      }else{
         cout << "Failed to open file" << endl;
      }
   }
}

