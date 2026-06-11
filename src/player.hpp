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
        Player(bool dev){
            if(dev){
                gold = 10000;
                inventory = Inventory(AllItems());
                stats = {10000, 10000, 10000, 10000};
            }
        }

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
                stats.GetDefense() += 2;
                stats.GetStrength() += 2;
                exp -= 300;
                std::cout << "you leveled up to level " << level << "!\n\n";
            }
        }
};

bool InventoryAccess(Player &player, const BattleState &state);
void StatsCheck(Stats &playerstats);
