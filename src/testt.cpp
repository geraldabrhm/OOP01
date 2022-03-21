#include <iostream>
#include <vector>
#include "./Item/Item.hpp"
using namespace std;

class test{
private:
    vector<Item*> kumpul;
public:   
    test(){
    }

    void addItem(Item* input){
        kumpul.push_back(input);
    }

    Item* getIndex(int ind){
        return kumpul[ind];
    }
};

bool compare(int* a, int* b){
    return a[0] == b[0];
}


int main(){
    test newClub;
    newClub.addItem(new ItemNonTool("akhirnya", "berhasil", 10));
    ItemNonTool* thi = static_cast<ItemNonTool*>(newClub.getIndex(0));

    cout << (thi->getQuantity()) << endl;
    (*thi) += 10;
    cout << (thi->getQuantity()) << endl;

    // vector<Item*>ok;

    // ok.push_back(new ItemNonTool);
    // cout << (ok[0]->isTool() ? "Yes" : "No" ) << endl;
    // ItemNonTool non1("a", "b", 1);

    // Item* item = dynamic_cast<Item*>(&non1);

    // ItemNonTool* non2 = dynamic_cast<ItemNonTool*>(item);
    // if(non2 == nullptr){
    //     cout << "NULL" << endl;
    // }else{
    //     (*non2) += 10;
    //     cout << non2->getQuantity() << endl;
    // }   
}

