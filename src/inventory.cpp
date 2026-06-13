#include "inventory.hpp"

#include <iostream>
using std::cout;

void ShowInventory(Inventory &inventory, bool showvalue){
    int itemnum = 1;

    if(size(inventory.GetConsumables()) == 0) cout << "You don't have any items!\n";
    else{
        cout << "_______________________\n";
        cout << "CONSUMABLES\n";
        cout << "Note : Booster consumables used outside battle will activate in the next battle.\n";

        for(auto &i : inventory.GetConsumables()){
            cout << itemnum << ". " << i.GetName() << " | " << i.GetDescription();
            if(showvalue) cout << "| Price : " << i.GetValue();
            cout << "\n";
            itemnum++;
        }
    }
}

void ShowEquipment(Inventory &inventory, bool showvalue){
    cout << "_______________________\n";
    cout << "EQUIPMENTS\n";
    cout << "Weapon : " << inventory.GetWeapon().GetName() << " | " << inventory.GetWeapon().GetDescription();
    if(showvalue) cout << " | Value : " << inventory.GetWeapon().GetValue();
    cout << "\n";
    cout << "Armor : " << inventory.GetArmor().GetName() << " | " << inventory.GetArmor().GetDescription();
    if(showvalue) cout << " | Value : " << inventory.GetArmor().GetValue();
    cout << "\n";
}