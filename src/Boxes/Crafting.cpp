#include "Boxes.hpp"


Crafting::Crafting() : Boxes(3,3) {}

Item* Crafting::craftResult(map<int,vector<Recipe>> listRecipe) {
    int blockCount = this->getBlockCount();
    cout << blockCount << endl;

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
    
    cout << row << " " << col << " " << recipe.getResult()->getName() << endl;
    // Ini iterasi buat nyari starting di pojok kiri atas
    for(int i = 0; i <= 3 - row; i ++){
        for(int j = 0; j <= 3 - col; j ++){
            bool isSame = true;
            // Ini iterasi di dalem submatriksnya gitu 
            for(int k = i; k < i + row; k ++){
                for(int l = j ; l < j + col; j ++){

                    int recIndRow, recIndCol;
                    recIndRow = k - i;
                    if(!isReverse){
                        recIndCol = l - j;
                    }else{
                        recIndCol = col - (l - j) - 1;
                    }
                    cout << k << " " << l << endl;
                    cout << recIndRow << " " << recIndCol << endl;
                    Item* fromTable = this->collection[k][l];
                    Item* fromRecipe = recipe(recIndRow, recIndCol);

                    cout << i << " " << j << endl;
                    cout << fromTable->getName() << " " << fromTable->getType() << endl;
                    cout << fromRecipe->getName() << " " << fromRecipe->getType() << endl;

                    if(fromRecipe->getName() == "-" && !fromRecipe->checkDummy()){
                        if(!((*fromTable) == (*fromRecipe))){
                            cout << "HERE" << endl;
                            isSame = false;
                            break;
                        }
                    }else{
                        if(!((*fromTable) & (*fromRecipe))){
                            isSame = false;
                            break;
                        }
                    }
                }
                if(!isSame){
                    break;
                }
            }

            if(isSame){
                return recipe.getResult();
            }
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
