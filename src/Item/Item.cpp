#include "./Item.hpp"

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

bool ItemNonTool::isTool(){
    return false;
}

bool ItemNonTool::isAvailable(ItemNonTool item){
    if(this->quantity + item.getQuantity() <= 64 ){
        return true;
    }else{
        return false;
    }
}

bool ItemNonTool::isEnough(int discard){
    if(this->quantity >= discard){
        return true;
    }
}