#pragma once

#include "stats.hpp"
#include "inventory.hpp"

class Entity{
    private:
        Stats stats;
        Inventory inventory;
    public:
        Entity() {}
        Entity(const Stats &s) : stats(s) {}
        Entity(const Stats &s, const Inventory &i) : stats(s), inventory(i) {}

        Stats &GetStats() {return stats;}
        Inventory &GetInventory() {return inventory;}

        void ChangeEquipment(const Armor &armor);
        void ChangeEquipment(const Weapon &weapon);
        int Slash(Stats &attackerstats, Stats &defenderstats, bool &defend);
        int Stab(Stats &attackerstats, Stats &defenderstats, bool &defend);
        bool Defend() {return true;}

        bool IsDead() {return stats.GetHealth() <= 0;}
};