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

bool operator==(const Item& item1, const string type){
  return item1.getType() == type;
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
bool Item::getTool() const {
  return this->isTool;
}

// * Check apakah item berupa dummy item (True jika dummy)
bool Item::checkDummy() const {
  return this->name == "-";
}

void Item::print() const{
    cout << "[ " << this->name << " "<< this->type << " Quantity: " << this->quantity << " ] ";
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

// * Set durability
ItemTool& ItemTool::operator+(const ItemTool& item2){
  ItemTool* newItem = new ItemTool(this->name, this->type);
  int newDura = item2.getDurability() + this->durability;

  while(newItem->getDurability() != min(10, newDura)){
    newItem->reduceDurability();
  }

  return (*newItem);
}

void ItemTool::print() const{
    cout << " T->";
    Item::print();
}

ItemNonTool::ItemNonTool() : Item(){

}

ItemNonTool::ItemNonTool(string name, string type, int quantity) : Item(name, type, quantity, false){

}

ItemNonTool& ItemNonTool::operator+=(const ItemNonTool& item){
    this->quantity += min(item.getQuantity(), this->slotAvailable());
    return *this;
}

ItemNonTool& ItemNonTool::operator+=(const int& quantity){
  if(this->slotAvailable() >= quantity){
    this->quantity += quantity;
    return *this;
  }else{
    ArithmeticException* exc = new ArithmeticException(quantity, this->slotAvailable());
    throw exc;
  }
}

ItemNonTool& ItemNonTool::operator-=(const int& quantity){
  if(this->isEnough(quantity)){
    this->quantity -= quantity;
    return *this;
  }else{
    ArithmeticException* exc = new ArithmeticException(quantity, this->quantity);
    throw exc;
  }
}

void ItemNonTool::print() const{
    cout << " NT ->" ;
    Item::print();
}

int ItemNonTool::slotAvailable() const{
   return (MAX_QUANTITY - this->quantity);
}

bool ItemNonTool::isEnough(int discard) const{
    if(this->quantity >= discard){
        return true;
    }
    return false;
}