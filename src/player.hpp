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

        void MeleeOption(Player &player, Enemy &enemy, bool &playerblock, bool &enemyblock);
        void RangedOption(Player &player, Enemy &enemy, bool &playerblock, bool &enemyblock, int &charge);

        void LevelUp();
        void StatsCheck();
        bool InventoryAccess(const BattleState &state);
};
