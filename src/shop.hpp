#pragma once

#include "inventory.hpp"
#include "player.hpp"

class Shop{
    private:
        Inventory shopitems;
    public:
        Shop() {}
        Shop(const Inventory &s) : shopitems(s) {}

        Inventory &GetInventory() {return shopitems;}
};

void ShopFunction(Player &player, const Shop &cponfig);

inline const vector<Consumables> ShopConsumablesOne(){return {
    SmallPotion(), 
    SmallPotion(),
    SmallPotion(),
    LargePotion(),
    PowerStone(),
    ArmorStone()
};}
inline Shop ShopConfigOne() {return Shop(Inventory(ShopConsumablesOne()));}