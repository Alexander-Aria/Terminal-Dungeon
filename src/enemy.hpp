#pragma once

#include "stats.hpp"
#include <string>

using std::string;

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

inline Enemy WolfCub() {return Enemy(Stats(50, 50, 3, 5), "Wolf Cub", "A young wolf cub.");}
inline Enemy Bat() {return Enemy(Stats(75, 75, 12, 5), "Bat", "An agressive bat.");}