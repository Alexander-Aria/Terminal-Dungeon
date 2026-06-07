#pragma once

#include <iostream>

#include "stats.hpp"
#include "inventory.hpp"

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
            while(exp >= 300){
                level++;
                stats.GetMaxHealth() += 20;
                stats.GetHealth() = stats.GetMaxHealth();
                stats.GetDefense() += 2;
                stats.GetStrength() += 2;
                exp -= 300;
                std::cout << "you leveled up to level " << level << "!\n";
            }
        }
};

void InventoryAccess(Player &player);
void StatsCheck(Stats &playerstats);