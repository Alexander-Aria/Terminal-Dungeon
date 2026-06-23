#pragma once

#include "entity.hpp"

#include <iostream>

class Enemy;

enum class BattleState {
    OUTBATTLE,
    INBATTLE
};

class Player : public Entity{
    private:
        int level = 1;
        int exp = 0;
        int gold = 0;
    public:
        Player() {}

        int &GetLevel(){return level;}
        int &GetExp(){return exp;}
        int &GetGold(){return gold;}

        bool SwitchWeapon();
        void ChangeEquipment(const Armor &armor);
        void ChangeEquipment(const Melee &melee);
        void ChangeEquipment(const Ranged &ranged);
        void LevelUp();
        void StatsCheck();
        bool InventoryAccess(const BattleState &state);

        void MeleeOption(Enemy &enemy);
        void RangedOption(Enemy &enemy);
};
