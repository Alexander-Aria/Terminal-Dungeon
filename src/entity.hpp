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
    public:
        Entity() {}
        Entity(const Stats &s) : stats(s) {}
        Entity(const Stats &s, const Inventory &i) : stats(s), inventory(i) {
            UpdateBuff();
        }

        WeaponType &GetUsingWeapon() {return usingweapon;}
        Stats &GetStats() {return stats;}
        Inventory &GetInventory() {return inventory;}

        void UpdateBuff();
        void SwitchWeapon();
        void ChangeEquipment(const Armor &armor);
        void ChangeEquipment(const Melee &melee);
        void ChangeEquipment(const Ranged &ranged);

        void Slash(Stats &attackerstats, Stats &defenderstats, bool &defend);
        void Stab(Stats &attackerstats, Stats &defenderstats, bool &defend);
        void Howl(Stats &defenderstats);
        void DoubleShot(Stats &attackerstats, Stats &defenderstats, bool &defend);
        bool Block() {return true;}

        bool IsDead() {return stats.GetHealth() <= 0;}
};