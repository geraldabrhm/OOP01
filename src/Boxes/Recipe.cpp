#include "Boxes.hpp"
#include <iostream>

Recipe::Recipe(int row, int col) : Boxes(row, col) {
    Item* dummy = new Item();
    this->result = dummy;
}

Recipe& Recipe::operator=(const Recipe& recipe){
    delete result;
    this->result = new Item();
    this->result = recipe.getResult();
    return *this;
}

Recipe::~Recipe(){
    delete result;
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