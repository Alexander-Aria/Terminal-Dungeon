#include "gamestate.hpp"
#include "stages.hpp"
#include "enemy.hpp"
#include "battle.hpp"
#include "utility.hpp"

#include <iostream>

using std::cout;
using std::cin;

void Choice(GameState &game){
    bool done = false;
    int opt = 0;

    while(!done){
        cout << "_____________________________\n";
        cout << "Player Lv." << game.GetPlayer().GetLevel() << "\n";
        cout << "Player EXP : " << game.GetPlayer().GetExp() << "\n\n";
        cout << "0. Turn Back\n1. Continue\n2. Check Stats\n3. Items\n\n-";
        NumInput(opt);
        switch(opt){
            case 0:
                game.GetStatus() = -2;
                done = true;
                break;
            case 1:
                done = true;
                break;
            case 2:
                StatsCheck(game.GetPlayer().GetStats());
                break;
            case 3:
                InventoryAccess(game.GetPlayer());
                break;
        }
    }
}

void StageZero(GameState &game){
    char choice = 'n';
    Enemy enemy = WolfCub();

    cout << "Do you want to play the tutorial? y/n?\n\n- ";
    cin >> choice;
    Ignore();
    if(choice == 'y'){
        cout << "\nTUTORIAL\n\n";
        Battle(game, enemy);
    }
    game.HealthReset();
    game.GetStage()++;
}

void StageOne(GameState &game){
    int opt = 0;
    Enemy enemy = Bat();

    game.GetPlayer().GetInventory().GetConsumables().push_back(SmallPotion());
    game.GetPlayer().GetGold() = 100;

    cout << "\nFLOOR 1\n\n";
    cout << "You are a lone adventurer looking for treasures inside a dungeon.\n";
    cout << "You entered a dungeon with a small potion and 100 gold.\n\n";
    Choice(game);
    if(game.GetStatus() == 0) Battle(game, enemy);
    game.GetStage()++;
}