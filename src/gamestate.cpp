#include "gamestate.hpp"
#include "utility.hpp"

#include <iostream>

using std::cout;

void GameState::BattleStateReset(){
    player.GetStats().GetTempStrengthBoost() = 0;
    player.GetStats().GetTempDefenseBoost() = 0;
    player.GetBlock() = false;
    player.GetInventory().GetRanged().GetAmmoAmount() = player.GetInventory().GetRanged().GetMaxAmmo();
}

void GameState::DeveloperMode(){
    Melee melee;
    Ranged ranged;
    Armor armor;
    int opt = 0;

    cout << "Set Gold : ";
    NumInput(player.GetGold());
    cout << "Set Melee : \n";
    cout << "1. Iron Sword\n2. Long Sword\n3. Dragon Slayer\n4. Shield\n\n- ";
    NumInput(opt);

    switch(opt){
        case 1:
            melee = IronSword();
            break;
        case 2:
            melee = LongSword();
            break;
        case 3:
            melee = DragonSlayer();
            break;
        case 4:
            melee = Shield();
            break;
        default:
            melee = NoMelee();
    }

    cout << "Set Ranged : \n";
    cout << "1. Crossbow\n2. Short Bow\n\n- ";
    NumInput(opt);

    switch(opt){
        case 1:
            ranged = Crossbow();
            break;
        case 2:
            ranged = ShortBow();
            break;
        default:
            ranged = NoRanged();
    }

    cout << "Set Armor : \n";
    cout << "1. Leather Armor\n2. Light Chainmail Armor\n3. Dragon Scale Armor\n\n- ";
    NumInput(opt);

    switch(opt){
        case 1:
            armor = LeatherArmor();
            break;
        case 2:
            armor = LightChainmailArmor();
            break;
        case 3:
            armor = DragonScaleArmor();
            break;
        default:
            armor = NoArmor();
    }

    player.GetInventory() = Inventory(AllItems(), melee, ranged, armor);
    player.UpdateBuff();

    cout << "Set Health/Max Health : ";
    NumInput(player.GetStats().GetMaxHealth());
    player.GetStats().GetHealth() = player.GetStats().GetMaxHealth();

    cout << "Set Strength : ";
    NumInput(player.GetStats().GetRawStrength());

    cout << "Set Defense : ";
    NumInput(player.GetStats().GetRawDefense());
}