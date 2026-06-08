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

inline Enemy Dummy() {return Enemy(
    Stats(200, 200, 0, 5),
    "Dummy",
    "A practice dummy.",
    0,
    0,
    0,
    0
);}

inline Enemy WolfCub() {return Enemy(
    Stats(60, 60, 10, 6), 
    "Wolf Cub", 
    "A young wolf cub.", 
    20, 
    30,
    50,
    50
);}

inline Enemy FemaleWolf() {return Enemy(
    Stats(150, 150, 15, 8),
    "Female Wolf",
    "A female wolf and a grieving mother of a wolf cub.",
    50,
    150,
    40,
    60
);}

inline Enemy MaleWolf() {return Enemy(
    Stats(200, 200, 18, 10),
    "Male Wolf",
    "A male wolf and a furious father of a wolf cub.",
    80,
    200,
    40,
    60
);}

inline Enemy Bat() {return Enemy(
    Stats(50, 50, 8, 5), 
    "Bat", 
    "An agressive and territorial bat.", 
    30, 
    50,
    20,
    80
);}

