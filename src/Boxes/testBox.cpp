#include "./Boxes.hpp"
#include <iostream>

int main(){
    freopen("testresult.txt", "w", stdout);

    Inventory* inventory = new Inventory;
    
    cout << "Try Getter" << endl;

    cout << endl;

    cout << "Try getRowSize" << endl;
    cout << "Hasil yang diharapkan 3" << endl;
    cout << inventory->getRowSize() << endl;

    cout << endl;
    
    cout << "Try getColSize" << endl;
    cout << "Hasil yang diharapkan 9" << endl;
    cout << inventory->getColSize() << endl;

    cout << endl;
    
    cout << "Try getEmpyIndex" << endl;
    pair<int,int> eIndex = inventory->getEmptyIndex();
    cout << "Hasil yang diharapkan 0 0" << endl;
    cout << eIndex.first << " " << eIndex.second << endl;


    //Create Item for testing
    ItemNonTool* itemNT = new ItemNonTool("birch_log", "log", 3);
    ItemNonTool* itemNT1 = new ItemNonTool("birch_log", "log", 4);
    ItemNonTool* itemNT2 = new ItemNonTool("wood_log", "log", 2);
    ItemNonTool* itemNT3 = new ItemNonTool("wood_plank", "plank", 2);

    ItemTool* itemT = new ItemTool("wood_axe", "axe");
    ItemTool* itemT1 = new ItemTool("iron_axe", "axe");
    ItemTool* itemT2 = new ItemTool("wood_axe", "axe");
    ItemTool* itemT3 = new ItemTool("wood_rope", "rope");

    cout << endl;
    
    cout << "Try InsertItem" << endl;
    cout << "Hasil yang diharapkan (berupa empty index) 0 7 " << endl;

    inventory->insertItem(itemNT); // 0 0
    inventory->insertItem(itemNT1); // 0 0
    inventory->insertItem(itemNT2); // 0 1
    inventory->insertItem(itemNT3); // 0 2

    inventory->insertItem(itemT); // 0 3
    inventory->insertItem(itemT1); // 0 4
    inventory->insertItem(itemT2); // 0 5
    inventory->insertItem(itemT3); // 0 6

    eIndex = inventory->getEmptyIndex();
    cout << eIndex.first << " " << eIndex.second << endl;

    cout << endl;
    
    cout << "Try Operator()" << endl;
    cout << "Hasil yang diharapkan birch_log 2 10 rope" << endl;

    ItemNonTool* checkNT1 = static_cast<ItemNonTool*>((*inventory)(0, 0));
    ItemNonTool* checkNT2 = static_cast<ItemNonTool*>((*inventory)(0, 2));

    ItemTool* check1 = static_cast<ItemTool*>((*inventory)(0, 4));
    ItemTool* check2 = static_cast<ItemTool*>((*inventory)(0, 6));

    cout << checkNT1->getName() << endl;
    cout << checkNT2->getQuantity() << endl;
    cout << check1->getDurability() << endl;
    cout << check2->getType() << endl;

    cout << endl;

    cout << "Try discardItem" << endl;
    cout << "Hasil yang diharapkan 5 0 dummy" << endl;

    inventory->discardItem(0, 0, 2);
    inventory->discardItem(0, 1, 2);

    checkNT1 = static_cast<ItemNonTool*>((*inventory)(0, 0));
    checkNT2 = static_cast<ItemNonTool*>((*inventory)(0, 1));

    cout << checkNT1->getQuantity() << endl;
    cout << checkNT2->getQuantity() << endl;
    cout << ((*inventory)(0,1)->checkDummy() ? "dummy" : "not dummy") << endl;

    cout << endl;

    cout << "Try stackItem" << endl;
    cout << "Hasil yang diharapkan 7 0" << endl;

    inventory->stackItem(make_pair(0,2), make_pair(0,0));
    // inventory->stackItem(make_pair(0,5), make_pair(0,0)); // error

    cout << (*inventory)(0,0)->getQuantity() << endl;
    cout << (*inventory)(0,2)->getQuantity() << endl;

    cout << endl;

    cout << "Try useItem" << endl;
    cout << "Hasil yang diharapkan 10 9" << endl;

    cout << static_cast<ItemTool*>((*inventory)(0,4))->getDurability() << endl;
    inventory->useItem(0,4);
    cout << static_cast<ItemTool*>((*inventory)(0,4))->getDurability() << endl;

    cout << endl;

    cout << "Try displayBoxes" << endl;
    
    inventory->displayBoxes();

    cout << endl;

    cout << "Try moveTo inventory to crafting" << endl;

    cout << "Try move ItemNonTool" << endl;
    Crafting* crafting = new Crafting;
    vector<pair<int,int>> indexDst;
    indexDst.push_back(make_pair(0,0));
    indexDst.push_back(make_pair(0,1));
    indexDst.push_back(make_pair(1,2));
    inventory->moveTo((*crafting), make_pair(0,0), indexDst);
    
    cout << "Inventory:" << endl;
    inventory->displayBoxes();
    cout << "Crafting:" << endl;
    crafting->displayBoxes();

    cout << endl << "Try move ItemTool" << endl;
    indexDst.clear();
    indexDst.push_back(make_pair(0,2));
    inventory->moveTo((*crafting), make_pair(0,3), indexDst);
    cout << "Inventory:" << endl;
    inventory->displayBoxes();
    cout << "Crafting:" << endl;
    crafting->displayBoxes();

    cout << endl;

    cout << "Try moveTo crafting to inventory" << endl;

    indexDst.clear();
    indexDst.push_back(make_pair(1,0));
    crafting->moveTo((*inventory), make_pair(0,0), indexDst);
    
    cout << "Inventory:" << endl;
    inventory->displayBoxes();
    cout << "Crafting:" << endl;
    crafting->displayBoxes();
}