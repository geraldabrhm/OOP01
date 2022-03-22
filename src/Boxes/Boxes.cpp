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
    pair<int, int> noEmptyIndex = make_pair(-1,-1);
    return noEmptyIndex;
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
        if(cast->getQuantity() >= quantity) {
            (*cast) -= quantity;
            this->collection[indexRow][indexCol] = (Item*) cast;
            if(cast->getQuantity() == 0) {
                makeDummy(indexRow, indexCol);
            }
        } else {
            // Throw exception here (discard quantity > current quantity)
        }
    } else{ // Assuming it is already a dummy or a tool item (quantity fixed-size = 1)
        makeDummy(indexRow, indexCol);
    }
}


void Boxes::makeDummy(int indexRow, int indexCol)
{
    Item* dummyItem = new Item();
    this->collection[indexRow][indexCol] = dummyItem;
}

Item* Boxes::operator()(int indexRow, int indexCol){
    return this->collection[indexRow][indexCol];
}
