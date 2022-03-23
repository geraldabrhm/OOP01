#include "Recipe.hpp"
#include <iostream>

Recipe::Recipe(int row, int col) : Boxes(row, col) {}

//Getter Setter
string Recipe::getResult() const{
    return this->result;
}
void Recipe::setResult(string res){
    this->result = res;
}
int Recipe::getQuantity() const{
    return this->res_quantity;
}
void Recipe::setQuantity(int q){
    this->res_quantity = q;
}

//Method