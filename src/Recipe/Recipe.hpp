#ifndef __RECIPE_H__
#define __RECIPE_H__

#include <string>
#include <vector>
using namespace std;

class Recipe {
    private:
        vector<vector<string>>recipe;

        const int rowSize;
        const int colSize;

        string result;
        int res_quantity;
    public:
        //Constructor
        Recipe(int row, int col);

        //Getter Setter
        vector<vector<string>> getContainer() const;
        int getRowSize() const;
        int getColSize() const;
        string getResult() const;
        void setResult(string res);
        int getQuantity() const;
        void setQuantity(int q);

        //Method
        void insertElmt(int row, int col, string str);
};

#endif //__RECIPE_H__