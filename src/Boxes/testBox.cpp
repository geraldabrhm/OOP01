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
    cout << "Hasil yang diharapkan (berupa empty index) 0 8 " << endl;

    inventory->insertItem(itemNT); // 0 0
    inventory->insertItem(itemNT1); // 0 1
    inventory->insertItem(itemNT2); // 0 2
    inventory->insertItem(itemNT3); // 0 3

    inventory->insertItem(itemT); // 0 4
    inventory->insertItem(itemT1); // 0 5
    inventory->insertItem(itemT2); // 0 6
    inventory->insertItem(itemT3); // 0 7

    eIndex = inventory->getEmptyIndex();
    cout << eIndex.first << " " << eIndex.second << endl;

    cout << endl;
    
    cout << "Try Operator()" << endl;
    cout << "Hasil yang diharapkan birch_log 2 10 rope" << endl;

    ItemNonTool* checkNT1 = static_cast<ItemNonTool*>((*inventory)(0, 0));
    ItemNonTool* checkNT2 = static_cast<ItemNonTool*>((*inventory)(0, 3));

    ItemTool* check1 = static_cast<ItemTool*>((*inventory)(0, 4));
    ItemTool* check2 = static_cast<ItemTool*>((*inventory)(0, 7));

    cout << checkNT1->getName() << endl;
    cout << checkNT2->getQuantity() << endl;
    cout << check1->getDurability() << endl;
    cout << check2->getType() << endl;

    cout << endl;

    cout << "Try discardItem" << endl;
    cout << "Hasil yang diharapkan 1 1" << endl;

    inventory->discardItem(0, 0, 2);
    inventory->discardItem(0, 1, 3);

    checkNT1 = static_cast<ItemNonTool*>((*inventory)(0, 0));
    checkNT2 = static_cast<ItemNonTool*>((*inventory)(0, 1));

    cout << check1->getQuantity() << endl;
    cout << check2->getQuantity() << endl;

    cout << endl;
}