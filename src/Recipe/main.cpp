#include "Recipe.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

int main(){
    string line, elmt, result;
    char space_char = ' ';
    int row, col;
    int res_quantity, i, j;
    ifstream testFile("./test.txt");
    testFile >> row >> col;
    getline(testFile, line);
    Recipe rec(row,col);
    for (i = 0; i < row; i++){
        getline(testFile,line);
        stringstream sstream(line);
        j = 0;
        while (getline(sstream, elmt, space_char)){
            rec.insertElmt(i,j,elmt);
            j++;
        }
    }
    testFile >> result >> res_quantity;
    rec.setResult(result);
    rec.setQuantity(res_quantity);

    cout << "TEST VECTOR" << endl;
    vector<vector<string>> con = rec.getContainer();
    for (i = 0; i < con.size(); i++){
        vector<string> con2 = con.at(i);
        for (j = 0; j < con2.size(); j++){
            cout << con2.at(j) << " ";
        }
        cout << endl;
    }
}