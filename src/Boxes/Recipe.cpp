#include "Boxes.hpp"
#include <iostream>

Recipe::Recipe(int row, int col) : Boxes(row, col) {
    this->result = "";
    this->qty = 0;
}

//Getter Setter
string Recipe::getResult() const{
    return result;
}
void Recipe::setResult(string res){
    this->result = res;
}
int Recipe::getQty() const{
    return qty;
}
void Recipe::setQty(int count){
    qty = count;
}

//Method
void Recipe::displayBoxes() {/*do nothing;*/}