#pragma once

#include "stats.hpp"

class Enemy{
    private:
        Stats stats;
        string name = "Undefined Enemy";
        string description = "No Description";
    public:
        Enemy(){}
        Enemy(const Stats &s, const string &n, const string &d){
            stats = s;
            name = n;
            description = d;
        }

        Stats &GetStats(){return stats;}
        string &GetName(){return name;}
        string &GetDescription(){return description;}
};

void EnemyTurn(Player &player, Enemy &enemy, bool &playerdefend, bool &enemydefend);