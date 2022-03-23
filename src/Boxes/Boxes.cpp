#include "Boxes.hpp"

Boxes::Boxes(int rowSize, int colSize) : rowSize(rowSize), colSize(colSize) {
    //Mengisi vector dengan dummy item
    Item* dummyItem = new Item();

    vector<Item*> in(colSize, dummyItem);
    this->collection = vector<vector<Item*>>(rowSize, in);
}

Item* Boxes::getElmt(int row, int col) const{
    return this->collection[row][col];
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


pair<int, int> Boxes::getIndexSameItem(Item* item)
{
    for(int i = 0; i < this->getRowSize(); i++) {
        for(int j = 0; j < this->getColSize(); j++) {
            if(this->collection[i][j] == item) {
                pair<int,int> index = make_pair(i, j);
                return index;
            }
        }
    }
    pair<int, int> noItemExist = make_pair(-1,-1);
    return noItemExist;
}


void Boxes::insertItem(Item* item)
{
    pair<int, int> index = getIndexSameItem(item);
    if(index.first != 1) { 
        ItemNonTool* cast = static_cast<ItemNonTool*> (this->collection[index.first][index.second]);
        if(cast->getQuantity() + item->getQuantity() <=64) {
            (*cast) += item->getQuantity();
            this->collection[index.first][index.second] = (Item*) cast;
        }
        else {
            int quantity = cast->getQuantity() + item->getQuantity();
            int remain = quantity % 64;
            quantity -= 64;
            (*cast) += (64 - cast->getQuantity());
            this->collection[index.first][index.second] = (Item*) cast;
            while(quantity > 64) { // to handle case input quantity > 128
                pair<int, int> emptyBox = this->getEmptyIndex();
                Item* item = new Item(item->getName(), item->getType(), 64, item->getTool());
                if(!(emptyBox.first == -1 || emptyBox.second == -1)) {
                    this->collection[emptyBox.first][emptyBox.second] = item;
                }
                quantity -= 64;
            }
            if(remain > 0) {
                pair<int, int> emptyBox = this->getEmptyIndex();
                Item* item = new Item(item->getName(), item->getType(), remain, item->getTool());
                if(!(emptyBox.first == -1 || emptyBox.second == -1)) {
                    this->collection[emptyBox.first][emptyBox.second] = item;
                }
            }
        }
    } else {
        pair<int, int> emptyBox = this->getEmptyIndex();
        if(!(emptyBox.first == -1 || emptyBox.second == -1)) {
            this->collection[emptyBox.first][emptyBox.second] = item;
        }
    }
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


void Boxes::setItemByIndex(Item* item, int indexRow, int indexCol)
{
    this->collection[indexRow][indexCol] = item;
}

void Boxes::makeDummy(int indexRow, int indexCol)
{
    Item* dummyItem = new Item();
    setItemByIndex(dummyItem, indexRow, indexCol);
}

Item* Boxes::operator()(int indexRow, int indexCol){
    return this->collection[indexRow][indexCol];
}
