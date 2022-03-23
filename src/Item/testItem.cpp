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

    ItemTool* itemT = new ItemTool("wood_axe", "axe");
    ItemTool* itemT1 = new ItemTool("iron_axe", "axe");
    ItemTool* itemT2 = new ItemTool("wood_axe", "axe");
    ItemTool* itemT3 = new ItemTool("wood_rope", "rope");

    cout << "Try operator==" << endl; 
    cout << "Hasil yang diharapkan: YES NO NO YES YES NO YES YES NO" << endl;
    cout << ((*dummyItem) == (*dummyItemNT) ? "YES" : "NO") << endl;
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
    cout << ((*dummyItem) & (*dummyItemNT) ? "YES" : "NO") << endl;
    cout << ((*dummyItem) & (*itemNT) ? "YES" : "NO") << endl;
    cout << ((*itemNT) & (*itemT) ? "YES" : "NO") << endl;
    cout << ((*itemNT) & (*itemNT1) ? "YES" : "NO") << endl;
    cout << ((*itemNT2) & (*itemNT1) ? "YES" : "NO") << endl;
    cout << ((*itemNT1) & (*itemNT3) ? "YES" : "NO") << endl;
    cout << ((*itemT) & (*itemT1) ? "YES" : "NO") << endl;
    cout << ((*itemT2) & (*itemT) ? "YES" : "NO") << endl;
    cout << ((*itemT1) & (*itemT3) ? "YES" : "NO") << endl;    

    cout << endl;
    cout << "Try Getter" << endl << endl;

    cout << "Try getName" << endl;
    cout << "Hasil yang diharapkan: - birch_log iron_axe" << endl;
    cout << dummyItemNT->getName() << endl;
    cout << itemNT1->getName() << endl;
    cout << itemT1->getName() << endl;

    cout << endl;

    cout << "Try getType" << endl;
    cout << "Hasil yang diharapkan: - log axe" << endl;
    cout << dummyItemNT->getType() << endl;
    cout << itemNT1->getType() << endl;
    cout << itemT1->getType() << endl;

    cout << endl;

    cout << "Try getQuantity" << endl;
    cout << "Hasil yang diharapkan: 0 4 1" << endl;
    cout << dummyItemNT->getQuantity() << endl;
    cout << itemNT1->getQuantity() << endl;
    cout << itemT1->getQuantity() << endl;
    
    cout << endl;

    cout << "Try checkDummy" << endl;
    cout << "Hasil yang diharapkan: YES NO NO" << endl;
    cout << (dummyItem->checkDummy() ? "YES" : "NO") << endl;
    cout << (itemNT1->checkDummy() ? "YES" : "NO") << endl;
    cout << (itemT1->checkDummy() ? "YES" : "NO") << endl;
    
    cout << endl;

    cout << "Try operator<<" << endl;
    cout << (*dummyItem) << endl;
    cout << (*itemNT1) << endl;
    cout << (*itemT) << endl;

    cout << "Try getDurability" << endl;
    cout << "Hasil yang diharapkan -1 10" << endl;
    cout << dummyItemT->getDurability() << endl;
    cout << itemT1->getDurability() << endl;

    cout << endl;

    cout << "Try reduceDurability" << endl;
    cout << "Hasil yang diharapkan 9" << endl;
    itemT1->reduceDurability();
    cout << itemT1->getDurability() << endl;

    cout << endl;
    cout << "Try operator+=" << endl;
    cout << "Hasil yang diharapkan 6 7" << endl;
    (*itemNT) += (*itemNT1);
    (*itemNT1) += 2;
    cout << itemNT1->getQuantity() << endl;
    cout << itemNT->getQuantity() << endl;

    cout << endl;
    
    cout << "Try operator-=" << endl;
    cout << "Hasil yang diharapkan 3 0" << endl;
    (*itemNT) -= 4;
    (*itemNT1) -= 6;
    cout << itemNT->getQuantity() << endl;
    cout << itemNT1->getQuantity() << endl;

    cout << endl;

    cout << "Try slotAvailable" << endl;
    cout << "Hasil yang diharapkan 61 64" << endl;
    cout << itemNT->slotAvailable() << endl;
    cout << itemNT1->slotAvailable() << endl;
    
    cout << endl;

    cout << "Try isEnough" << endl;
    cout << "Hasil yang diharapkan YES NO YES" << endl;

    cout << ((*itemNT).isEnough(2) ? "YES" : "NO") << endl;
    cout << ((*itemNT).isEnough(5) ? "YES" : "NO") << endl;
    cout << ((*itemNT1).isEnough(0) ? "YES" : "NO") << endl;
}   