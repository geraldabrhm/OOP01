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

void Inventory::exportInventory(){
    
}

void Inventory::displayBoxes()
{
    for(int i = 0; i < this->getRowSize(); i++) {
        for(int j = 0; j < this->getColSize(); j++) {
            cout << "[ " << this->collection[i][j]->getName() << " " << this->collection[i][j]->getQuantity() << " ] ";
        }
        cout << endl;
    }
}

// Belum handle move many item
void Inventory::moveToCrafting(Crafting &crafting, int indexSrc[], int indexDst[])
{
    Item* srcItem = this->collection[indexSrc[0]][indexSrc[1]];
    Item* dstItem = crafting(indexDst[0], indexDst[1]);
    if(!srcItem->checkDummy()) {
        this->insertItem(dstItem);
        if(srcItem->getTool()) {
            // Dibuat setter setItemByIndex karena gatau cara ngubah member atribut objek/instansiasi
            // crafting dari metode di Inventory
            crafting.setItemByIndex(srcItem, indexDst[0], indexDst[1]);
            this->makeDummy(indexSrc[0], indexSrc[1]);
        } else {
            ItemNonTool* cast = static_cast<ItemNonTool*>(srcItem);
            (*cast) -= (cast->getQuantity() - 1);
            Item* temp = (Item*) cast;
            this->collection[indexSrc[0]][indexSrc[1]] -= 1;
            crafting.setItemByIndex(temp, indexDst[0], indexDst[1]);
            if(this->collection[indexSrc[0]][indexSrc[1]]->getQuantity() == 0) {
                this->makeDummy(indexSrc[0], indexSrc[1]);
            }
        }
    }
}
