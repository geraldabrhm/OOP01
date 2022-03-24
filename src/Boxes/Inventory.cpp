#include "Boxes.hpp"

Inventory::Inventory() : Boxes(3, 9) {}


void Inventory::stackItem(pair<int,int>indexSrc, pair<int,int>indexDst){
    Item* itemSrc = this->collection[indexSrc.first][indexSrc.second];
    Item* itemDst = this->collection[indexDst.first][indexDst.second];

    if(!itemSrc->getTool() && !itemDst->getTool()){
        ItemNonTool* castSrc = static_cast<ItemNonTool*>(itemSrc);
        ItemNonTool* castDst = static_cast<ItemNonTool*>(itemDst);

        
        int slot = min(castSrc->getQuantity(), castDst->slotAvailable());
        try {
            (*castDst) += slot;
            (*castSrc) -= slot;
        } catch(OperationFailedException *exec) {
            exec->printMessage();
        }


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
        InvalidTypeException *exce = new InvalidTypeException(false);
        throw exce;
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
            this->collection[i][j]->print();
        }
        cout << endl;
    }
}

// Asumsi: pemindahan dilakukan 1 persatu dan jika di crafting sudah ada item, dilakukan pengembalian ke inventory
// void Inventory::moveToCrafting(Crafting &crafting, pair<int, int> indexSrc, vector<pair<int, int>> indexsDst)
// {
//     Item* srcItem = this->collection[indexSrc.first][indexSrc.second];
//     if(!srcItem->checkDummy()) {
//         if(srcItem->getTool()) {
//             Item* dstItem = crafting(indexsDst[0].first, indexsDst[0].second);
//             crafting.setItemByIndex(srcItem, indexsDst[0].first, indexsDst[0].second);
//             this->makeDummy(indexSrc.first, indexSrc.second);
//             if(!dstItem->checkDummy()) {
//                 this->insertItem(dstItem);
//             }
//         } else {
//             ItemNonTool* cast2 = static_cast<ItemNonTool*>(srcItem);
//             int count = 0;

//             for(int i = 0; i < indexsDst.size(); i++) {
//                 ItemNonTool* cast = new ItemNonTool(srcItem->getName(), srcItem->getType(), 1);
//                 Item* dstItem = crafting(indexsDst[i].first, indexsDst[i].second);

//                 this->setItemByIndex((Item*) cast2, indexSrc.first, indexSrc.second);
//                 crafting.setItemByIndex((Item*) cast, indexsDst[i].first, indexsDst[i].second);
                
//                 if(!dstItem->checkDummy()) {
//                     this->insertItem(dstItem);
//                 }
//                 count++;
//             }
//             if(count == cast2->getQuantity()) {
//                 this->makeDummy(indexSrc.first, indexSrc.second);
//             } else {
//                 (*cast2) -= count;
//                 this->setItemByIndex((Item*) cast2, indexSrc.first, indexSrc.second);
//             }
//         }
//     }   
// }
