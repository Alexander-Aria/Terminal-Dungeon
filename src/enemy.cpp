#include "enemy.hpp"
#include "player.hpp"
#include "utility.hpp"

void Enemy::Turn(Player &player){cout << GetName() << " does nothing!\n\n";}

void BatEnemy::Turn(Player &player){
    Random RNG;
    int RNGnum = RNG.Int(1,100);
    Choice choice = Choice::NOTHING;

    if(RNGnum <= slashchance) choice = Choice::SLASH;
    else if(RNGnum >= 100 - blockchance && !GetBlock()) choice = Choice::BLOCK;
    else choice = Choice::SLASH;

    switch(choice){
        case Choice::SLASH:
            cout << GetName() << " attacks!\n";
            Slash(player);
            break;
        case Choice::BLOCK:
            cout << GetName() << " is blocking!\n\n";
            GetBlock() = true;
            break;
        default:
            cout << GetName() << " does nothing!\n\n";
    }
}

void WolfEnemy::Turn(Player &player){
    Random RNG;
    int RNGnum = RNG.Int(1,100);
    Choice choice = Choice::NOTHING;

    if(RNGnum <= slashchance) choice = Choice::SLASH;
    else if(RNGnum > 100 - (blockchance + howlchance) && RNGnum <= 100 - howlchance && !GetBlock()) choice = Choice::BLOCK;
    else if(RNGnum > 100 - howlchance && player.GetStats().GetTempStrengthBoost() >= -5) choice = Choice::HOWL;
    else choice = Choice::SLASH;

    switch(choice){
        case Choice::SLASH:
            cout << GetName() << " attacks!\n";
            Slash(player);
            break;
        case Choice::BLOCK:
            cout << GetName() << " is blocking!\n\n";
            GetBlock() = true;
            break;
        case Choice::HOWL:
            cout << GetName() << " howls!\n";
            Howl(player.GetStats());
            break;
        default:
            cout << GetName() << " does nothing!\n\n";
    }
}

void BanditEnemy::Turn(Player &player){
    Random RNG;
    int RNGnum = RNG.Int(1,100);
    Choice choice = Choice::NOTHING;

    if(player.GetBlock()){
        if(bandittype == BanditType::LEADER) choice = Choice::DOUBLESHOT;
        else choice = Choice::STAB;
    }
    else if(RNGnum <= slashchance) choice = Choice::SLASH;
    else if(RNGnum >= 100 - blockchance && !GetBlock()) choice = Choice::BLOCK;
    else choice = Choice::SLASH;

    switch(choice){
        case Choice::SLASH:
            cout << GetName() << " attacks!\n";
            Slash(player);
            break;
        case Choice::STAB:
            cout << GetName() << " stabs!\n";
            Stab(player);
            break;
        case Choice::DOUBLESHOT:
            cout << GetName() << " shot you twice with a crossbow!\n";
            DoubleShot(player);
            break;
        case Choice::BLOCK:
            cout << GetName() << " is blocking!\n\n";
            GetBlock() = true;
            break;
        default:
            cout << GetName() << " does nothing!\n\n";
    }
}

void GolemEnemy::Turn(Player &player){
    Random RNG;
    int RNGnum = RNG.Int(1,100);
    Choice choice = Choice::NOTHING;

    if(RNGnum <= bashchance) choice = Choice::BASH;
    else if(RNGnum >= 100 - magicchance){
        if(golemtype == GolemType::ROCK) choice = Choice::ROCKTHROW;
        else if(golemtype == GolemType::ICE) choice = Choice::ICEBEAM;
        else if(golemtype == GolemType::FIRE) choice = Choice::FIREBLAST;
    }

    switch(choice){
        case Choice::BASH:
            cout << GetName() << " bashes!\n";
            Bash(player);
            break;
        case Choice::ROCKTHROW:
            cout << GetName() << " uses rock throw!\n";
            RockThrow(player);
            break;
        case Choice::ICEBEAM:
            cout << GetName() << " uses ice beam!\n";
            IceBeam(player);
            break;
        case Choice::FIREBLAST:
            cout << GetName() << " uses fire blast!\n";
            FireBlast(player);
            break;
        default:
            if(GetName() == "Broken Golem") cout << GetName() << " is breaking down!\n\n";
            else cout << GetName() << " does nothing!\n\n";
    }
}

void GuardEnemy::Turn(Player &player){
    Random RNG;
    int RNGnum = RNG.Int(1,100);
    Choice choice = Choice::NOTHING;

    if(RNGnum <= slashchance) choice = Choice::SLASH;
    else if(RNGnum >= 100 - shieldchance && !GetBlock()){
        if(guardtype == GuardType::PATROL) choice = Choice::BLOCK;
        else if(guardtype == GuardType::ROYALGUARD) choice = Choice::SHIELDCHARGE;
    }
    else choice = Choice::SLASH;

    switch(choice){
        case Choice::SLASH:
            cout << GetName() << " slashes!\n";
            Slash(player);
            break;
        case Choice::BLOCK:
            cout << GetName() << " is blocking!\n";
            GetBlock() = Block();
            break;
        case Choice::SHIELDCHARGE:
            cout << GetName() << " charges with their shield!\n";
            ShieldCharge(player);
            break;
        default:
            if(GetName() == "Broken Golem") cout << GetName() << " is breaking down!\n\n";
            else cout << GetName() << " does nothing!\n\n";
    }
}

void ArcherEnemy::Turn(Player &player){
    Random RNG;
    int RNGnum = RNG.Int(1,100);
    Choice choice = Choice::NOTHING;
    
    if(RNGnum <= shootchance && GetInventory().GetRanged().GetAmmoAmount() > 0) choice = Choice::SHOOT;
    else if(RNGnum >= 100 - chargechance && GetInventory().GetRanged().GetAmmoAmount() > 0) choice = Choice::CHARGE;
    else choice = Choice::CLOSECOMBAT;

    switch(choice){
        case Choice::SHOOT:
            cout << GetName() << " shoots!\n";
            Shoot(player);
            break;
        case Choice::CHARGE:
            cout << GetName() << " charges!\n";
            Charge(GetCharge());
            break;
        case Choice::CLOSECOMBAT:
            cout << GetName() << " uses close combat!\n";
            CloseCombat(player);
            break;
        default:
            if(GetName() == "Broken Golem") cout << GetName() << " is breaking down!\n\n";
            else cout << GetName() << " does nothing!\n\n";
    }
}

void KnightEnemy::Turn(Player &player){
     Random RNG;
    int RNGnum = RNG.Int(1,100);
    Choice choice = Choice::NOTHING;
    
    if(RNGnum <= heavyblowchance) choice = Choice::HEAVYBLOW;
    else if(RNGnum >= 100 - shieldchance && !GetBlock()) choice = Choice::SHIELDCHARGE;
    else choice = Choice::HEAVYBLOW;

    switch(choice){
        case Choice::HEAVYBLOW:
            cout << GetName() << " uses heavy blow!\n";
            HeavyBlow(player);
            break;
        case Choice::SHIELDCHARGE:
            cout << GetName() << " charges with their shield!\n";
            ShieldCharge(player);
            break;
        default:
            if(GetName() == "Broken Golem") cout << GetName() << " is breaking down!\n\n";
            else cout << GetName() << " does nothing!\n\n";
    }
}