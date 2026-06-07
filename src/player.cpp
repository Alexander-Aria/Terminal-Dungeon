#include "player.hpp"
#include "utility.hpp"

#include <iostream>

using std::cout;

void InventoryAccess(Player &player){
    int itemnum = 1, opt = 0;   

    cout << "\n_____________________________________________\n";
    cout << "CONSUMABLES\n";
    cout << "Gold : " << player.GetGold() << "\n\n";
    if(size(player.GetInventory().GetConsumables()) == 0) cout << "You don't have any consumables!\n";
    else{
        for(auto &i : player.GetInventory().GetConsumables()){
            cout << itemnum << ". " << i.GetName() << "\n";
            itemnum++;
        }
        itemnum = 1;
        cout << "\n0 to come back.\n\n- ";
        NumInput(opt);
        if(opt > 0 && opt <= itemnum){
            player.GetStats().GetHealth() += player.GetInventory().GetConsumables()[opt-1].GetHealth();
            if(player.GetStats().GetHealth() > player.GetStats().GetMaxHealth()) player.GetStats().GetHealth() = player.GetStats().GetMaxHealth();
        }
        else if(opt == 0);
        else cout << "Invalid Input!\n";
    }
}

void StatsCheck(Stats &playerstats){
    cout << "\n_____________________________________________\n";
    cout << "STATS\n";
    cout << "Health = " << playerstats.GetHealth() << "\n";
    cout << "Max Health = " << playerstats.GetMaxHealth() << "\n";
    cout << "Strength = " << playerstats.GetStrength() << "\n";
    cout << "Defense = " << playerstats.GetDefense() << "\n\n";
}