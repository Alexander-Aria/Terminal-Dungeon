#include "player.hpp"
#include "inventory.hpp"
#include "utility.hpp"

#include <iostream>
#include <vector>

using std::cout;

bool InventoryAccess(Player &player, const BattleState &state){
    int opt = 0;   

    while(true){
        cout << "Gold : " << player.GetGold() << "\n";
        ShowInventory(player.GetInventory(), false);
        cout << "\n0 to come back.\n\n- ";
        NumInput(opt);

        if(opt > 0 && opt <= size(player.GetInventory().GetConsumables())){
            player.GetStats().GetHealth() += player.GetInventory().GetConsumables()[opt-1].GetHealthGain();
            player.GetStats().GetStrengthBoost() += player.GetInventory().GetConsumables()[opt-1].GetStrengthBoost();
            player.GetStats().GetDefenseBoost() += player.GetInventory().GetConsumables()[opt-1].GetDefenseBoost();
            cout << "You consumed " << player.GetInventory().GetConsumables()[opt-1].GetName() << "\n";

            player.GetInventory().GetConsumables().erase(player.GetInventory().GetConsumables().begin() + opt - 1);

            if(player.GetStats().GetHealth() > player.GetStats().GetMaxHealth()) player.GetStats().GetHealth() = player.GetStats().GetMaxHealth();
            if(state == BattleState::INBATTLE) return true;
        }

        else if(opt == 0) break;
        else cout << "Invalid Input!\n";
    }
    return false;
}

void StatsCheck(Stats &playerstats){
    cout << "\n_____________________________________________\n";
    cout << "STATS\n";
    cout << "Health = " << playerstats.GetHealth() << "\n";
    cout << "Max Health = " << playerstats.GetMaxHealth() << "\n";
    cout << "Strength = " << playerstats.GetStrength() << "\n";
    cout << "Defense = " << playerstats.GetDefense() << "\n\n";
}