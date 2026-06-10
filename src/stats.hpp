#pragma once

class Stats{
    private:
        int health = 100;
        int maxhealth = 100;
        int strength = 10;
        int defense = 10;
        int strboost = 0;
        int defboost = 0;
    public:
        Stats(){}
        Stats(
            const int &h, 
            const int &mh, 
            const int &str, 
            const int &def
        ) : health(h), maxhealth(mh), strength(str), defense(def) {}

        int &GetHealth(){return health;}
        int &GetMaxHealth(){return maxhealth;}
        int &GetStrength(){return strength;}
        int &GetDefense(){return defense;}
        int &GetStrengthBoost(){return strboost;}
        int &GetDefenseBoost(){return defboost;}
};