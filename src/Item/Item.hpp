#ifndef _ITEM_
#define _ITEM_

#include <string>
#include <iostream>
#include "../Exception/Exception.hpp"
using namespace std;

/**
    * TODO: 1. Buat Map di main atau singleton buat nyimpen nama sama Id item -> Dapet dari config {"OAK_WOOD" : 1, ""}
    *       2. Buat Map di main atau singleton buat nyimpen nama sama tipe -> Dapet dari config
    *       3. Buat array nyimpen yang tool sama non tool
*/

// Consturct oak_wood -> masukin ke inventory 
// Ini tuh gak ada id, sementara id itu dapetnya dari config

// Buat map di main -> Nyimpen pasangan nama sama id

const int MAX_QUANTITY = 64;

class Item{
protected:
    string name;
    string type;
    bool isTool;
    int quantity;
public:
    // * Default Constructor -> Dummy Item, name = "-", type = "-"
    Item();
    Item(string name, string type, int quantity, bool isTool);


    // * Getter 
    string getName() const;
    string getType() const;
    int getQuantity() const;
    bool getTool() const;

    // * Check apakah item berupa dummy item (True jika dummy)
    bool checkDummy() const;

    // * Menentukan apakah Tool atau non Tool

    // * Mencetak ke layar
    virtual void print() const;
    
    // * Operator overloading
    
    // * Mengecek apakah tipe nya sama
    friend bool operator==(const Item& item1, const Item& item2);
    // * Mengecek apakah benda yang sama (tipe dan nama nya sama)
    friend bool operator&(const Item& item1, const Item& item2);

    friend ostream& operator<<(ostream& out, const Item& item);
};

class ItemTool: public Item{
private:
    int durability;
public:
    ItemTool();
    ItemTool(string name, string type);

    // * Getter
    int getDurability() const;

    // * Mengurangi durability;
    void reduceDurability();
    
    // * Stack durability of two ItemTool with the same name and type
    ItemTool& operator+(const ItemTool& item2);

    // * Mencetak item
    void print() const;
};

class ItemNonTool: public Item{
public:
    ItemNonTool();
    ItemNonTool(string name, string type, int quantity);

    // * Operator overloading
    // * Menambahkan item
    ItemNonTool& operator+=(const ItemNonTool& item);
    ItemNonTool& operator+=(const int& quantity);
    ItemNonTool& operator-=(const int& quantity);

    // Method

    // * Mengecek apakah item masih memiliki slot untuk ditambah
    int slotAvailable() const;
    
    // * Mengecek apakah item mencukupi untuk dibuang
    bool isEnough(int discard) const;

    // * Mencetak item
    void print() const;
};

#endif