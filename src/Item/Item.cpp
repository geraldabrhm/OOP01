#include "Item.hpp"

// * Default Constructor -> Dummy Item, name = "-", type = "-"
Item::Item() {
  this->name = "-";
  this->type = "-";
  this->quantity = 0;
  this->isTool = false;
}
Item::Item(string name, string type, int quantity, bool isTool) {
  this->name = name;
  this->type = type;
  this->quantity = quantity;
  this->isTool = isTool;
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

ostream& operator<<(ostream& out, const Item& item){
    item.print();
    return out;
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

void Item::print() const{
    cout << this->name << endl;
    cout << this->type << endl;
    cout << "Quantity: " << this->quantity << endl;
}

// ItemTool
ItemTool::ItemTool() : Item() {
  this->durability = -1;
}
ItemTool::ItemTool(string name, string type) : Item(name, type, 1, true) {
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

void ItemTool::print() const{
    cout << "Item Tool" << endl;
    Item::print();
    cout << "Durability " << this->durability << endl;
}

ItemNonTool::ItemNonTool() : Item(){

}

ItemNonTool::ItemNonTool(string name, string type, int quantity) : Item(name, type, quantity, false){

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

void ItemNonTool::print() const{
    cout << "Item Non Tool" << endl;
    Item::print();
}

int ItemNonTool::slotAvailable() const{
   return max(-1, (MAX_QUANTITY - this->quantity));
}

bool ItemNonTool::isEnough(int discard) const{
    if(this->quantity >= discard){
        return true;
    }
    return false;
}