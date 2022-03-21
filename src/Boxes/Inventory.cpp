#include "Boxes.hpp"

Inventory::Inventory() : Boxes(3, 9) {}


void Inventory::stackItem(int indexSrc[2], int indexDst[2])
{
    if ((collection[indexSrc[0]][indexSrc[1]].first & collection[indexDst[0]][indexDst[1]].first) &&
    !collection[indexSrc[0]][indexSrc[1]].first.checkDummy())
    {
        // // Hanya boleh stack item NonTool
        // if (collection[indexSrc[0]][indexSrc[1]].first.getName() == collection[indexDst[0]][indexDst[1]].first.getName()){
        //     if (collection[indexSrc[0]][indexSrc[1]].first.getType() == collection[indexDst[0]][indexDst[1]].first.getType())
        //     {
        //         // Jumlahkan quantity Item di indexDst, hapus item di indexSrc
        //         collection[indexDst[0]][indexDst[1]].first.quantity += collection[indexSrc[0]][indexSrc[1]].first.getQuantity();
        //         // Kalau totalnya lebih dari 64
        //         if (collection[indexDst[0]][indexDst[1]].first.getQuantity() > 64)
        //         {
        //             collection[indexSrc[0]][indexSrc[1]].first.quantity = (collection[indexDst[0]][indexDst[1]].first.getQuantity() - 64);
        //             collection[indexDst[0]][indexDst[1]].first.quantity = 64;

        //         } else
        //         {
        //             discardItem(indexSrc[0], indexSrc[1], collection[indexSrc[0]][indexSrc[1]].first.getQuantity());
        //         }
                
        //     }
        // }
        pair<ItemNonTool, ItemTool> src = collection[indexSrc[0]][indexSrc[1]];
        pair<ItemNonTool, ItemTool> dst = collection[indexDst[0]][indexDst[1]];
        int srcQuantity = src.first.getQuantity();
        int dstQuantity = dst.first.getQuantity();
        int totalQuantity = srcQuantity + dstQuantity;
        if(totalQuantity >= 64) {
            dst.first += (64-dstQuantity);
            if(totalQuantity == 64) {
                this->makePairDummy(indexSrc[0], indexSrc[1]);
            } else {
                discardItem(indexSrc[0], indexSrc[1], (64-dstQuantity));
                ItemNonTool temp = src.first;
                this->makePairDummy(indexSrc[0], indexSrc[1]);
                pair<int, int> newIndexSrc = this->getEmptyIndex();
                this->collection[newIndexSrc.first][newIndexSrc.second].first = temp;
            }
        }
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
