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
        void Buy(Player &player);
        void Sell(Player &player);
};

void ShopFunction(Player &player, const Shop &config);

inline const vector<Consumables> ShopConsumablesOne(){return {
    SmallPotion(), 
    SmallPotion(),
    SmallPotion(),
    LargePotion(),
    PowerStone(),
    ArmorStone()
};}
inline Shop ShopConfigOne() {return Shop(Inventory(ShopConsumablesOne(), LongSword(), NoRanged(), LightChainmailArmor()));}

inline const vector<Consumables> ShopConsumablesTwo(){return {
    SmallPotion(), 
    SmallPotion(),
    LargePotion(),
    LargePotion(),
    LifeStone(),
    PowerStone(),
    ArmorStone()
};}
inline Shop ShopConfigTwo() {return Shop(Inventory(ShopConsumablesTwo(), DragonSlayer(), NoRanged(), DragonScaleArmor()));}