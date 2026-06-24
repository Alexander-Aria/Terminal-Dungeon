#pragma once

#include "stats.hpp"
#include "inventory.hpp"

enum class Choice{
    NOTHING,
    SLASH,
    STAB,
    HOWL,
    DOUBLESHOT,
    BASH,
    ROCKTHROW,
    SHIELDCHARGE,
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

        void Slash(Entity &defender);
        void Stab(Entity &defender);
        void Shoot(Entity &defender);
        void Charge(int &charge);
        void Howl(Stats &defenderstats);
        void DoubleShot(Entity &defender);
        void Bash(Entity &defender);
        void RockThrow(Entity &defender);
        void ShieldCharge(Entity &defender);
        bool Block() {return true;}

        bool IsDead() {return stats.GetHealth() <= 0;}
};