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
        cout << "you leveled up to level " << level << "!\n\n";
    }
}

bool Player::InventoryAccess(const BattleState &state){
    int opt = 0;   

    while(true){
        cout << "Gold : " << GetGold() << "\n";

        ShowEquipment(GetInventory(), false);
        if(GetUsingWeapon() == WeaponType::MELEE) cout << "Using : Melee Weapon\n";
        else if(GetUsingWeapon() == WeaponType::RANGED) cout << "Using : Ranged Weapon\n";

        ShowConsumables(GetInventory(), false);
        cout << "\n-1 to switch weapon\n";
        cout << "0 to come back.\n\n- ";
        NumInput(opt);

        if(opt > 0 && opt <= size(GetInventory().GetConsumables())){
            GetStats().GetHealth() += GetInventory().GetConsumables()[opt-1].GetHealthGain();
            GetStats().GetTempStrengthBoost() += GetInventory().GetConsumables()[opt-1].GetTempStrengthBoost();
            GetStats().GetTempDefenseBoost() += GetInventory().GetConsumables()[opt-1].GetTempDefenseBoost();
            cout << "You consumed " << GetInventory().GetConsumables()[opt-1].GetName() << "\n";

            GetInventory().GetConsumables().erase(GetInventory().GetConsumables().begin() + opt - 1);

            if(GetStats().GetHealth() > GetStats().GetMaxHealth()) GetStats().GetHealth() = GetStats().GetMaxHealth();
            if(state == BattleState::INBATTLE) return true;
        }

        else if(opt == 0) break;
        else if(opt == -1) SwitchWeapon();
        else cout << "Invalid Input!\n";
    }
    return false;
}

void Player::StatsCheck(){
    cout << "\n_____________________________________________\n";
    cout << "STATS\n";
    cout << "Health = " << GetStats().GetHealth() << "\n";
    cout << "Max Health = " << GetStats().GetMaxHealth() << "\n";
    cout << "Strength = " << GetStats().GetRawStrength() << " + " << GetStats().GetStrengthBuff() << "\n";
    cout << "Defense = " << GetStats().GetRawDefense() << " + " << GetStats().GetDefenseBuff() << "\n\n";
}