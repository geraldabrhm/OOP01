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

   this->command = "Default";
   this->inventory = new Inventory();
   this->craftbox = new Crafting();
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

void MainKrap::GIVE(){
   string itemName;
   int itemQty;
   cin >> itemName >> itemQty;
   if (find(listTool.begin(), listTool.end(), itemName) != listTool.end()) {
         cout << "Tidak dapat melakukan command GIVE untuk item Tool!" << endl;
   }
   else if (find(listNonTool.begin(), listNonTool.end(), itemName) != listNonTool.end()) {
         ItemNonTool* item = new ItemNonTool(itemName, itemType.at(itemName), itemQty);
         (Item*)item;
         (*this->inventory).insertItem(item);
   }
   else {
         cout << "Nama item tidak valid!!" << endl;
   }
}
void MainKrap::MOVE(){
   pair<int,int> idx_src;
   vector<pair<int,int>> idx_dest;
   int row_src, col_src, slotQty, row_dest, col_dest;
   int row = (*this->inventory).getRowSize();
   int col = (*this->inventory).getColSize();

   string out = checkInput('I',row,col,row_src,col_src);
   if (out.empty()){
      idx_src = make_pair(row_src,col_src);
      cin >> slotQty;
      row = (*this->craftbox).getRowSize();
      col = (*this->craftbox).getColSize();
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
         this->inventory->moveTo((*this->craftbox), idx_src, idx_dest);
      }
   } else {
      row = (*this->craftbox).getRowSize();
      col = (*this->craftbox).getColSize();
      string out = checkInput('C',row,col,row_src,col_src);
      if (out.empty()){
         idx_src = make_pair(row_src,col_src);
         cin >> slotQty;
         if (slotQty == 1){
            row = (*this->inventory).getRowSize();
            col = (*this->inventory).getColSize();

            string out = checkInput('I',row,col,row_dest,col_dest);
            if (out.empty()){
               idx_dest.push_back(make_pair(row_dest,col_dest));
               this->craftbox->moveTo((*this->inventory),idx_src,idx_dest);
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
void MainKrap::CRAFT(){

}
void MainKrap::USE(){
   int row_dest, col_dest;
   int row = (*this->inventory).getRowSize();
   int col = (*this->inventory).getColSize();

   string out = checkInput('I',row,col,row_dest,col_dest);
   if (out.empty()){
      (*this->inventory).useItem(row_dest,col_dest);
   } else {
      cout << out << endl;
   }
}
void MainKrap::DISCARD(){
   int row_dest, col_dest, itemQty;
   int row = (*this->inventory).getRowSize();
   int col = (*this->inventory).getColSize();

   string out = checkInput('I',row,col,row_dest,col_dest);
   if (out.empty()){
      cin >> itemQty;
      (*this->inventory).discardItem(row_dest,col_dest,itemQty);
   } else {
      cout << out << endl;
   }
}
void MainKrap::SHOW(){
   (*this->craftbox).displayBoxes();
   (*this->inventory).displayBoxes();
}
void MainKrap::EXPORT(){
   string outputPath;
   cout << "Masukkan nama file baru : " << endl;
   cin >> outputPath;
   ifstream checkfile;
   checkfile.open(outputPath);
   while (checkfile){
      checkfile.close();
      string confirmation;
      cout << "Terdapat file dengan nama yang sama!" << endl;
      cout << "Apakah ingin melakukan overwrite? (Yy)" << endl;
      cout << "(Ketik apapun untuk input nama file baru!)" << endl;
      cin >> confirmation;
      if (confirmation == "Y" || confirmation == "y"){
         break;
      }
      else {
         cout << "Masukkan nama file baru : " << endl;
         cin >> outputPath;
         checkfile.open(outputPath);
      }
   }
   ofstream outputFile;
   outputFile.open(outputPath);
   int row = (*this->inventory).getRowSize();
   int col = (*this->inventory).getColSize();

   // Do export
   for (int i = 0; i < row; i++){
         for (int j = 0; j < col; j++){
            Item* elmt = (*this->inventory).getElmt(i,j);
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
void MainKrap::HELP(){
   cout << "GIVE NAME COUNT -> Mendapatkan barang NAME sebanyak COUNT" << endl;
   cout << "DISCARD IX COUNT -> Membuang item  sejumlah COUNT pada inventory slot X jika jumlah mencukupi" << endl;
   cout << "MOVE IX N CA CB ... CN -> Memindahkan item dari inventory slot X ke N slot crafting" << endl;
   cout << "MOVE IX 1 IY -> Memindahkan dan menumpuk item dari inventory slot X ke slot Y jika item sama" << endl;
   cout << "MOVE CX 1 IY -> Memindahkan item dari crafting slot X ke inventory slot Y" << endl;
   cout << "CRAFT -> Melakukan crafting item jika konfigurasi pada box crafting memenuhi resep" << endl;
   cout << "USE IX -> Menggunakan item pada Inventory slot X jika item adalah item tool" << endl;
   cout << "SHOW -> Menampilkan isi box Crafting dan Inventory" << endl;
   cout << "EXPORT FILENAME -> Melakukan eksport data inventory ke dalam file FILENAME" << endl;
   cout << "EXIT -> Keluar dari permainan" << endl;
}

void MainKrap::PLAY(){
   cout << "Selamat bermain!!" << endl;
   cout << "Ketik HELP untuk melihat daftar COMMAND" << endl;
   cout << endl;

   while (command != "EXIT"){
      cout << "COMMAND : ";
      cin >> command;

      if (command == "GIVE"){
         GIVE();
      }
      else if (command == "MOVE"){
         MOVE();
      }
      else if (command == "CRAFT"){
         CRAFT();
      }
      else if (command == "USE"){
         USE();
      }
      else if (command == "DISCARD"){
         DISCARD();
      }
      else if (command == "SHOW"){
         SHOW();
      }
      else if (command == "EXPORT"){
         EXPORT();
      }
      else if (command == "HELP"){
         HELP();
      }
      else {
         cout << "Command tidak valid!!" << endl;
      }
   }

   cout << "Terimakasih telah bermain MainKrap!!" << endl;
   cout << "Semoga hari-harimu menyenangkan :D" << endl;
}

string MainKrap::checkInput(char toMatch, int rowMatch, int colMatch, int& row, int& col){
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