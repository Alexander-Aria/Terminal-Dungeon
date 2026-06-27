#include "player.hpp"
#include "enemy.hpp"
#include "inventory.hpp"
#include "utility.hpp"

#include <iostream>
#include <vector>

using std::cout;

bool Player::SwitchWeapon(){
    if(GetUsingWeapon() == WeaponType::MELEE && GetInventory().GetRanged() != "SOLD OUT"){
        GetUsingWeapon() = WeaponType::RANGED;
        cout << "Switched to ranged!\n\n";
    }
    else if(GetUsingWeapon() == WeaponType::RANGED && GetInventory().GetMelee() != "SOLD OUT"){
        GetUsingWeapon() = WeaponType::MELEE;
        cout << "Switched to melee!\n\n";
    }
    else{
        std::cout << "Unable to switch weapons!\n\n";
        return false;
    }
    UpdateBuff();
    return true;
}

void Player::ChangeEquipment(const Armor &armor){
    GetInventory().GetArmor() = armor;
    UpdateBuff();
}

void Player::ChangeEquipment(const Melee &melee){
    GetInventory().GetMelee() = melee;
    UpdateBuff();
}

void Player::ChangeEquipment(const Ranged &ranged){
    GetInventory().GetRanged() = ranged;
    UpdateBuff();
}


void Player::LevelUp(){
    while(exp >= 250){
        level++;
        GetStats().GetMaxHealth() += 20;
        GetStats().GetHealth() = GetStats().GetMaxHealth();
        GetStats().GetRawDefense() += 2;
        GetStats().GetRawStrength() += 2;
        exp -= 250;
        cout << "you leveled up to level " << level << "!\n";
        cout << "You health has been restored!\n\n";
    }
}

bool Player::InventoryAccess(const BattleState &state){
    int opt = 0;   

    while(true){
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
            cout << "\nYou consumed a " << GetInventory().GetConsumables()[opt-1].GetName() << ".\n\n";

            GetInventory().GetConsumables().erase(GetInventory().GetConsumables().begin() + opt - 1);
            MaxHealthCheck();
            
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
    cout << "Health = " << GetStats().GetHealth() << "/" << GetStats().GetMaxHealth() << "\n";
    cout << "Strength = " << GetStats().GetRawStrength() << " + " << GetStats().GetStrengthBuff() << "\n";
    cout << "Defense = " << GetStats().GetRawDefense() << " + " << GetStats().GetDefenseBuff() << "\n\n";
}

void Player::MeleeOption(Enemy &enemy){
    int opt = 0;
    bool finish = false;

    while(!finish){
        cout << "__________________________\n";
        cout << "Player Health : " << GetStats().GetHealth() << "/" << GetStats().GetMaxHealth();
        if(GetStats().GetTempStrengthBoost() > 0) cout << " (STR +" << GetStats().GetTempStrengthBoost() << ")";
        else if(GetStats().GetTempStrengthBoost() < 0) cout << " (STR " << GetStats().GetTempStrengthBoost() << ")";
        if(GetStats().GetTempDefenseBoost() > 0) cout << " (DEF +" << GetStats().GetTempDefenseBoost() << ")";
        else if(GetStats().GetTempDefenseBoost() < 0) cout << " (DEF " << GetStats().GetTempDefenseBoost() << ")";
        cout  << "\n";

        cout << enemy.GetName() << " Health : " << enemy.GetStats().GetHealth() << "/" << enemy.GetStats().GetMaxHealth();
        if(enemy.GetStats().GetTempStrengthBoost() > 0) cout << " (STR +" << enemy.GetStats().GetTempStrengthBoost() << ")";
        else if(enemy.GetStats().GetTempStrengthBoost() < 0) cout << " (STR " << enemy.GetStats().GetTempStrengthBoost() << ")";
        if(enemy.GetStats().GetTempDefenseBoost() > 0) cout << " (DEF +" << enemy.GetStats().GetTempDefenseBoost() << ")";
        else if(enemy.GetStats().GetTempDefenseBoost() < 0) cout << " (DEF " << enemy.GetStats().GetTempDefenseBoost() << ")";
        cout  << "\n\n";

        cout << "1. Attack\n2. Block\n3. Items\n4. Surrender\n\n- ";
        NumInput(opt);

        switch(opt){
            case 1:
                cout << "___________________________\n";
                cout << "0. Back\n1. Slash | High Damage\n2. Stab  | Medium Damage, Piercing (breaks defense)\n\n- ";
                NumInput(opt);
                switch(opt){
                    case 1:
                        cout << "\nYou slashed the enemy!\n";
                        Slash(enemy);
                        finish = true;
                        break;
                    case 2:
                        cout << "\nYou stabbed the enemy!\n";
                        Stab(enemy);
                        finish = true;
                        break;
                }
                break;
            case 2:
                cout << "\nYou are blocking!\n\n";
                GetBlock() = Block();
                finish = true;
                break;
            case 3:
                if(InventoryAccess(BattleState::INBATTLE)) finish = true;
                break;
            case 4:
                GetStats().GetHealth() = 0;
                finish = true;
                break;
            default:
                cout << "\nInvalid Input!\n\n";
        }
    }
}

void Player::RangedOption(Enemy &enemy){
    int opt = 0;
    bool finish = false;

    while(!finish){
        cout << "__________________________\n";
        cout << "Player Health : " << GetStats().GetHealth() << "/" << GetStats().GetMaxHealth();
        if(GetStats().GetTempStrengthBoost() > 0) cout << " (STR +" << GetStats().GetTempStrengthBoost() << ")";
        else if(GetStats().GetTempStrengthBoost() < 0) cout << " (STR " << GetStats().GetTempStrengthBoost() << ")";
        if(GetStats().GetTempDefenseBoost() > 0) cout << " (DEF +" << GetStats().GetTempDefenseBoost() << ")";
        else if(GetStats().GetTempDefenseBoost() < 0) cout << " (DEF " << GetStats().GetTempDefenseBoost() << ")";
        cout  << "\n";

        cout << enemy.GetName() << " Health : " << enemy.GetStats().GetHealth() << "/" << enemy.GetStats().GetMaxHealth();
        if(enemy.GetStats().GetTempStrengthBoost() > 0) cout << " (STR +" << enemy.GetStats().GetTempStrengthBoost() << ")";
        else if(enemy.GetStats().GetTempStrengthBoost() < 0) cout << " (STR " << enemy.GetStats().GetTempStrengthBoost() << ")";
        if(enemy.GetStats().GetTempDefenseBoost() > 0) cout << " (DEF +" << enemy.GetStats().GetTempDefenseBoost() << ")";
        else if(enemy.GetStats().GetTempDefenseBoost() < 0) cout << " (DEF " << enemy.GetStats().GetTempDefenseBoost() << ")";
        cout  << "\n\n";

        cout << "Ammo count : " << GetInventory().GetRanged().GetAmmoAmount() << "/" << GetInventory().GetRanged().GetMaxAmmo() << "\n";
        cout << "1. Shoot | Medium Damage, Piercing (breaks defense)\n2. Charge | multiplies shot damage by 3, resets after a shot/damaged\n3. Items\n4. Surrender\n\n- ";
        NumInput(opt);

        switch(opt){
            case 1:
                if(GetInventory().GetRanged().GetAmmoAmount() > 0){
                    if(GetCharge() == 0) cout << "\nYou shoot the enemy!\n";
                    else cout << "\nYou released your charge into the enemy!\n";
                    Shoot(enemy);
                    finish = true;
                }
                else cout << "\nYou ran out of ammunition/arrows!\n\n";
                break;
            case 2:
                cout << "\nYou charged your weapon!\n";
                Charge(GetCharge());
                finish = true;
                break;
            case 3:
                if(InventoryAccess(BattleState::INBATTLE)) finish = true;
                break;
            case 4:
                GetStats().GetHealth() = 0;
                finish = true;
                break;
            default:
                cout << "\nInvalid Input!\n\n";
        }
    }
}