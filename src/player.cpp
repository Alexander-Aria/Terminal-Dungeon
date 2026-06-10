#include "player.hpp"
#include "utility.hpp"

#include <iostream>

using std::cout;

bool InventoryAccess(Player &player, const BattleState &state){
    int itemnum = 1, opt = 0;   

    while(true){
        cout << "\n_____________________________________________\n";
        cout << "ITEMS\n";
        cout << "Gold : " << player.GetGold() << "\n\n";
        if(size(player.GetInventory().GetConsumables()) == 0) cout << "You don't have any items!\n";
        else{
            cout << "_______________________\n";
            cout << "CONSUMABLES\n";
            cout << "Note : Booster consumables used outside battle will activate in the next battle.\n";

            for(auto &i : player.GetInventory().GetConsumables()){
                cout << itemnum << ". " << i.GetName() << " | " << i.GetDescription() << "\n";
                itemnum++;
            }
            itemnum = 1;
            cout << "\n0 to come back.\n\n- ";
            NumInput(opt);

            if(opt > 0 && opt <= itemnum){
                player.GetStats().GetHealth() += player.GetInventory().GetConsumables()[opt-1].GetHealthGain();
                player.GetStats().GetStrengthBoost() += player.GetInventory().GetConsumables()[opt-1].GetHealthGain();
                player.GetStats().GetDefenseBoost() += player.GetInventory().GetConsumables()[opt-1].GetHealthGain();

                if(player.GetStats().GetHealth() > player.GetStats().GetMaxHealth()) player.GetStats().GetHealth() = player.GetStats().GetMaxHealth();
                if(state == BattleState::INBATTLE) return true;
            }

            else if(opt == 0) break;
            else cout << "Invalid Input!\n";
        }
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