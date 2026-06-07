#pragma once

#include "stats.hpp"
#include <string>

using std::string;

class Enemy{
    private:
        Stats stats;
        string name = "Undefined Enemy";
        string description = "No Description";
        int goldreward = 0;
        int expreward = 0;
        int attchance = 50;
        int defchance = 50;
    public:
        Enemy(){}
        Enemy(
            const Stats &s, 
            const string &n, 
            const string &d,
            const int &greward,
            const int &ereward,
            const int &dc,
            const int &ac
        ) : stats(s), name(n), description(d), goldreward(greward), expreward(ereward), defchance(dc), attchance(ac) {}

        Stats &GetStats(){return stats;}
        string &GetName(){return name;}
        string &GetDescription(){return description;}
        int &GetGoldReward(){return goldreward;}
        int &GetExpReward(){return expreward;}
        int &GetAttChance(){return attchance;}
        int &GetDefChance(){return defchance;}
};

inline Enemy WolfCub() {return Enemy(
    Stats(50, 50, 3, 5), 
    "Wolf Cub", 
    "A young wolf cub.", 
    0, 
    0,
    50,
    50
);}

inline Enemy Bat() {return Enemy(
    Stats(75, 75, 15, 5), 
    "Bat", 
    "An agressive bat.", 
    30, 
    50,
    80,
    20
);}