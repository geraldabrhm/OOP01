#include "Boxes.hpp"

Inventory::Inventory()
{
    ItemNonTool dummyNT;
    ItemTool dummyT;
    pair<ItemNonTool, ItemTool> pairDummy;
    pairDummy.first = dummyNT;
    pairDummy.second = dummyT;
    vector<pair<Item,ItemTool>> contents(9, pairDummy);
    this->collection.resize(3, contents);
}


void Inventory::stackItem(int indexSrc[], int indexDst[])
{
    if(!(collection[indexSrc[0]][indexSrc[1]].first.checkDummy() && collection[indexSrc[0]][indexSrc[1]].second.checkDummy())) {
        
    }
}



bool Inventory::equalityItems(int index1[], int index2[])
{

}


void Inventory::useItem(int index[])
{

}

void Inventory::exportInventory(){
    
}

void Inventory::displayBoxes()
{

}


void Inventory::moveToCrafting(Crafting &crafting, int indexSrc[], int indexDst[])
{

}
