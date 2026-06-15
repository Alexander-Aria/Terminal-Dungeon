#include "entity.hpp"
#include "utility.hpp"

#include <iostream>

void Entity::ChangeEquipment(const Armor &armor){
    inventory.GetArmor() = armor;
    stats.GetDefenseBuff() = inventory.GetArmor().GetDefenseBuff();
}

void Entity::ChangeEquipment(const Weapon &weapon){
    inventory.GetWeapon() = weapon;
    stats.GetStrengthBuff() = inventory.GetWeapon().GetStrengthBuff();
}

int Entity::Slash(Stats &attackerstats, Stats &defenderstats, bool &defend){
    Random RNG;
    int chance = RNG.Int(0,2);
    double basedamage = 10.0 * (attackerstats.GetRawStrength() + attackerstats.GetStrengthBuff() + attackerstats.GetTempStrengthBoost())/(defenderstats.GetRawDefense() + defenderstats.GetDefenseBuff() + defenderstats.GetTempDefenseBoost());
    int damage; 
    
    if(defend){
        damage = static_cast<int>(round(0.5 * RNG.Int(round(0.8 * basedamage), round(1.2 * basedamage))));
        if(chance == 0 || chance == 1){
            cout << "The defense is broken!\n";
            defend = false;
        }
        else cout << "The defenders defense held strong!\n";
    }
    else damage = static_cast<int>(RNG.Int(round(0.8 * basedamage), round(1.2 * basedamage)));

    cout << "The attacker dealt " << damage << " damage!\n\n";
    return damage;
}

int Entity::Stab(Stats &attackerstats, Stats &defenderstats, bool &defend){
    Random RNG;
    double basedamage = 7.0 * (attackerstats.GetRawStrength() + attackerstats.GetStrengthBuff() + attackerstats.GetTempStrengthBoost())/(defenderstats.GetRawDefense() + defenderstats.GetDefenseBuff() + defenderstats.GetTempDefenseBoost());
    int damage; 
    
    damage = static_cast<int>(RNG.Int(round(0.8 * basedamage), round(1.2 * basedamage)));
    if(defend) {
        cout << "The defense is broken!\n";
        defend = false;
    }

    cout << "The attacker dealt " << damage << " damage!\n\n";
    return damage;
}