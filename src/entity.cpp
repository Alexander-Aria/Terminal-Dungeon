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

void Entity::MaxHealthCheck(){
    if(stats.GetHealth() > stats.GetMaxHealth()) stats.GetHealth() = stats.GetMaxHealth();
}

void Entity::Slash(Entity &defender){
    Random RNG;
    int chance = RNG.Int(0,2);
    const double basedamage = 10.0 * (stats.GetRawStrength() + stats.GetStrengthBuff() + stats.GetTempStrengthBoost())/(defender.GetStats().GetRawDefense() + defender.GetStats().GetDefenseBuff() + defender.GetStats().GetTempDefenseBoost());
    const double blockresist = 0.5;
    const double range[2] = {0.8, 1.2};
    int damage; 
    
    if(defender.GetBlock()){
        damage = static_cast<int>(round(blockresist * RNG.Int(round(range[0] * basedamage), round(range[1] * basedamage))));
        if(chance == 0){
            cout << "The defense is broken!\n";
            defender.GetBlock() = false;
        }
        else cout << "The defenders defense held strong!\n";
    }
    else damage = static_cast<int>(RNG.Int(round(range[0] * basedamage), round(range[1] * basedamage)));

    defender.GetStats().GetHealth() -= damage;
    defender.GetCharge() = 0;
    cout << "The attacker dealt " << damage << " damage!\n\n";
}

void Entity::Stab(Entity &defender){
    Random RNG;
    const double basedamage = 7.0 * (stats.GetRawStrength() + stats.GetStrengthBuff() + stats.GetTempStrengthBoost())/(defender.GetStats().GetRawDefense() + defender.GetStats().GetDefenseBuff() + defender.GetStats().GetTempDefenseBoost());
    const double blockresist = 0.5;
    const double range[2] = {0.8, 1.2};
    int damage; 

    if(defender.GetInventory().GetMelee().GetShieldEffect() && defender.GetBlock()){
        damage = static_cast<int>(blockresist * round(RNG.Int(round(range[0] * basedamage), round(range[1] * basedamage))));
        if(RNG.Int(0, 1) == 0){
            cout << "The defense is broken!\n";
            defender.GetBlock() = false;
        }
        else{
            cout << "The defenders defense held strong thanks to the shield!\n";
        }
    }
    else{
        damage = static_cast<int>(RNG.Int(round(range[0] * basedamage), round(range[1] * basedamage)));
        if(defender.GetBlock()) {
            cout << "The defense is broken!\n";
            defender.GetBlock() = false;
        }
    }

    defender.GetStats().GetHealth() -= damage;
    defender.GetCharge() = 0;
    cout << "The attacker dealt " << damage << " damage!\n\n";
}

void Entity::Shoot(Entity &defender){
    Random RNG;
    const double basedamage = 12.0 * (stats.GetRawStrength() + stats.GetStrengthBuff() + stats.GetTempStrengthBoost())/(defender.GetStats().GetRawDefense() + defender.GetStats().GetDefenseBuff() + defender.GetStats().GetTempDefenseBoost());
    const double range[2] = {0.8, 1.2};
    const double blockresist = 0.6;
    int damage, multiplieddamage; 

    if(defender.GetInventory().GetMelee().GetShieldEffect() && defender.GetBlock()){
        damage = static_cast<int>(blockresist * round(RNG.Int(round(range[0] * basedamage), round(range[1] * basedamage))));
        if(RNG.Int(0, 2) == 0){
            cout << "The defense is broken!\n";
            defender.GetBlock() = false;
        }
        else{
            cout << "The defenders defense held strong thanks to the shield!\n";
        }
    }
    else if(defender.GetBlock()) {
        cout << "The defense is broken!\n";
        defender.GetBlock() = false;
        damage = static_cast<int>(RNG.Int(round(range[0] * basedamage), round(range[1] * basedamage)));
    }
    else damage = static_cast<int>(RNG.Int(round(range[0] * basedamage), round(range[1] * basedamage)));

    if(charge > 0) multiplieddamage = damage * 3 * charge;
    else multiplieddamage = damage;

    defender.GetStats().GetHealth() -= multiplieddamage;
    cout << "The attacker dealt " << multiplieddamage << " damage!\n\n";
    charge = 0;
    GetInventory().GetRanged().GetAmmoAmount()--;
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

void Entity::DoubleShot(Entity &defender){
    Random RNG;
    const double basedamage = 7.0 * (stats.GetRawStrength() + stats.GetStrengthBuff() + stats.GetTempStrengthBoost())/(defender.GetStats().GetRawDefense() + defender.GetStats().GetDefenseBuff() + defender.GetStats().GetTempDefenseBoost());
    const double range[2] = {0.8, 1.2};
    int damage1, damage2;

    damage1 = static_cast<int>(RNG.Int(round(range[0] * basedamage), round(range[1] * basedamage)));
    damage2 = static_cast<int>(RNG.Int(round(range[0] * basedamage), round(range[1] * basedamage)));

    if(defender.GetBlock()){
        cout << "The defense is broken!\n";
        defender.GetBlock() = false;
    }

    defender.GetStats().GetHealth() -= damage1 + damage2;
    defender.GetCharge() = 0;
    cout << "The attacker dealt " << damage1 << " damage!\n";
    cout << "The attacker dealt " << damage2 << " damage!\n\n";
}

void Entity::Bash(Entity &defender){
    Random RNG;
    int chance = RNG.Int(0,1);
    const double basedamage = 12.0 * (stats.GetRawStrength() + stats.GetStrengthBuff() + stats.GetTempStrengthBoost())/(defender.GetStats().GetRawDefense() + defender.GetStats().GetDefenseBuff() + defender.GetStats().GetTempDefenseBoost());
    const double blockresist = 0.7;
    const double range[2] = {0.8, 1.2};
    int damage; 
    
    if(defender.GetBlock()){
        damage = static_cast<int>(round(blockresist * RNG.Int(round(range[0] * basedamage), round(range[1] * basedamage))));
        if(chance == 0){
            cout << "The defense is broken!\n";
            defender.GetBlock() = false;
        }
        else cout << "The defenders defense held strong!\n";
    }
    else damage = static_cast<int>(RNG.Int(round(range[0] * basedamage), round(range[1] * basedamage)));

    defender.GetStats().GetHealth() -= damage;
    defender.GetCharge() = 0;
    cout << "The attacker dealt " << damage << " damage!\n\n";
}

void Entity::RockThrow(Entity &defender){
    Random RNG;
    const double basedamage = 8.0 * (stats.GetRawStrength() + stats.GetStrengthBuff() + stats.GetTempStrengthBoost())/(defender.GetStats().GetRawDefense() + defender.GetStats().GetDefenseBuff() + defender.GetStats().GetTempDefenseBoost());
    const double blockresist = 0.6;
    const double range[2] = {0.8, 1.2};
    int damage;
    int chance;

    for(int i = 0; i < 4; i++){
        chance = RNG.Int(0,2);

        if(chance == 0 || chance == 1){
            if(defender.GetBlock()) damage = static_cast<int>(blockresist * RNG.Int(round(range[0] * basedamage), round(range[1] * basedamage)));
            else damage = static_cast<int>(RNG.Int(round(range[0] * basedamage), round(range[1] * basedamage)));
            defender.GetStats().GetHealth() -= damage;
            defender.GetCharge() = 0;
            cout << "The attacker dealt " << damage << " damage!\n";
        }
        else cout << "The attacker missed!\n";
    }
    cout << "\n";
}

void Entity::IceBeam(Entity &defender){
    Random RNG;
    const double basedamage = 10.0 * (stats.GetRawStrength() + stats.GetStrengthBuff() + stats.GetTempStrengthBoost())/(defender.GetStats().GetRawDefense() + defender.GetStats().GetDefenseBuff() + defender.GetStats().GetTempDefenseBoost());
    const double blockresist = 0.2;
    const double range[2] = {0.9, 1.1};
    int damage;
    int chance;

    if(defender.GetBlock()) damage = static_cast<int>(blockresist * RNG.Int(round(range[0] * basedamage), round(range[1] * basedamage)));
    else damage = static_cast<int>(RNG.Int(round(range[0] * basedamage), round(range[1] * basedamage)));
    defender.GetStats().GetHealth() -= damage;
    defender.GetCharge() = 0;
    cout << "The attacker dealt " << damage << " damage!\n";
}

void Entity::ShieldCharge(Entity &defender){
    Random RNG;
    const double basedamage = 7.0 * (stats.GetRawStrength() + stats.GetStrengthBuff() + stats.GetTempStrengthBoost())/(defender.GetStats().GetRawDefense() + defender.GetStats().GetDefenseBuff() + defender.GetStats().GetTempDefenseBoost());
    const double blockresist = 0.8;
    const double range[2] = {0.8, 1.2};
    int damage;

    if(defender.GetBlock()) damage = static_cast<int>(blockresist * RNG.Int(round(range[0] * basedamage), round(range[1] * basedamage)));
    else damage = static_cast<int>(RNG.Int(round(range[0] * basedamage), round(range[1] * basedamage)));
    defender.GetStats().GetHealth() -= damage;
    defender.GetCharge() = 0;
    cout << "The attacker dealt " << damage << " damage!\n";

    block = Block();
    cout << "The attacker is blocking!\n\n";
}

void Entity::CloseCombat(Entity &defender){
    Random RNG;
    int chance = RNG.Int(0,3);
    const double basedamage = 5.0 * (stats.GetRawStrength() + stats.GetStrengthBuff() + stats.GetTempStrengthBoost())/(defender.GetStats().GetRawDefense() + defender.GetStats().GetDefenseBuff() + defender.GetStats().GetTempDefenseBoost());
    const double blockresist = 0.8;
    const double range[2] = {0.6, 1.4};
    int damage; 
    
    if(defender.GetBlock()){
        damage = static_cast<int>(round(blockresist * RNG.Int(round(range[0] * basedamage), round(range[1] * basedamage))));
        if(chance == 0){
            cout << "The defense is broken!\n";
            defender.GetBlock() = false;
        }
        else cout << "The defenders defense held strong!\n";
    }
    else damage = static_cast<int>(RNG.Int(round(range[0] * basedamage), round(range[1] * basedamage)));

    defender.GetStats().GetHealth() -= damage;
    defender.GetCharge() = 0;
    cout << "The attacker dealt " << damage << " damage!\n\n";
}

void Entity::HeavyBlow(Entity &defender){
    Random RNG;
    int chance = RNG.Int(0,2);
    const double basedamage = 15.0 * (stats.GetRawStrength() + stats.GetStrengthBuff() + stats.GetTempStrengthBoost())/(defender.GetStats().GetRawDefense() + defender.GetStats().GetDefenseBuff() + defender.GetStats().GetTempDefenseBoost());
    const double blockresist = 0.4;
    const double range[2] = {0.7, 1.3};
    int damage; 
    
    if(defender.GetBlock()){
        damage = static_cast<int>(round(blockresist * RNG.Int(round(range[0] * basedamage), round(range[1] * basedamage))));
        if(chance == 0){
            cout << "The defense is broken!\n";
            defender.GetBlock() = false;
        }
        else cout << "The defenders defense held strong!\n";
    }
    else damage = static_cast<int>(RNG.Int(round(range[0] * basedamage), round(range[1] * basedamage)));

    defender.GetStats().GetHealth() -= damage;
    defender.GetCharge() = 0;
    cout << "The attacker dealt " << damage << " damage!\n\n";
}