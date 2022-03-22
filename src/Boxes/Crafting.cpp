#include "Boxes.hpp"


Crafting::Crafting() : Boxes(3,3) {}


bool Crafting::craftAble()
{

}


Item* Crafting::craftResult()
{

}


void Crafting::displayBoxes()
{
    for(int i = 0; i < this->getRowSize(); i++) {
        for(int j = 0; j < this->getColSize(); j++) {
            cout << "[ " << this->collection[i][j]->getName() << " " << this->collection[i][j]->getQuantity() << " ] ";
        }
        cout << endl;
    }
}

void Crafting::moveToInventory(Inventory &inventory, int indexSrc, int indexDst)
{

}