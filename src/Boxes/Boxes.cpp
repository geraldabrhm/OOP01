#include "Boxes.hpp"

Boxes::Boxes(int rowSize, int colSize) : rowSize(rowSize), colSize(colSize) {
    ItemNonTool dummyNT;
    ItemTool dummyT;
    vector<vector<pair<ItemNonTool,ItemTool>>> temp(rowSize, vector<pair<ItemNonTool,ItemTool>> /**/(colSize, make_pair(dummyNT, dummyT)));
    this->collection = temp;
}

pair<int, int> Boxes::getEmptyIndex()
{
    for(int i = 0; i < this->rowSize; i++) {
        for(int j = 0; j < this->colSize; j++) {
            if(collection[i][j].first.checkDummy() && collection[i][j].second.checkDummy()) {
                pair<int, int> result = make_pair(i, j);
                return result;
            }
        }
    }
}

void Boxes::insertItem(ItemTool &item)
{
    pair<int, int> emptyBox = this->getEmptyIndex();
    this->collection[emptyBox.first][emptyBox.second].second = item;
}

void Boxes::insertItem(ItemNonTool &item)
{

    pair<int, int> emptyBox = this->getEmptyIndex();
    if(item.getQuantity() <= 64) {
        this->collection[emptyBox.first][emptyBox.second].first = item;
    } else {
        ItemNonTool temp = item;
        temp += -(item.getQuantity() - 64);
        item += -64;
        this->collection[emptyBox.first][emptyBox.second].first = temp;
        insertItem(item);
    }
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
