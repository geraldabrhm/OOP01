#include "Boxes.hpp"

Inventory::Inventory() : Boxes(3, 9) {}


void Inventory::stackItem(pair<int,int>indexSrc, pair<int,int>indexDst){
    Item* itemSrc = this->collection[indexSrc.first][indexSrc.second];
    Item* itemDst = this->collection[indexDst.first][indexDst.second];

    if(!itemSrc->getTool() && !itemDst->getTool()){
        ItemNonTool* castSrc = static_cast<ItemNonTool*>(itemSrc);
        ItemNonTool* castDst = static_cast<ItemNonTool*>(itemDst);

        if(castDst->slotAvailable() > 0){
            int slot = min(castSrc->getQuantity(), 64 - (castDst->getQuantity()));
            (*castDst) += slot;
            (*castSrc) -= slot;

            if(castSrc ->getQuantity() == 0){
                makeDummy(indexSrc.first, indexSrc.second);
            }else{
                pair<int,int>index = this->getEmptyIndex();
                if(index.first != indexSrc.first || index.second != indexSrc.second){
                    this->collection[index.first][index.second] = (Item*) castSrc;
                    makeDummy(indexSrc.first, indexSrc.second);
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
    Item* itemToBeUsed = this->collection[indexRow][indexCol];
    if(itemToBeUsed->getTool()) {
        ItemTool* castItem = static_cast<ItemTool*>(itemToBeUsed);
        castItem->reduceDurability();
        if(castItem->getDurability() == 0) {
            makeDummy(indexRow, indexCol);
        } else {
            this->collection[indexRow][indexCol] = (Item*) castItem;
        }
    }
}

void Inventory::displayBoxes()
{
    for(int i = 0; i < this->getRowSize(); i++) {
        for(int j = 0; j < this->getColSize(); j++) {
            cout << "[ " << this->collection[i][j]->getName() << ", Q: " << this->collection[i][j]->getQuantity() << " ] ";
        }
        cout << endl;
    }
}

void Inventory::moveToCrafting(Crafting &crafting, pair<int, int> indexSrc, vector<pair<int, int>> indexsDst)
{
    Item* srcItem = this->collection[indexSrc.first][indexSrc.second];
    if(!srcItem->checkDummy() && srcItem->getQuantity() >= indexsDst.size()) {
        if(srcItem->getTool()) {
            Item* dstItem = crafting(indexsDst[0].first, indexsDst[0].second);
            crafting.setItemByIndex(srcItem, indexsDst[0].first, indexsDst[0].second);
            this->makeDummy(indexSrc.first, indexSrc.second);
            if(!dstItem->checkDummy()) {
                this->insertItem(dstItem);
            }
        } else {
            for(int i = 0; i < indexsDst.size(); i++) {
                Item* dstItem = crafting(indexsDst[i].first, indexsDst[i].second);

                ItemNonTool* cast = static_cast<ItemNonTool*>(srcItem);
                ItemNonTool* cast2 = static_cast<ItemNonTool*>(srcItem);
                (*cast) -= (cast->getQuantity() - 1);
                (*cast2) -= 1;
                this->collection[indexSrc.first][indexSrc.second] = (Item*) cast2;
                crafting.setItemByIndex((Item*) cast, indexsDst[i].first, indexsDst[i].second);
                
                if(this->collection[indexSrc.first][indexSrc.second]->getQuantity() == 0) {
                    this->makeDummy(indexSrc.first, indexSrc.second);
                }
                
                if(!dstItem->checkDummy()) {
                    this->insertItem(dstItem);
                }
            }
        }
    }   
}
