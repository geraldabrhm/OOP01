#include "Item.hpp"

// * Default Constructor -> Dummy Item, name = "-", type = "-"
Item::Item() {
  this->name = "-";
  this->type = "-";
  this->quantity = 0;
}
Item::Item(string name, string type, int quantity) {
  this->name = name;
  this->type = type;
  this->quantity = quantity;
}

// * Operator overloading
// * Mengecek apakah tipe nya sama
bool operator==(const Item& item1, const Item& item2) {
  return item1.getType() == item2.getType();
}


bool operator&(const Item& item1, const Item& item2)
{
  return (item1.getType() == item2.getType() && item1.getName() == item2.getName());
}


// * Methods

// * Getter 
string Item::getName() const {
  return this->name;
}
string Item::getType() const {
  return this->type;
}
int Item::getQuantity() const {
  return this->quantity;
}

// * Check apakah item berupa dummy item (True jika dummy)
bool Item::checkDummy() const {
  return this->name == "-";
}

bool Item::isTool() const{
  return false;
}

// ItemTool
ItemTool::ItemTool() : Item() {
  this->durability = -1;
}
ItemTool::ItemTool(string name, string type, int quantity) : Item(name, type, 1) {
  this->durability = 10;
}

// * Getter
int ItemTool::getDurability() const {
  return this->durability;
}

// * Mengurangi durability;
void ItemTool::reduceDurability() {
  this->durability--;
}
bool ItemTool::isTool() const{
  return true;
}

ItemNonTool::ItemNonTool() : Item(){

}

ItemNonTool::ItemNonTool(string name, string type, int quantity) : Item(name, type, quantity){

}

// ! Untuk tiap method overloading, pastiin udah memenuhi syarat baru dipakai
// ! I.S. Syarat operator terpenuhi -> Untuk penjumlahan masih ada slot dan untuk pengurangn jumlah untuk dibuang mencukupi
ItemNonTool& ItemNonTool::operator+=(const ItemNonTool& item){
    this->quantity += item.getQuantity();
    return *this;
}

ItemNonTool& ItemNonTool::operator+=(const int& quantity){
    this->quantity += quantity;
    return *this;
}

ItemNonTool& ItemNonTool::operator-=(const int& quantity){
    this->quantity -= quantity;
    return *this;
}

bool ItemNonTool::isTool() const{
    return false;
}

bool ItemNonTool::isAvailable() const{
   return this->quantity < 64;
}

bool ItemNonTool::isEnough(int discard) const{
    if(this->quantity >= discard){
        return true;
    }
}