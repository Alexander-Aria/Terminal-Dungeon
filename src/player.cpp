#include "player.hpp"
#include "enemy.hpp"
#include "inventory.hpp"
#include "utility.hpp"

#include <iostream>
#include <vector>

using std::cout;

void Player::MeleeOption(Player &player, Enemy &enemy){
    int opt = 0;
    bool finish = false;

    while(!finish){
        cout << "__________________________\n";
        cout << "Player Health : " << player.GetStats().GetHealth() << "\n";
        cout << enemy.GetName() << " Health : " << enemy.GetStats().GetHealth() << "\n\n";
        cout << "1. Attack\n2. Block\n3. Items\n4. Surrender\n\n- ";
        NumInput(opt);

        switch(opt){
            case 1:
                cout << "___________________________\n";
                cout << "0. Back\n1. Slash | High Damage\n2. Stab  | Medium Damage, Piercing (breaks defense)\n\n- ";
                NumInput(opt);
                switch(opt){
                    case 1:
                        cout << "You slashed the enemy!\n";
                        player.Slash(enemy);
                        finish = true;
                        break;
                    case 2:
                        cout << "You stabbed the enemy!\n";
                        player.Stab(enemy);
                        finish = true;
                        break;
                }
                break;
            case 2:
                cout << "You are blocking!\n\n";
                player.GetBlock() = player.Block();
                finish = true;
                break;
            case 3:
                if(player.InventoryAccess(BattleState::INBATTLE)) finish = true;
                break;
            case 4:
                player.GetStats().GetHealth() = 0;
                finish = true;
                break;
            default:
                cout << "Invalid Input!\n\n";
        }
    }
}

void Player::RangedOption(Player &player, Enemy &enemy){
    int opt = 0;
    bool finish = false;

    while(!finish){
        cout << "__________________________\n";
        cout << "Player Health : " << player.GetStats().GetHealth() << "\n";
        cout << enemy.GetName() << " Health : " << enemy.GetStats().GetHealth() << "\n\n";
        cout << "1. Shoot | Medium Damage, Piercing (breaks defense)\n2. Charge | multiplies shot damage by 3, resets after a shot/damaged\n3. Items\n4. Surrender\n\n- ";
        NumInput(opt);

        switch(opt){
            case 1:
                if(player.GetCharge() == 0) cout << "You shoot the enemy!\n";
                else cout << "You released your charge into the enemy!\n";
                player.Shoot(enemy);
                finish = true;
                break;
            case 2:
                cout << "You charged your weapon!\n";
                player.Charge(player.GetCharge());
                finish = true;
                break;
            case 3:
                if(player.InventoryAccess(BattleState::INBATTLE)) finish = true;
                break;
            case 4:
                player.GetStats().GetHealth() = 0;
                finish = true;
                break;
            default:
                cout << "Invalid Input!\n\n";
        }
    }
}

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
        if(GetUsingWeapon() == WeaponType::MELEE) cout << "Using : Melee Weapon\n\n";
        else if(GetUsingWeapon() == WeaponType::RANGED) cout << "Using : Ranged Weapon\n\n";

        ShowConsumables(GetInventory(), false);
        cout << "\n-1 to switch weapon (it will cost a turn in battle)\n";
        cout << "0 to come back.\n\n- ";
        NumInput(opt);

        if(opt > 0 && opt <= size(GetInventory().GetConsumables())){
            GetStats().GetHealth() += GetInventory().GetConsumables()[opt-1].GetHealthGain();
            GetStats().GetTempStrengthBoost() += GetInventory().GetConsumables()[opt-1].GetTempStrengthBoost();
            GetStats().GetTempDefenseBoost() += GetInventory().GetConsumables()[opt-1].GetTempDefenseBoost();
            cout << "\nYou consumed " << GetInventory().GetConsumables()[opt-1].GetName() << "\n\n";

            GetInventory().GetConsumables().erase(GetInventory().GetConsumables().begin() + opt - 1);

            if(GetStats().GetHealth() > GetStats().GetMaxHealth()) GetStats().GetHealth() = GetStats().GetMaxHealth();
            if(state == BattleState::INBATTLE) return true;
        }

        else if(opt == 0) break;
        else if(opt == -1){
            if(SwitchWeapon() && state == BattleState::INBATTLE) return true;
        }
        else cout << "\nInvalid Input!\n\n";
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