#include "entity.hpp"
#include "utility.hpp"

#include <iostream>
#include <memory>
#include <cmath>

void Entity::UpdateBuff(){
    stats.GetDefenseBuff() = inventory.GetArmor().GetDefenseBuff();
    if(usingweapon == WeaponType::MELEE) stats.GetStrengthBuff() = inventory.GetMelee().GetStrengthBuff();
    else if(usingweapon == WeaponType::RANGED) stats.GetStrengthBuff() = inventory.GetRanged().GetStrengthBuff();
}

bool Entity::SwitchWeapon(){
    if(usingweapon == WeaponType::MELEE && inventory.GetRanged() != "SOLD OUT"){
        usingweapon = WeaponType::RANGED;
        cout << "Switched to ranged!\n\n";
    }
    else if(usingweapon == WeaponType::RANGED && inventory.GetMelee() != "SOLD OUT"){
        usingweapon = WeaponType::MELEE;
        cout << "Switched to melee!\n\n";
    }
    else{
        std::cout << "Unable to switch weapons!\n\n";
        return false;
    }
    UpdateBuff();
    return true;
}

void Entity::ChangeEquipment(const Armor &armor){
    inventory.GetArmor() = armor;
    UpdateBuff();
}

void Entity::ChangeEquipment(const Melee &melee){
    inventory.GetMelee() = melee;
    UpdateBuff();
}

void Entity::ChangeEquipment(const Ranged &ranged){
    inventory.GetRanged() = ranged;
    UpdateBuff();
}

void Entity::Slash(Stats &attackerstats, Stats &defenderstats, bool &defend){
    Random RNG;
    int chance = RNG.Int(0,2);
    double basedamage = 10.0 * (attackerstats.GetRawStrength() + attackerstats.GetStrengthBuff() + attackerstats.GetTempStrengthBoost())/(defenderstats.GetRawDefense() + defenderstats.GetDefenseBuff() + defenderstats.GetTempDefenseBoost());
    int damage; 
    
    if(defend){
        damage = static_cast<int>(round(0.5 * RNG.Int(round(0.8 * basedamage), round(1.2 * basedamage))));
        if(chance == 0){
            cout << "The defense is broken!\n";
            defend = false;
        }
        else cout << "The defenders defense held strong!\n";
    }
    else damage = static_cast<int>(RNG.Int(round(0.8 * basedamage), round(1.2 * basedamage)));

    defenderstats.GetHealth() -= damage;
    cout << "The attacker dealt " << damage << " damage!\n\n";
}

void Entity::Stab(Stats &attackerstats, Stats &defenderstats, bool &defend){
    Random RNG;
    double basedamage = 7.0 * (attackerstats.GetRawStrength() + attackerstats.GetStrengthBuff() + attackerstats.GetTempStrengthBoost())/(defenderstats.GetRawDefense() + defenderstats.GetDefenseBuff() + defenderstats.GetTempDefenseBoost());
    int damage; 
    
    damage = static_cast<int>(RNG.Int(round(0.8 * basedamage), round(1.2 * basedamage)));
    if(defend) {
        cout << "The defense is broken!\n";
        defend = false;
    }

    defenderstats.GetHealth() -= damage;
    cout << "The attacker dealt " << damage << " damage!\n\n";
}

void Entity::Shoot(Entity &attacker, Stats &defenderstats, bool &defend, int &charge){
    Random RNG;
    double basedamage = 8.0 * (attacker.GetStats().GetRawStrength() + attacker.GetStats().GetStrengthBuff() + attacker.GetStats().GetTempStrengthBoost())/(defenderstats.GetRawDefense() + defenderstats.GetDefenseBuff() + defenderstats.GetTempDefenseBoost());
    int damage, multiplieddamage; 
    
    damage = static_cast<int>(RNG.Int(round(0.8 * basedamage), round(1.2 * basedamage)));
    multiplieddamage = damage * pow(3, charge);
    if(defend) {
        cout << "The defense is broken!\n";
        defend = false;
    }

    defenderstats.GetHealth() -= multiplieddamage;
    cout << "The attacker dealt " << multiplieddamage << " damage!\n\n";
    charge = 0;
}

void Entity::Charge(int &charge){
    charge++;
    cout << "Weapon Charge : " << charge << "(" << charge*3 << "x damage)\n\n";
}

void Entity::Howl(Stats &defenderstats){
    if(defenderstats.GetTempStrengthBoost() >= -5) {
        defenderstats.GetTempStrengthBoost() -= 1;
        cout << "Your attack went down by 1!\n";
    }
    else cout << "You are unaffected!\n";
}

void Entity::DoubleShot(Stats &attackerstats, Stats &defenderstats, bool &defend){
    Random RNG;
    double basedamage = 5.0 * (attackerstats.GetRawStrength() + attackerstats.GetStrengthBuff() + attackerstats.GetTempStrengthBoost())/(defenderstats.GetRawDefense() + defenderstats.GetDefenseBuff() + defenderstats.GetTempDefenseBoost());
    int damage1, damage2;

    damage1 = static_cast<int>(RNG.Int(round(0.8 * basedamage), round(1.2 * basedamage)));
    damage2 = static_cast<int>(RNG.Int(round(0.8 * basedamage), round(1.2 * basedamage)));

    if(defend){
        cout << "The defense is broken!\n";
        defend = false;
    }

    defenderstats.GetHealth() -= damage1 + damage2;
    cout << "The attacker dealt " << damage1 << " damage!\n\n";
    cout << "The attacker dealt " << damage2 << " damage!\n\n";
}