#include "./Item.hpp"
#include <iostream>
using namespace std;

int main(){
    freopen("testresult.txt", "w", stdout);

    // Test Constructor
    // Dummy Item
    Item* dummyItem = new Item;
    ItemNonTool* dummyItemNT = new ItemNonTool;
    ItemTool* dummyItemT = new ItemTool;

    // Non Dummy Item
    ItemNonTool* itemNT = new ItemNonTool("birch_log", "log", 3);
    ItemNonTool* itemNT1 = new ItemNonTool("birch_log", "log", 4);
    ItemNonTool* itemNT2 = new ItemNonTool("wood_log", "log", 2);
    ItemNonTool* itemNT3 = new ItemNonTool("wood_plank", "plank", 2);

    ItemTool* itemT = new ItemTool("wood_axe", "axe", 1);
    ItemTool* itemT1 = new ItemTool("iron_axe", "axe", 1);
    ItemTool* itemT2 = new ItemTool("wood_axe", "axe", 1);
    ItemTool* itemT3 = new ItemTool("wood_rope", "rope", 1);

    cout << "Try operator==" << endl; 
    cout << "Hasil yang diharapkan: YES NO NO YES YES NO YES YES NO" << endl;
    cout << ((*dummyItem) == (*dummyItemNT) ? "YES" : " NO") << endl;
    cout << ((*dummyItem) == (*itemNT) ? "YES" : "NO") << endl;
    cout << ((*itemNT) == (*itemT) ? "YES" : "NO") << endl;
    cout << ((*itemNT) == (*itemNT1) ? "YES" : "NO") << endl;
    cout << ((*itemNT2) == (*itemNT1) ? "YES" : "NO") << endl;
    cout << ((*itemNT1) == (*itemNT3) ? "YES" : "NO") << endl;
    cout << ((*itemT) == (*itemT1) ? "YES" : "NO") << endl;
    cout << ((*itemT2) == (*itemT1) ? "YES" : "NO") << endl;
    cout << ((*itemT1) == (*itemT3) ? "YES" : "NO") << endl;

    cout << endl;

    cout << "Try operator&&" << endl;
    cout << "Hasil yang diharapkan: YES NO NO YES NO NO NO YES NO" << endl;
    cout << ((*dummyItem) & (*dummyItemNT) ? "YES" : " NO") << endl;
    cout << ((*dummyItem) & (*itemNT) ? "YES" : "NO") << endl;
    cout << ((*itemNT) & (*itemT) ? "YES" : "NO") << endl;
    cout << ((*itemNT) & (*itemNT1) ? "YES" : "NO") << endl;
    cout << ((*itemNT2) & (*itemNT1) ? "YES" : "NO") << endl;
    cout << ((*itemNT1) & (*itemNT3) ? "YES" : "NO") << endl;
    cout << ((*itemT) & (*itemT1) ? "YES" : "NO") << endl;
    cout << ((*itemT2) & (*itemT) ? "YES" : "NO") << endl;
    cout << ((*itemT1) & (*itemT3) ? "YES" : "NO") << endl;    

}   