#include "Recipe.hpp"
#include <iostream>

Recipe::Recipe(int row, int col) : rowSize(row), colSize(col){
    //Mengisi vector dengan string kosong
    string placeholder = "";

    vector<string> rows(colSize, placeholder);
    this->recipe = vector<vector<string>>(rowSize, rows);
}

//Getter Setter
vector<vector<string>> Recipe::getContainer() const{
    return this->recipe;
}
int Recipe::getRowSize() const{
    return this->rowSize;
}
int Recipe::getColSize() const{
    return this->colSize;
}
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
void Recipe::insertElmt(int row, int col, string str){
    if (row >= this->getRowSize() || col >= this->getColSize()){
        cout << "Index out of range";
    } else { 
        this->recipe[row][col] = str;
    }
}