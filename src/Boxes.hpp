#ifndef __BOXES_H__
#define __BOXES_H__

#include "item.hpp"
#include <vector>
using namespace std;

class Boxes : Item {
    private:
        vector <Item> collection;
    public:
        Boxes(); // ctor
        virtual void displayBoxes()=0; // display all Item di Boxes
        void insertItem(Item item, int quantity); // insert Item di slot kosong dengan indeks terkecil
        void discardItem(int index, int quantity); // discard Item yang ada di index pada parameter sejumlah quantity
        bool checkEmpty(int index); // pengecekan apakah Box dengan index pada parameter kosong atau tidak
        void setSize(int inputSize);
        void setMaxPerBox(int inputMaxPerBox);
};

class Inventory : Boxes {
    private:
        const static int size = 27;
        const static int maxPerBox = 64;
    public:
        Inventory();// ctor
        void stackItem(int indexSrc, int indexDst);  // melakukan stack dari Item di indexSrc ke indexDst jika sama
        bool equalityItems(int index1, int index2); // mengecek apakah Item pada index1 dan index2 sama (nama, tipe)
        void useItem(int index); // Menggunakan Item yang terletak pada index parameter dan mengurangi durabilitynya
        void displayBoxes(); // display all Item di Inventory
        // void exportInventory(); // ekspor inventory ke inventory.txt, belum tau dijadiin method atau kerjain di main
};

class Crafting : Boxes {
    private:
        const static int size = 9;
        const static int maxPerBox = 1;
    public:
        Crafting();
        void craftItem(); // Melakukan craft item
        void displayBoxes(); // display all Item di Inventory
};

// Unhandled 
// (Poin 4 - Move dari inventory ke craft)
// (Poin 6 - Move dari craft ke inventory)


#endif // __BOXES_H__