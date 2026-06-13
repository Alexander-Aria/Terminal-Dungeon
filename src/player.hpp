#pragma once

#include <iostream>

#include "stats.hpp"
#include "inventory.hpp"

enum class BattleState {
    OUTBATTLE,
    INBATTLE
};

class Player{
    private:
        Stats stats;
        Inventory inventory;
        int level = 1;
        int exp = 0;
        int gold = 0;
    public:
        Player(){}

        Stats &GetStats(){return stats;}
        Inventory &GetInventory(){return inventory;}
        int &GetLevel(){return level;}
        int &GetExp(){return exp;}
        int &GetGold(){return gold;}

        void LevelUp(){
            while(exp >= 250){
                level++;
                stats.GetMaxHealth() += 20;
                stats.GetHealth() = stats.GetMaxHealth();
                stats.GetRawDefense() += 2;
                stats.GetRawStrength() += 2;
                exp -= 250;
                std::cout << "you leveled up to level " << level << "!\n\n";
            }
        }

        void BuffUpdate(){
            stats.GetDefenseBuff() = inventory.GetArmor().GetDefenseBuff();
            stats.GetStrengthBuff() = inventory.GetWeapon().GetStrengthBuff();
        }
};

bool InventoryAccess(Player &player, const BattleState &state);
void StatsCheck(Stats &playerstats);
