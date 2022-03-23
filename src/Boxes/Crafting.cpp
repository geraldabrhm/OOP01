#include "./Boxes.hpp"


Crafting::Crafting() : Boxes(3,3) {}


bool Crafting::craftAble()
{

}


Item* Crafting::craftResult()
{

}


void Crafting::displayBoxes() // Cara dapet ID dari file config? Untuk ditampilin di sini juga
{
    for(int i = 0; i < this->getRowSize(); i++) {
        for(int j = 0; j < this->getColSize(); j++) {
            cout << "[ " << this->collection[i][j]->getName() << ", Q: " << this->collection[i][j]->getQuantity() << " ] ";
        }
        cout << endl;
    }
}

void Crafting::moveToInventory(Inventory& inventory, pair<int, int> indexCr, pair<int,int> indexInv)
{
    // indexCr isinya bukan dummy item, dan diasumsikan jenis item di indexCr dan indexInv sama
    Item* temp = this->collection[indexCr.first][indexCr.second];
    Item* srcItem = inventory(indexInv.first, indexInv.second);
    this->makeDummy(indexCr.first, indexCr.second);

    if(srcItem->checkDummy()) {
        inventory.setItemByIndex(temp, indexInv.first, indexInv.second);
    } else {
        if(temp->getTool()) {
            inventory.insertItem(temp);
        } else {
            ItemNonTool* castItem = static_cast<ItemNonTool*>(srcItem);
            (*castItem) += 1;
            inventory.setItemByIndex((Item*) castItem, indexInv.first, indexInv.second);
        }
    }
}
