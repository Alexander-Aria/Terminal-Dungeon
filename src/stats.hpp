#pragma once

class Stats{
    private:
        int health = 100;
        int maxhealth = 100;

        int rawstrength = 10;
        int strbuff = 0;
        int tempstrboost = 0;

        int rawdefense = 10;
        int defbuff = 0;
        int tempdefboost = 0;
    public:
        Stats(){}
        Stats(
            const int &h, 
            const int &mh, 
            const int &str, 
            const int &def
        ) : health(h), maxhealth(mh), rawstrength(str), rawdefense(def) {}

        int &GetHealth(){return health;}
        int &GetMaxHealth(){return maxhealth;}

        int &GetRawStrength(){return rawstrength;}
        int &GetStrengthBuff(){return strbuff;}
        int &GetTempStrengthBoost(){return tempstrboost;}

        int &GetRawDefense(){return rawdefense;}
        int &GetDefenseBuff(){return defbuff;}
        int &GetTempDefenseBoost(){return tempdefboost;}
};