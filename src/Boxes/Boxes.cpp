#include "Boxes.hpp"

Boxes::Boxes(int rowSize, int colSize) : rowSize(rowSize), colSize(colSize) {
    //Mengisi vector dengan dummy item
    Item* dummyItem = new Item();

    vector<Item*> in(colSize, dummyItem);
    this->collection = vector<vector<Item*>>(rowSize, in);
}

Item* Boxes::getElmt(int row, int col) const{
    return this->collection[row][col];
}

int Boxes::getRowSize() const{
    return this->rowSize;
}

int Boxes::getColSize() const{
    return this->colSize;
}

pair<int, int> Boxes::getEmptyIndex(){
    for(int i = 0; i < this->rowSize; i++) {
        for(int j = 0; j < this->colSize; j++) {
            if(collection[i][j]->checkDummy()){
                return make_pair(i, j);
            }
        }
    }
    pair<int, int> noEmptyIndex = make_pair(-1,-1);
    return noEmptyIndex;
}


pair<int, int> Boxes::getIndexSameItem(Item* item)
{
    for(int i = 0; i < this->getRowSize(); i++) {
        for(int j = 0; j < this->getColSize(); j++) {
            if(*(this->collection[i][j]) & (*item) && this->collection[i][j]->getQuantity()!=64) {
                pair<int, int> index = make_pair(i, j);
                return index;
            }
        }
    }
    pair<int, int> noItemExist = make_pair(-1,-1);
    return noItemExist;
}


void Boxes::insertItem(Item* item)
{
    // Dapet index isi boxes yang isinya item dengan nama dan tipe yg sama dengan parameter item
    pair<int, int> index = getIndexSameItem(item);
    if(index.first != -1 && !item->getTool()) { // Kasus kalau sudah ada item di inv dan item NonTool
        ItemNonTool* cast = static_cast<ItemNonTool*> (this->collection[index.first][index.second]);
        if(cast->getQuantity() + item->getQuantity() <=64) {
            (*cast) += item->getQuantity();
            this->collection[index.first][index.second] = (Item*) cast;
        }
        else {
            int quantity = item->getQuantity();
            quantity -= cast->slotAvailable();
            (*cast) += cast->slotAvailable();
            this->collection[index.first][index.second] = (Item*) cast;
            if(quantity >= 64) { // to handle case input quantity > 128
                Item* itemNew = new Item(item->getName(), item->getType(), quantity, item->getTool());
                this->insertItem(itemNew);
            }
        }
    } else { // Kasus jika tidak ada item yang sama di inv atau item adalah item tool
        pair<int, int> emptyBox = this->getEmptyIndex();
        int qty = item->getQuantity();
        if (qty > 64){
            Item* itemNew = new Item(item->getName(), item->getType(), 64, item->getTool());
            if(!(emptyBox.first == -1 || emptyBox.second == -1)) {
                this->collection[emptyBox.first][emptyBox.second] = itemNew;
            }
            this->insertItem(new Item(item->getName(), item->getType(), qty-64, item->getTool()));
        } else {
            if(!(emptyBox.first == -1 || emptyBox.second == -1)) {
                this->collection[emptyBox.first][emptyBox.second] = item;
            }
        }
    }
}

void Boxes::discardItem(int indexRow, int indexCol, int quantity)
{
    if(!this->collection[indexRow][indexCol]->getTool()){
        ItemNonTool* cast = static_cast<ItemNonTool*>(this->collection[indexRow][indexCol]);
        if(cast->getQuantity() >= quantity) {
            (*cast) -= quantity;
            this->collection[indexRow][indexCol] = (Item*) cast;
            if(cast->getQuantity() == 0) {
                makeDummy(indexRow, indexCol);
            }
            cout << "Item berhasil dibuang!!" << endl;
        } else {
            // Throw exception here (discard quantity > current quantity)
            cout << "Jumlah item tidak mencukupi!" << endl;
        }
    } else{ // Assuming it is already a dummy or a tool item (quantity fixed-size = 1)
        makeDummy(indexRow, indexCol);
        cout << "Item berhasil dibuang!!" << endl;
    }
}

void Boxes::setItemByIndex(Item* item, int indexRow, int indexCol)
{
    this->collection[indexRow][indexCol] = item;
}

void Boxes::makeDummy(int indexRow, int indexCol)
{
    Item* dummyItem = new Item();
    this->setItemByIndex(dummyItem, indexRow, indexCol);
}

Item* Boxes::operator()(int indexRow, int indexCol){
    return this->collection[indexRow][indexCol];
}

// Petunjuk penggunaan: kalau dari inv ke craft, vector size bisa >= 1. Tetapi kalau sebaliknya, size harus == 1
void Boxes::moveTo(Boxes& target, pair<int, int>indexSrc, vector<pair<int,int>> indexDst)
{
    Item* srcItem = this->collection[indexSrc.first][indexSrc.second];
    // Memastikan item indexSrc bukan dummy
    if(!srcItem->checkDummy()) {
        // Case kalau srcItem tool
        if(srcItem->getTool()) {
            // Menyimpan dstItem, mengubah target dengan src, dan src menjadi dummy
            Item* dstItem = target(indexDst[0].first, indexDst[0].second);
            target.setItemByIndex(srcItem, indexDst[0].first, indexDst[0].second);
            this->makeDummy(indexSrc.first, indexSrc.second);
            // Kasus kalau dstItem tidak dummy
            if(!dstItem->checkDummy()) {
                // dari crafting ke inventory, maka dst item akan tetap ke inventory (bukan crafting)
                if(target.getColSize() == 9) {
                    target.insertItem(dstItem);
                } else if (target.getColSize() == 3) { // dari inventory ke crafting, dst item akan ke inventory juga
                    this->insertItem(dstItem);
                }
            }
        } else {
            ItemNonTool* cast2 = static_cast<ItemNonTool*>(srcItem);
            int count = 0;

            for(int i = 0; i < indexDst.size(); i++) {
                ItemNonTool* cast = new ItemNonTool(srcItem->getName(), srcItem->getType(), 1);
                Item* dstItem = target(indexDst[i].first, indexDst[i].second);

                this->setItemByIndex((Item*) cast2, indexSrc.first, indexSrc.second);
                target.setItemByIndex((Item*) cast, indexDst[i].first, indexDst[i].second);
                
                if(!dstItem->checkDummy()) {
                    if(target.getColSize() == 9) {
                        target.insertItem(dstItem);
                    } else if(target.getColSize() == 3) {
                        this->insertItem(dstItem);
                    }
                }
                count++;
            }
            if(count == cast2->getQuantity()) {
                this->makeDummy(indexSrc.first, indexSrc.second);
            } else {
                (*cast2) -= count;
                this->setItemByIndex((Item*) cast2, indexSrc.first, indexSrc.second);
            }
        }
    }   
}
