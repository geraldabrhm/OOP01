#include "Boxes.hpp"
#include <iostream>

Recipe::Recipe(int row, int col) : Boxes(3, 3) {}

//Getter Setter
Item* Recipe::getResult() const{
    return this->result;
}
void Recipe::setResult(Item* res){
    this->result = res;
}

//Method