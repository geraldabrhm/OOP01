#include "Boxes.hpp"


Crafting::Crafting() : Boxes(3,3) {}

pair<string,int> Crafting::craftResult(map<int,vector<Recipe>> listRecipe) {
    int blockCount = this->getBlockCount();

    vector<Recipe> needCheck = listRecipe[blockCount];

    for(int i = 0; i < needCheck.size(); i ++){
        pair<string,int> result = checkRecipe(needCheck[i], false);

        if(result.first!="Default"){
            return result;
        }else{
            result = checkRecipe(needCheck[i], true);
            if(result.first!="Default"){
                return result;
            }
        }
    }
    if (blockCount == 2){
        Item* item1 = new Item;
        Item* item2 = new Item;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(!this->collection[i][j]->checkDummy()) {
                    if(item1->checkDummy()) {
                        item1 = this->collection[i][j];
                    } else {
                        item2 = this->collection[i][j];
                    }
                }
            }
        }

        if(item1->getTool() && item2->getTool() && (*item1 & *item2) ) {
            ItemTool* itemTool1 = static_cast<ItemTool*>(item1);
            ItemTool* itemTool2 = static_cast<ItemTool*>(item2);
            string name = itemTool1->getName();
            int dura = min(10,itemTool1->getDurability()+itemTool2->getDurability()); 
            return make_pair(name,dura);
        }
    }
    return make_pair("Default",0);
}

pair<string,int> Crafting::checkRecipe(Recipe recipe, bool isReverse){
    int row = recipe.getRowSize();
    int col = recipe.getColSize();

    // Ini iterasi buat nyari starting di pojok kiri atas
    for(int i = 0; i <= 3 - row; i ++){
        for(int j = 0; j <= 3 - col; j ++){
            bool isSame = true;
            // Ini iterasi di dalem submatriksnya gitu 
            for(int k = i; k < i + row; k ++){
                for(int l = j ; l < j + col; l ++){

                    int recIndRow, recIndCol;
                    recIndRow = k - i;
                    if(!isReverse){
                        recIndCol = l - j;
                    }else{
                        recIndCol = col - (l - j) - 1;
                    }
                    Item* fromTable = this->collection[k][l];
                    Item* fromRecipe = recipe(recIndRow, recIndCol);

                    if(fromRecipe->getName() == "-" && !fromRecipe->checkDummy()){
                        if(!((*fromTable) == (*fromRecipe))){
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
                return make_pair(recipe.getResult(),recipe.getQty());
            }
        }
    }
    return make_pair("Default",0);
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
