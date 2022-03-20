#include "Boxes.hpp"

Boxes::Boxes()
{

}


void Boxes::insertItem(ItemTool &item, int quantity)
{
    // ItemNonTool dummyNT;
    // If statement to make sure it won't insert pair of dummy item
    if(!item.checkDummy()) {
        for(int i = 0; i < collection.size(); i++) {
            for(int j = 0; j < collection[0].size(); j++) {
                if(collection[i][j].first.checkDummy() && collection[i][j].second.checkDummy()) {
                    // this->collection[i][j].first = dummyNT;
                    this->collection[i][j].second = item;
                    goto point1;
                }
            }
        }
    }
    point1:
        ;
}


void Boxes::insertItem(ItemNonTool &item, int quantity)
{
    if(!item.checkDummy()) {
        for(int i = 0; i < collection.size(); i++) {
            for(int j = 0; j < collection[0].size(); j++) {
                if(collection[i][j].first.checkDummy() && collection[i][j].second.checkDummy()) {
                    // this->collection[i][j].first = dummyNT;
                    this->collection[i][j].first = item;
                    goto point1;
                }
            }
        }
    }
    point1:
        ;
}



void Boxes::discardItem(int indexRow, int indexCol, int quantity)
{
    // Makes sure dont discard an dummyitem in particular index
    ItemNonTool dummyNT;
    ItemTool dummyT;
    if(collection[indexRow][indexCol].first.checkDummy() ||  collection[indexRow][indexCol].second.checkDummy()) {
        if(collection[indexRow][indexCol].first.checkDummy()) {
            // This is item tool
            collection[indexRow][indexCol].second = dummyT;
        } else {
            // This is non-item tool
            if(collection[indexRow][indexCol].first.getQuantity() >= quantity) {
                collection[indexRow][indexCol].first -= quantity;
                if(collection[indexRow][indexCol].first.getQuantity() == 0) {
                    collection[indexRow][indexCol] = dummyNT;
                }
            }
        }
    }
}

pair<ItemNonTool,ItemTool> Boxes::getItem(int indexRow, int indexCol) {
    return collection[indexRow][indexCol];
}
