#include "inventory.hpp"

#include <iostream>
using std::cout;

void ShowInventory(Inventory &inventory, bool shop){
    int itemnum = 1;

    if(size(inventory.GetConsumables()) == 0) cout << "You don't have any items!\n";
    else{
        cout << "_______________________\n";
        cout << "CONSUMABLES\n";
        cout << "Note : Booster consumables used outside battle will activate in the next battle.\n";

        for(auto &i : inventory.GetConsumables()){
            cout << itemnum << ". " << i.GetName() << " | " << i.GetDescription();
            if(shop) cout << "| Price : " << i.GetValue();
            cout << "\n";
            itemnum++;
        }
    }
}