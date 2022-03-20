#ifndef __BOXES_H__
#define __BOXES_H__

#include "../Item/item.hpp"
#include <vector>
using namespace std;
class Crafting;

class Boxes {
    protected:
        vector <vector<pair<ItemNonTool, ItemTool>>> collection;
        const int rowSize;
        const int colSize;
    public:
        Boxes(int rowSize, int colSize); // ctor
        virtual void displayBoxes()=0; // display all Item di Boxes
        pair<int, int> getEmptyIndex();
        void insertItem(ItemTool &item, int quantity); // insert Item di slot kosong dengan indeks terkecil
        void insertItem(ItemNonTool &item, int quantity); // insert Item di slot kosong dengan indeks terkecil
        void discardItem(int indexRow, int indexCol, int quantity); // discard Item yang ada di index pada parameter sejumlah quantity
        pair<ItemNonTool,ItemTool>& operator()(int indexRow, int indexCol);
        void makePairDummy(int indexRow, int indexCol);
};

class Inventory : public Boxes {
    public:
        Inventory();// ctor
        void stackItem(int indexSrc[], int indexDst[]);  // melakukan stack dari Item di indexSrc ke indexDst jika sama
        void useItem(int indexRow, int indexCol); // Menggunakan Item yang terletak pada index parameter dan mengurangi durabilitynya
        void displayBoxes(); // display all Item di Inventory
        void exportInventory(); // ekspor inventory ke inventory.txt, belum tau dijadiin method atau kerjain di main
        void moveToCrafting(Crafting &crafting, int indexSrc[], int indexDst[]); // memindahkan Item dari inventory ke crafting
};

class Crafting : public Boxes {
    public:
        Crafting();
        bool craftAble(); // Memvalidasi susunan Item yang ada di Crafting Table ada di resep atau tidak
        Item* craftResult(); // Menghasilkan Item hasil jika susunan craftable
        void displayBoxes(); // display all Item di Inventory
        void moveToInventory(Inventory &inventory, int indexSrc, int indexDst); // memindahkan Item dari crafting ke inventory
};

#endif // __BOXES_H__