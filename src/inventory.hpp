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

        const string &GetName() const {return name;}
        const string &GetDescription() const {return description;}
        const int &GetValue() const {return value;}
};

class Consumables : public Items{
    private:
        struct{
        int healthgain = 0;
        int tempstrboost = 0;
        int tempdefboost = 0;
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
            effect.tempstrboost = str;
            effect.tempdefboost = def;
        }

        const int &GetHealthGain() const {return effect.healthgain;}
        const int &GetTempStrengthBoost() const {return effect.tempstrboost;}
        const int &GetTempDefenseBoost() const {return effect.tempdefboost;}
};

class Weapon : public Items{
    private:
        int attackbuff = 0;
    public:
        Weapon(
            const string &name, 
            const string &description, 
            const int &value, 
            const int &attbuff
        ) : Items(name, description, value), attackbuff(attbuff) {}

        const int &GetStrengthBuff() const {return attackbuff;}
};

class Armor : public Items{
    private:
        int defensebuff = 0;
    public:
        Armor(
            const string &name, 
            const string &description, 
            const int &value, 
            const int &defbuff
        ) : Items(name, description, value), defensebuff(defbuff) {}

        const int &GetDefenseBuff() const {return defensebuff;}
};

inline Weapon NoWeapon() {return Weapon(
    "SOLD OUT",
    "This weapon is sold out.",
    0,
    0
);}

inline Weapon IronSword() {return Weapon(
    "Iron Sword",
    "A simple but reliable sword (+0 Strength).",
    0,
    0
);}

inline Weapon LongSword() {return Weapon(
    "Long Sword",
    "A heavy and hard hitting long sword (+3 Strength).",
    400,
    3
);}

inline Armor NoArmor() {return Armor(
    "SOLD OUT",
    "This Armor is sold out.",
    0,
    0
);}

inline Armor LeatherArmor() {return Armor(
    "Leather Armor",
    "A regular adventurer's armor (+0 Defense).",
    0,
    0
);}

inline Armor LightChainmailArmor() {return Armor(
    "Light Chainmail Armor",
    "A military grade light chainmail armor (+3 Defense).",
    400,
    3
);}

inline Consumables SmallPotion() {return Consumables(
    "Small Potion", 
    "A small potion that heals a small amount of health (40 HP).", 
    100, 
    40, 
    0, 
    0
);}

inline Consumables LargePotion() {return Consumables(
    "Large Potion", 
    "A large potion that heals a considerable amount of health (100 HP).", 
    250, 
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

inline vector<Consumables> AllItems() {return {
    SmallPotion(),
    SmallPotion(),
    SmallPotion(),
    LargePotion(),
    LargePotion(),
    LargePotion(),
    PowerStone(),
    PowerStone(),
    PowerStone(),
    ArmorStone(),
    ArmorStone(),
    ArmorStone()
};}

class Inventory{
    private:
        vector<Consumables> consumables;
        Weapon weapon = NoWeapon();
        Armor armor = NoArmor();
    public:
        Inventory() {}
        Inventory(const vector<Consumables> &cons, const Weapon &w, const Armor &a) : consumables(cons), weapon(w), armor(a) {}

        vector<Consumables> &GetConsumables() {return consumables;}
        Weapon &GetWeapon() {return weapon;}
        Armor &GetArmor() {return armor;}
};

void ShowConsumables(Inventory &inventory, bool shop);
void ShowEquipment(Inventory &inventory, bool showvalue);