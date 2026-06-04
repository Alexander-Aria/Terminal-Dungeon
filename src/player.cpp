#include "player.hpp"
#include "utility.hpp"

#include <iostream>

using std::cout;

void InventoryAccess(Player &player){
    int itemnum = 1, opt = 0;   

    if(size(player.GetInventory().GetConsumables()) == 0) cout << "You don't have any consumables!\n";
    else{
        for(auto &i : player.GetInventory().GetConsumables()){
            cout << itemnum << ". " << i.GetName() << "\n";
            itemnum++;
        }
        itemnum = 1;
        NumInput(opt);
        player.GetStats().GetHealth() += player.GetInventory().GetConsumables()[opt-1].GetHealth();
        if(player.GetStats().GetHealth() > player.GetStats().GetMaxHealth()) player.GetStats().GetHealth() = player.GetStats().GetMaxHealth();
    }
}