#ifndef _ITEM_
#define _ITEM_

#include <string>
using namespace std;

/**
    * TODO: 1. Buat Map di main atau singleton buat nyimpen nama sama Id item -> Dapet dari config {"OAK_WOOD" : 1, ""}
    *       2. Buat Map di main atau singleton buat nyimpen nama sama tipe -> Dapet dari config
    *       3. Buat array nyimpen yang tool sama non tool
*/

// Consturct oak_wood -> masukin ke inventory 
// Ini tuh gak ada id, sementara id itu dapetnya dari config

// Buat map di main -> Nyimpen pasangan nama sama id

class Item{
protected:
    string name;
    string type;
    int quantity;
public:
    // * Default Constructor -> Dummy Item, name = "-", type = "-"
    Item();
    Item(string name, string type, int quantity);

    // * Operator overloading
    // * Mengecek apakah tipe nya sama
    friend bool operator==(const Item& item1, const Item& item2);

    // * Methods

    // * Getter 
    string getName() const;
    string getType() const;
    int getQuantity() const;

    // * Check apakah item berupa dummy item (True jika dummy)
    bool checkDummy() const;

    // * Menentukan apakah Tool atau non Tool
    bool isTool();
};

class ItemTool: public Item{
private:
    int durability;
public:
    ItemTool();
    ItemTool(string name, string type, int quantity, int durability);

    // * Getter
    int getDurability() const;

    // * Mengurangi durability;
    void reduceDurability();
    bool isTool();
};

class ItemNonTool: public Item{
public:
    ItemNonTool();
    ItemNonTool(string name, string type, int quantity);

    // * Operator overloading
    // * Menambahkan item
    ItemNonTool& operator+(const ItemNonTool& item);
    ItemNonTool& operator+(const int& quantity);
    ItemNonTool& operator-(const int& quantity);

    // Method

    bool isTool();
    // * Mengecek apakah item masih memiliki slot untuk ditambah
    bool isAvailable(ItemNonTool item);
    
    // * Mengecek apakah item mencukupi untuk dibuang
    bool isEnough(int discard);
};

#endif