#include "./Boxes.hpp"


Crafting::Crafting() : Boxes(3,3) {}

Item* Crafting::craftResult(Recipe &resep)
{
    // for(int i = 0; i < this->rowSize; i++) {
    //     for(int j = 0; j < this->colSize; j++) {

    //     }
    // }
}


void Crafting::displayBoxes()
{
    for(int i = 0; i < this->getRowSize(); i++) {
        for(int j = 0; j < this->getColSize(); j++) {
            this->collection[i][j]->print();
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
            try {
                (*castItem) += 1;
            } catch(OperationFailedException *exe) {
                exe->printMessage();
            }
            inventory.setItemByIndex((Item*) castItem, indexInv.first, indexInv.second);
        }
    }
}
