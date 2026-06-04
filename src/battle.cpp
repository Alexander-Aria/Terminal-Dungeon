#include "battle.hpp"
#include "stages.hpp"
#include "utility.hpp"
#include "inventory.hpp"

#include <iostream>

using std::cout;

int Battle(int &stage, GameState &game, Enemy &enemy){
    Random RNG;
    int status = 0;
    bool playerdefend = false, enemydefend = false;


    cout << enemy.GetName() << " appeared!\n";
    cout << "Description : " << enemy.GetDescription() << "\n";
    while(status == 0){
        cout << "__________________________\n";
        cout << "Player Health : " << game.GetPlayer().GetStats().GetHealth() << "\n";
        cout << enemy.GetName() << " Health : " << enemy.GetStats().GetHealth() << "\n\n";

        PlayerTurn(game.GetPlayer(), enemy, playerdefend, enemydefend);
        status = StatusCheck(game.GetPlayer().GetStats(), enemy.GetStats());
        if(status != 0) break;

        EnemyTurn(game.GetPlayer(), enemy, playerdefend, enemydefend);
        status = StatusCheck(game.GetPlayer().GetStats(), enemy.GetStats());
        if(status != 0) break;
    }
    if(status == -1) cout << "You lose!\n";
    else if(status == 1) cout << "You won!\n";
    game.HealthReset();
    return status;
}

int StatusCheck(Stats &playerstats, Stats &enemystats){
    if(playerstats.GetHealth() <= 0) return -1;
    else if(enemystats.GetHealth() <= 0) return 1;
    else return 0;
}

void PlayerTurn(Player &player, Enemy &enemy, bool &playerdefend, bool &enemydefend){
    int opt = 0;
    bool finish = false;

    while(!finish){
        cout << "1. Attack\n2. Defend\n3. Items\n4. Surrender\n\n- ";
        NumInput(opt);
        switch(opt){
            case 1:
                enemy.GetStats().GetHealth() -= Attack(player.GetStats(), enemy.GetStats(), enemydefend);
                finish = true;
                break;
            case 2:
                playerdefend = true;
                finish = true;
                break;
            case 3:
                InventoryAccess(player);
                break;
            case 4:
                player.GetStats().GetHealth() = 0;
                finish = true;
                break;
        }
    }
}

void EnemyTurn(Player &player, Enemy &enemy, bool &playerdefend, bool &enemydefend){
    Random RNG;
    int range[2] = {0, 2};

    // 0 = Nothing, 1 = Attack, 2 = Defend
    switch(RNG.Int(range[0], range[1])){
        case 0:
            cout << enemy.GetName() << " does nothing!\n";
            break;
        case 1:
            cout << enemy.GetName() << " attacks!\n";
            player.GetStats().GetHealth() -= Attack(enemy.GetStats(), player.GetStats(), playerdefend);
            break;
        case 2:
            enemydefend = true;
            cout << enemy.GetName() << " is defending!\n";
            break;
    }
}

int Attack(Stats &attackerstats, Stats &defenderstats, bool &defend){
    Random RNG;
    double basedamage = 10 * attackerstats.GetStrength()/defenderstats.GetDefense();
    int damage; 
    
    if(defend){
        damage = static_cast<int>(round(0.5 * RNG.Int(round(0.8 * basedamage), round(1.2 * basedamage))));
        defend = false;
    }
    else damage = static_cast<int>(RNG.Int(round(0.8 * basedamage), round(1.2 * basedamage)));

    cout << "The attacker dealt " << damage << " damage!\n";
    return damage;
}