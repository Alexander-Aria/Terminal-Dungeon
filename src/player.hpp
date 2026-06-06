#pragma once

#include "stats.hpp"
#include "inventory.hpp"

class Player{
    private:
        Stats stats;
        Inventory inventory;
    public:
        Player(){}

        Stats &GetStats(){return stats;}
        Inventory &GetInventory(){return inventory;}
};

void InventoryAccess(Player &player);
void StatsCheck(Stats &playerstats);