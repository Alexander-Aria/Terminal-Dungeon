#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class Items{
    private:
        string name = "Undefined Item";
        string description = "No Description";
        int value = 0;
    public:
        Items(){}
        Items(
            const string &n, 
            const string &d,
            const int &v
        ) : name(n), description(d), value(v) {}

        const string &GetName() const {return name;};
        const string &GetDescription() const {return description;};
};

class Consumables : public Items{
    private:
        struct{
        int healthgain = 0;
        int strboost = 0;
        int defboost = 0;
        } effect;
    public:
        Consumables(){}
        Consumables(
            const string &name, 
            const string &description, 
            const int &value, 
            const int &health, 
            const int &str, 
            const int &def
        ) : Items(name, description, value) {
            effect.healthgain = health;
            effect.strboost = str;
            effect.defboost = def;
        }

        const int &GetHealthGain(){return effect.healthgain;}
        const int &GetStrengthBoost(){return effect.strboost;}
        const int &GetDefenseBoost(){return effect.defboost;}
};

class Inventory{
    private:
        vector<Consumables> consumables;
    public:
        Inventory(){}
        Inventory(vector<Consumables> cons) : consumables(cons) {}

        vector<Consumables> &GetConsumables(){return consumables;}
};

inline Consumables SmallPotion() {return Consumables(
    "Small Potion", 
    "A small potion that heals a small amount of health.", 
    100, 
    40, 
    0, 
    0
);}

inline Consumables LargePotion() {return Consumables(
    "Large Potion", 
    "A large potion that heals a considerable amount of health.", 
    300, 
    80, 
    0, 
    0
);}

inline Consumables PowerStone() {return Consumables(
    "Power Stone",
    "A magical stone that increases your strength by 3 in a single fight.", 
    200, 
    0, 
    3, 
    0
);}

inline Consumables ArmorStone() {return Consumables(
    "Armor Stone", 
    "A magical stone that increases your defense by 3 in a single fight.", 
    200, 
    0, 
    0, 
    3
);}