#include "Boxes.hpp"

Inventory::Inventory() : Boxes(3, 9) {}


void Inventory::stackItem(pair<int,int>indexSrc, pair<int,int>indexDst){
    Item* itemSrc = this->collection[indexSrc.first][indexSrc.second];
    Item* itemDst = this->collection[indexDst.first][indexDst.second];

    if(itemSrc->checkDummy()){
        //Error kosong
        cout << "Tidak dapat memindahkan item kosong!!" << endl;
        return;
    }
    else{
        if(itemDst->checkDummy()){
            //MOVE biasa
            this->collection[indexDst.first][indexDst.second] = itemSrc;
            makeDummy(indexSrc.first,indexSrc.second);
        }
        else{
            if(!itemSrc->getTool() && !itemDst->getTool()){
                ItemNonTool* castSrc = static_cast<ItemNonTool*>(itemSrc);
                ItemNonTool* castDst = static_cast<ItemNonTool*>(itemDst);
                
                if ((*castSrc) & (*castDst)){
                    int slot = min(castSrc->getQuantity(), castDst->slotAvailable());
                    try {
                        (*castDst) += slot;
                        (*castSrc) -= slot;
                    } catch(BaseException *exec) {
                        exec->printMessage();
                    }

                    if(castSrc->getQuantity() == 0){
                        makeDummy(indexSrc.first, indexSrc.second);
                    }
                } else {
                    cout << "Slot tujuan telah ditempati\n";
                }
            } 
        }
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
        cout << "Item berhasil digunakan!!" << endl;
    }else {
        cout << "Hanya dapat menggunakan item tool!" << endl;
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
