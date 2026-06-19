#include "inventory.hpp"
#include "utility.hpp"

#include <iostream>
#include <memory>
using std::cout;

void ShowConsumables(Inventory &inventory, bool showvalue){
    int itemnum = 1;

    if(size(inventory.GetConsumables()) == 0) cout << "There are no consumables!\n";
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

    if(!showvalue && inventory.GetMelee() == "SOLD OUT") cout << "Melee : No Melee\n";
    else{
        cout << "Melee : " << inventory.GetMelee().GetName() << " | " << inventory.GetMelee().GetDescription();
        if(showvalue) cout << " | Value : " << inventory.GetMelee().GetValue();
        cout << "\n";
    }

    if(!showvalue && inventory.GetRanged() == "SOLD OUT") cout << "Ranged : No Ranged\n";
    else{
        cout << "Ranged : " << inventory.GetRanged().GetName() << " | " << inventory.GetRanged().GetDescription();
        if(showvalue) cout << " | Value : " << inventory.GetRanged().GetValue();
        cout << "\n";
    }
    
    cout << "Armor : " << inventory.GetArmor().GetName() << " | " << inventory.GetArmor().GetDescription();
    if(showvalue) cout << " | Value : " << inventory.GetArmor().GetValue();
    cout << "\n\n";
}