#pragma once

#include "entity.hpp"

#include <iostream>

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

        void LevelUp();
};

bool InventoryAccess(Player &player, const BattleState &state);
void StatsCheck(Stats &playerstats);
