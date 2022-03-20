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
    // Cek indexSrc tidak kosong
    if (equalityItems(indexSrc, indexDst))
    {
        // Hanya boleh stack item NonTool
        if (collection[indexSrc[0]][indexSrc[1]].first.getName() == collection[indexDst[0]][indexDst[1]].first.getName()){
            if (collection[indexSrc[0]][indexSrc[1]].first.getType() == collection[indexDst[0]][indexDst[1]].first.getType())
            {
                // Jumlahkan quantity Item di indexDst, hapus item di indexSrc
                collection[indexDst[0]][indexDst[1]].first.quantity += collection[indexSrc[0]][indexSrc[1]].first.getQuantity();
                // Kalau totalnya lebih dari 64
                if (collection[indexDst[0]][indexDst[1]].first.getQuantity() > 64)
                {
                    collection[indexSrc[0]][indexSrc[1]].first.quantity = (collection[indexDst[0]][indexDst[1]].first.getQuantity() - 64);
                    collection[indexDst[0]][indexDst[1]].first.quantity = 64;

                } else
                {
                    discardItem(indexSrc[0], indexSrc[1], collection[indexSrc[0]][indexSrc[1]].first.getQuantity());
                }
                
            }
        }
    }
}

bool Inventory::equalityItems(int index1[], int index2[])
{
    bool ans = false;
    // Cek index1 tidak kosong
    if (!(collection[index1[0]][index1[1]].first.checkDummy() && collection[index1[0]][index1[1]].second.checkDummy())) {
        if (collection[index1[0]][index1[1]].first.checkDummy()) {
            if (collection[index1[0]][index1[1]].second.getName() == collection[index2[0]][index2[1]].second.getName()) {
                if (collection[index1[0]][index1[1]].second.getType() == collection[index2[0]][index2[1]].second.getType()) {
                    ans = true;
            }
        } else {
            if (collection[index1[0]][index1[1]].first.getName() == collection[index2[0]][index2[1]].first.getName()) {
                if (collection[index1[0]][index1[1]].first.getType() == collection[index2[0]][index2[1]].first.getType()) {
                    ans = true;
                }
            }
        }
    }
    return ans;
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
