#include "Boxes.hpp"
#include <iostream>

Recipe::Recipe(int row, int col) : Boxes(row, col) {
    Item* dummy = new Item();
    this->result = dummy;
}

//Getter Setter
Item* Recipe::getResult() const{
    return this->result;
}
void Recipe::setResult(Item* res){
    this->result = res;
}

//Method
void Recipe::displayBoxes() {/*do nothing;*/}