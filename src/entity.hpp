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

        void ChangeEquipment(const Armor &armor){
            inventory.GetArmor() = armor;
            stats.GetDefenseBuff() = inventory.GetArmor().GetDefenseBuff();
        }

        void ChangeEquipment(const Weapon &weapon){
            inventory.GetWeapon() = weapon;
            stats.GetStrengthBuff() = inventory.GetWeapon().GetStrengthBuff();
        }

        bool IsDead() {return stats.GetHealth() <= 0;}
};