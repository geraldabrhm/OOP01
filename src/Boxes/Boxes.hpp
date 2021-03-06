#ifndef __BOXES_H__
#define __BOXES_H__

#include "../Item/Item.hpp"
#include <vector>
#include <map>
#include "../Exception/Exception.hpp"
using namespace std;

class Boxes {
    protected:
        //Array for saving item
        vector<vector<Item*>>collection;
        
        int rowSize;
        int colSize;
    public:

        // ctor
        Boxes(int rowSize, int colSize); 
        
        // * Getter
        Item* getElmt(int row, int col) const;
        int getRowSize() const;
        int getColSize() const;

        // * Setter
        void setItemByIndex(Item* item, int indexRow, int indexCol);

        // * Method
        // * Get empty cell with lowest index, 
        // Lowest index dicek berdasarkan column nya dulu
        pair<int, int> getEmptyIndex();

        // * get index of item in the box if item in the box same as the parameter
        pair<int, int> getIndexSameItem(Item* item);

        // * insert Item di slot kosong dengan indeks terkecil
        void insertItem(Item* item); 
        
        // discard Item yang ada di index pada parameter sejumlah quantity
        void discardItem(int indexRow, int indexCol, int quantity);

        // Make item in particular index to be a dummy
        void makeDummy(int indexRow, int indexCol);
        
        // * Operator overloading
        // * Accessing element
        Item* operator()(int indexRow, int indexCol);
        
        void moveTo(Boxes& target, pair<int, int>indexSrc, vector<pair<int,int>> indexDst);

        virtual void displayBoxes()=0; // display all Item di Boxes
};

class Recipe : public Boxes {
    private:
        string result;
        int qty;
    public:
        //Constructor
        Recipe(int row, int col);

        //Getter Setter
        string getResult() const;
        void setResult(string res);
        int getQty() const;
        void setQty(int count);
        void displayBoxes();
        //Method
};

class Inventory : public Boxes {
    public:
        // * Ctor
        Inventory();
        
        // * Method
        
        // * Melakukan stack dari Item di indexSrc ke indexDst
        void stackItem(pair<int,int>indexSrc, pair<int,int>indexDst);
        
        // * Menggunakan Item yang terletak pada index parameter dan mengurangi durabilitynya 
        void useItem(int indexRow, int indexCol); 
        
        // * display all Item di Inventory
        void displayBoxes();  
};

class Crafting : public Boxes {
    private:
        pair<string,int> checkRecipe(Recipe recipe, bool isReverse);
    public:
        Crafting();
        int getBlockCount();
        pair<string,int> craftResult(map<int,vector<Recipe>> listRecipe); // Menghasilkan Item hasil jika susunan craftable
        void displayBoxes(); // display all Item di Inventory
};

#endif // __BOXES_H__