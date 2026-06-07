#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class Items{
    private:
        string name = "Undefined Item";
        string description = "No Description";
    public:
        Items(){}
        Items(
            const string &n, 
            const string &d
        ) : name(n), description(d) {}

        const string &GetName() const {return name;};
        const string &GetDescription() const {return description;};
};

class Consumables : public Items{
    private:
        struct{
        int healthgain = 0;
        } effect;
    public:
        Consumables(){}
        Consumables(const string &name, const string &description, const int &health) : Items(name, description) {
            effect.healthgain = health;
        }

        const int &GetHealth(){return effect.healthgain;}
};

class Inventory{
    private:
        vector<Consumables> consumables;
    public:
        Inventory(){}

        vector<Consumables> &GetConsumables(){return consumables;}
};

inline Consumables SmallPotion() {return Consumables("Small Potion", "A small potion that heals a small amount of health.", 40);}
inline Consumables LargePotion() {return Consumables("Large Potion", "A large potion that heals a considerable amount of health.", 80);}
