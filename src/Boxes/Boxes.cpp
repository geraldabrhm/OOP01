#include "Boxes.hpp"

Boxes::Boxes(int rowSize, int colSize) : rowSize(rowSize), colSize(colSize) {
    ItemNonTool dummyNT;
    ItemTool dummyT;
    vector<vector<pair<ItemNonTool,ItemTool>>> temp(rowSize, vector<pair<ItemNonTool,ItemTool>> /**/(colSize, make_pair(dummyNT, dummyT)));
    this->collection = temp;
}

pair<int, int> Boxes::getEmptyIndex()
{
    for(int i = 0; i < rowSize; i++) {
        for(int j = 0; j < colSize; j++) {
            if(collection[i][j].first.checkDummy() && collection[i][j].second.checkDummy()) {
                pair<int, int> result = make_pair(i, j);
                return result;
                goto point1;
            }
        }
    }
    point1: ;
}

void Boxes::insertItem(ItemTool &item, int quantity)
{
    pair<int, int> emptyBox = this->getEmptyIndex();
    this->collection[emptyBox.first][emptyBox.second].second = item; 
}

void Boxes::insertItem(ItemNonTool &item, int quantity)
{

    pair<int, int> emptyBox = this->getEmptyIndex();
    this->collection[emptyBox.first][emptyBox.second].first = item; 
}



void Boxes::discardItem(int indexRow, int indexCol, int quantity)
{
    if(collection[indexRow][indexCol].first.checkDummy()) {
        this->makePairDummy(indexRow, indexCol);
    } else if(collection[indexRow][indexCol].second.checkDummy()) {
        if(collection[indexRow][indexCol].first.getQuantity() >= quantity) { // This is non-item tool
            collection[indexRow][indexCol].first -= quantity;
            if(collection[indexRow][indexCol].first.getQuantity() == 0) {
                this->makePairDummy(indexRow, indexCol);
            }
        }
    }
}


pair<ItemNonTool,ItemTool>& Boxes::operator()(int indexRow, int indexCol)
{
    return this->collection[indexRow][indexCol];
}

void Boxes::makePairDummy(int indexRow, int indexCol) {
    if(collection[indexRow][indexCol].first.checkDummy()) {
        ItemTool dummyT;
        collection[indexRow][indexCol].second = dummyT;
    } else if(collection[indexRow][indexCol].second.checkDummy()) {
        ItemNonTool dummyNT;
        collection[indexRow][indexCol].first = dummyNT;    }
}
