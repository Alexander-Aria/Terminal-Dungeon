#pragma once

#include "inventory.hpp"

class Shop{
    private:
        Inventory shopitems;
    public:
        Shop() {}
        Shop(const Inventory &s) : shopitems(s) {}

        Inventory &GetInventory() {return shopitems;}
};

void ShopOne();

inline Shop ShopConfigOne() {return Shop(Inventory(ShopConsumablesOne()));}

inline vector<Consumables> ShopConsumablesOne() {return {
    SmallPotion(), 
    SmallPotion(),
    SmallPotion(),
    LargePotion(),
    PowerStone(),
    ArmorStone()
};}