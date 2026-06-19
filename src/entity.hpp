#pragma once

#include "stats.hpp"
#include "inventory.hpp"

enum class Choice{
    NOTHING,
    SLASH,
    STAB,
    HOWL,
    DOUBLESHOT,
    BLOCK
};

enum class WeaponType{
    MELEE,
    RANGED
};

class Entity{
    private:
        WeaponType usingweapon = WeaponType::MELEE;
        Stats stats;
        Inventory inventory;
        bool block = false;
        int charge = 0;
    public:
        Entity() {}
        Entity(const Stats &s) : stats(s) {}
        Entity(const Stats &s, const Inventory &i) : stats(s), inventory(i) {
            UpdateBuff();
        }

        WeaponType &GetUsingWeapon() {return usingweapon;}
        Stats &GetStats() {return stats;}
        Inventory &GetInventory() {return inventory;}
        bool &GetBlock() {return block;}
        int &GetCharge() {return charge;}

        void UpdateBuff();
        bool SwitchWeapon();
        void ChangeEquipment(const Armor &armor);
        void ChangeEquipment(const Melee &melee);
        void ChangeEquipment(const Ranged &ranged);

        void Slash(Entity &defender);
        void Stab(Entity &defender);
        void Shoot(Entity &defender);
        void Charge(int &charge);
        void Howl(Stats &defenderstats);
        void DoubleShot(Entity &defender);
        bool Block() {return true;}

        bool IsDead() {return stats.GetHealth() <= 0;}
};