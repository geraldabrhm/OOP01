#include "Boxes.hpp"


Crafting::Crafting() : Boxes(3,3) {}

Item* Crafting::craftResult(map<int,vector<Recipe>> listRecipe) {
    int blockCount = this->getBlockCount();

    vector<Recipe> needCheck = listRecipe[blockCount];

    for(int i = 0; i < needCheck.size(); i ++){
        Item* result = checkRecipe(needCheck[i], false);

        if(!result->checkDummy()){
            return result;
        }else{
            result = checkRecipe(needCheck[i], true);
            if(!result->checkDummy()){
                return result;
            }
        }
    }
    
    Item* dummyItem = new Item;
    return dummyItem;
}

Item* Crafting::checkRecipe(Recipe recipe, bool isReverse){
    int row = recipe.getRowSize();
    int col = recipe.getColSize();

    // Ini iterasi buat nyari starting di pojok kiri atas
    for(int i = 0; i < 3 - row; i ++){
        for(int j = 0; j < 3 - col; j ++){
            
            // Ini iterasi di dalem submatriksnya gitu 
            
        }
    }

    Item* dummyItem = new Item;
    return dummyItem;
}

void Crafting::displayBoxes()
{
    for(int i = 0; i < this->getRowSize(); i++) {
        for(int j = 0; j < this->getColSize(); j++) {
            this->collection[i][j]->print();
        }
        cout << endl;
    }
}

int Crafting::getBlockCount(){
    int count = 0;

    for(int i = 0; i < 3; i ++){
        for(int j = 0; j < 3; j++){
            if(!this->collection[i][j]->checkDummy()){
                count ++;
            }
        }
    }

    return count;
}
// void Crafting::moveToInventory(Inventory& inventory, pair<int, int> indexCr, pair<int,int> indexInv)
// {
//     // indexCr isinya bukan dummy item, dan diasumsikan jenis item di indexCr dan indexInv sama
//     Item* temp = this->collection[indexCr.first][indexCr.second];
//     Item* srcItem = inventory(indexInv.first, indexInv.second);
//     this->makeDummy(indexCr.first, indexCr.second);

//     if(srcItem->checkDummy()) {
//         inventory.setItemByIndex(temp, indexInv.first, indexInv.second);
//     } else {
//         if(temp->getTool()) {
//             inventory.insertItem(temp);
//         } else {
//             ItemNonTool* castItem = static_cast<ItemNonTool*>(srcItem);
//             try {
//                 (*castItem) += 1;
//             } catch(OperationFailedException *exe) {
//                 exe->printMessage();
//             }
//             inventory.setItemByIndex((Item*) castItem, indexInv.first, indexInv.second);
//         }
//     }
// }
