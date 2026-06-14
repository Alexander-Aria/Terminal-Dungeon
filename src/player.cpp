#include "player.hpp"
#include "inventory.hpp"
#include "utility.hpp"

#include <iostream>
#include <vector>

using std::cout;

void Player::LevelUp(){
    while(exp >= 250){
        level++;
        GetStats().GetMaxHealth() += 20;
        GetStats().GetHealth() = GetStats().GetMaxHealth();
        GetStats().GetRawDefense() += 2;
        GetStats().GetRawStrength() += 2;
        exp -= 250;
        std::cout << "you leveled up to level " << level << "!\n\n";
    }
}

bool InventoryAccess(Player &player, const BattleState &state){
    int opt = 0;   

    while(true){
        cout << "Gold : " << player.GetGold() << "\n";
        ShowEquipment(player.GetInventory(), false);
        ShowInventory(player.GetInventory(), false);
        cout << "\n0 to come back.\n\n- ";
        NumInput(opt);

        if(opt > 0 && opt <= size(player.GetInventory().GetConsumables())){
            player.GetStats().GetHealth() += player.GetInventory().GetConsumables()[opt-1].GetHealthGain();
            player.GetStats().GetTempStrengthBoost() += player.GetInventory().GetConsumables()[opt-1].GetTempStrengthBoost();
            player.GetStats().GetTempDefenseBoost() += player.GetInventory().GetConsumables()[opt-1].GetTempDefenseBoost();
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
    cout << "Strength = " << playerstats.GetRawStrength() << " + " << playerstats.GetStrengthBuff() << "\n";
    cout << "Defense = " << playerstats.GetRawDefense() << " + " << playerstats.GetDefenseBuff() << "\n\n";
}