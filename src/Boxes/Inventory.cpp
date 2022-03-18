#include "Boxes.hpp"

Inventory::Inventory()
{
    // Item temp = Item();
    this->collection.resize(size);
}


void Inventory::stackItem(int indexSrc, int indexDst)
{
    if(equalityItems(indexSrc, indexDst)) {
        
    }
}



bool Inventory::equalityItems(int index1, int index2)
{
    if(collection[index1].getName() == collection[index2].getName() && collection[index1].getType() == collection[index1].getType()) {
        return true;
    }
    return false;
}


void Inventory::useItem(int index)
{

}


void Inventory::displayBoxes()
{

}