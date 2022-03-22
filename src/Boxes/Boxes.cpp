#include "Boxes.hpp"

Boxes::Boxes(int rowSize, int colSize) : rowSize(rowSize), colSize(colSize) {
    //Mengisi vector dengan dummy item
    Item* dummyItem = new Item();

    vector<Item*> in(colSize, dummyItem);
    this->collection = vector<vector<Item*>>(rowSize, in);
}

int Boxes::getRowSize() const{
    return this->rowSize;
}

int Boxes::getColSize() const{
    return this->colSize;
}

pair<int, int> Boxes::getEmptyIndex(){
    for(int i = 0; i < this->rowSize; i++) {
        for(int j = 0; j < this->colSize; j++) {
            if(collection[i][j]->checkDummy()){
                return make_pair(i, j);
            }
        }
    }
}

void Boxes::insertItem(Item* item)
{
    pair<int, int> emptyBox = this->getEmptyIndex();
    this->collection[emptyBox.first][emptyBox.second] = item;
}

void Boxes::discardItem(int indexRow, int indexCol, int quantity)
{
    if(!this->collection[indexRow][indexCol]->getTool()){
        ItemNonTool* cast = static_cast<ItemNonTool*>(this->collection[indexRow][indexCol]);
        (*cast) -= quantity;
        this->collection[indexRow][indexCol] = (Item*) cast;
    }else{
        return;
    }
}


Item* Boxes::operator()(int indexRow, int indexCol){
    return this->collection[indexRow][indexCol];
}
