#include "./MainKrap.hpp"

MainKrap::MainKrap(){
   for(int i = 1; i <= 9; i ++){
      vector<Recipe>emptyVector;
      this->listRecipe[i] = emptyVector;
   }
   this->inventory = new Inventory();
   this->craftbox = new Crafting();
}

MainKrap* MainKrap::getInstance(){
   if (instance == nullptr){
      instance = new MainKrap;
   }
   return instance;
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
      std::cout << "Failed to open file" << endl;
   }
}

void MainKrap::setupRecipe(string configPath, string recipeFolder){
   string recipePath = configPath + recipeFolder;
   const filesystem::path recPath(recipePath);
   for(const auto& entry: filesystem::directory_iterator(recPath)){
      cout << entry.path() << endl;
      ifstream itemRecipeFile(entry.path());
      if(itemRecipeFile.is_open()){
         int row, column, res_quantity;
         int blockCount = 0;
         string result;

         itemRecipeFile >> row >> column;
         cout << row << column << endl;
         Recipe rec(row, column);
         
         for(int i = 0; i < row; i ++ ){
            for(int j = 0; j < column; j ++){
               string name;
               itemRecipeFile >> name;
               cout << name << endl;
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
         cout << result << " " << res_quantity << endl;
         Item* itemResult = new Item;
         if (find(listTool.begin(), listTool.end(), result) != listTool.end()) {
            itemResult =(Item*)(new ItemTool(result,itemType[result]));
         }
         else{
            itemResult =(Item*)(new ItemNonTool(result, itemType[result], res_quantity));
         }
         cout << "R" << endl;
         rec.setResult(itemResult);
         cout << rec.getResult()->getName() << endl;
         this->listRecipe[blockCount].push_back(rec);
         cout << "END" << endl;
      }else{
         std::cout << "Failed to open file" << endl;
      }
   }
}

void MainKrap::GIVE(){
   string itemName;
   int itemQty;
   cin >> itemName >> itemQty;
   if (find(listTool.begin(), listTool.end(), itemName) != listTool.end()) {
         std::cout << "Tidak dapat melakukan command GIVE untuk item Tool!" << endl;
   }
   else if (find(listNonTool.begin(), listNonTool.end(), itemName) != listNonTool.end()) {
         ItemNonTool* item = new ItemNonTool(itemName, itemType.at(itemName), itemQty);
         (Item*)item;
         (*this->inventory).insertItem(item);
   }
   else {
         std::cout << "Nama item tidak valid!!" << endl;
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
            std::cout << out << endl;
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
               std::cout << out << endl;
            }
         }
         else {
            std::cout << "Hanya dapat memindahkan ke 1 slot inventory" << endl;
         }
      } else {
         std::cout << out << endl;
      }
   }
}
void MainKrap::CRAFT(){
   Item* result = this->craftbox->craftResult(listRecipe);
   if(result->checkDummy()){
      cout << "Craft gagal " << endl;
   }else{
      inventory->insertItem(result);
   }
}
void MainKrap::USE(){
   int row_dest, col_dest;
   int row = (*this->inventory).getRowSize();
   int col = (*this->inventory).getColSize();

   string out = checkInput('I',row,col,row_dest,col_dest);
   if (out.empty()){
      (*this->inventory).useItem(row_dest,col_dest);
   } else {
      std::cout << out << endl;
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
      std::cout << out << endl;
   }
}
void MainKrap::SHOW(){
   cout << "Crafting Table: " << endl;
   (*this->craftbox).displayBoxes();

   cout << "Inventory: " << endl;
   (*this->inventory).displayBoxes();
}
void MainKrap::EXPORT(){
   string outputPath;
   cin >> outputPath;
   ifstream checkfile;
   checkfile.open(outputPath);
   while (checkfile){
      checkfile.close();
      string confirmation;
      std::cout << "Terdapat file dengan nama yang sama!" << endl;
      std::cout << "Apakah ingin melakukan overwrite? (Yy)" << endl;
      std::cout << "(Ketik apapun untuk input nama file baru!)" << endl;
      cin >> confirmation;
      if (confirmation == "Y" || confirmation == "y"){
         break;
      }
      else {
         std::cout << "Masukkan nama file baru : " << endl;
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
            if(elmt->checkDummy()){
               outputFile << "0:0" << endl;
            }
            else if (elmt->getTool()){
               ItemTool* elmt = static_cast<ItemTool*>(elmt);
               outputFile << itemId.at(elmt->getName()) << ":" << elmt->getDurability() << endl;
            }
            else{
               outputFile << itemId.at(elmt->getName()) << ":" << elmt->getQuantity() << endl;
            }
         }
   }
   std::cout << "Exported" << endl;
}
void MainKrap::HELP(){
   std::cout << "GIVE NAME COUNT -> Mendapatkan barang NAME sebanyak COUNT" << endl;
   std::cout << "DISCARD IX COUNT -> Membuang item  sejumlah COUNT pada inventory slot X jika jumlah mencukupi" << endl;
   std::cout << "MOVE IX N CA CB ... CN -> Memindahkan item dari inventory slot X ke N slot crafting" << endl;
   std::cout << "MOVE IX 1 IY -> Memindahkan dan menumpuk item dari inventory slot X ke slot Y jika item sama" << endl;
   std::cout << "MOVE CX 1 IY -> Memindahkan item dari crafting slot X ke inventory slot Y" << endl;
   std::cout << "CRAFT -> Melakukan crafting item jika konfigurasi pada box crafting memenuhi resep" << endl;
   std::cout << "USE IX -> Menggunakan item pada Inventory slot X jika item adalah item tool" << endl;
   std::cout << "SHOW -> Menampilkan isi box Crafting dan Inventory" << endl;
   std::cout << "EXPORT FILENAME -> Melakukan eksport data inventory ke dalam file FILENAME" << endl;
   std::cout << "EXIT -> Keluar dari permainan" << endl;
}

void MainKrap::PLAY(){
   std::cout << "Selamat bermain!!" << endl;
   std::cout << "Ketik HELP untuk melihat daftar COMMAND" << endl;

   while (command != "EXIT"){
      std::cout << endl << "COMMAND : ";
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
         std::cout << "Command tidak valid!!" << endl;
      }
   }

   std::cout << "Terimakasih telah bermain MainKrap!!" << endl;
   std::cout << "Semoga hari-harimu menyenangkan :D" << endl;
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