#include "Boxes.hpp"

Inventory::Inventory() : Boxes(3, 9) {}


void Inventory::stackItem(pair<int,int>indexSrc, pair<int,int>indexDst){
    Item* itemSrc = this->collection[indexSrc.first][indexSrc.second];
    Item* itemDst = this->collection[indexDst.first][indexDst.second];

    if(!itemSrc->isTool() && !itemDst->isTool()){
        ItemNonTool* castSrc = static_cast<ItemNonTool*>(itemSrc);
        ItemNonTool* castDst = static_cast<ItemNonTool*>(itemDst);

        if(castDst->isAvailable()){
            int slot = min(castSrc->getQuantity(), 64 - (castDst->getQuantity()));
            (*castDst) += slot;
            (*castSrc) -= slot;

            if(castSrc ->getQuantity() == 0){
                Item* dummyItem = new Item;
                this->collection[indexSrc.first][indexSrc.second] = dummyItem;
            }else{
                pair<int,int>index = this->getEmptyIndex();
                if(index.first != indexSrc.first || index.second != indexSrc.second){
                    this->collection[index.first][index.second] = (Item*) castSrc;
                    Item* dummyItem = new Item;
                    this->collection[indexSrc.first][indexSrc.second] = dummyItem;
                }else{
                    this->collection[indexSrc.first][indexSrc.second] = (Item*) castSrc;
                }
            }
        }else{
            //Harusnya throw error disini
            return;
        }
    }else{
        //Harusnya throw error disini
        return;
    }
}

void Inventory::useItem(int indexRow, int indexCol)
{
    if(!collection[indexRow][indexCol].second.checkDummy()) {
        collection[indexRow][indexCol].second.reduceDurability();
    }
}

void Inventory::exportInventory(){
    
}

void Inventory::displayBoxes()
{

}


void Inventory::moveToCrafting(Crafting &crafting, int indexSrc[], int indexDst[])
{

}
