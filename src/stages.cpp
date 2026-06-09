#include "gamestate.hpp"
#include "stages.hpp"
#include "enemy.hpp"
#include "battle.hpp"
#include "utility.hpp"

#include <iostream>

using std::cout;
using std::cin;

bool GameStatusCheck(Status &status){return (status != Status::ONGOING);}

void Choice(GameState &game){
    bool done = false;
    int opt = 0;

    while(!done){
        cout << "_____________________________\n";
        cout << "Player Lv." << game.GetPlayer().GetLevel() << "\n";
        cout << "Player EXP : " << game.GetPlayer().GetExp() << "/250\n\n";
        cout << "0. Turn Back\n1. Continue\n2. Check Stats\n3. Items\n\n-";
        NumInput(opt);
        switch(opt){
            case 0:
                game.GetStatus() = Status::TURNBACK;
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
    Enemy enemy = Dummy();

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
    Enemy enemy1 = Bat(), enemy2 = Bat();

    game.GetPlayer().GetInventory().GetConsumables().push_back(SmallPotion());
    game.GetPlayer().GetGold() = 100;

    cout << "\nFLOOR 1\n\n";
    cout << "You are a lone adventurer looking for treasures inside a dungeon.\n";
    cout << "You entered a dungeon with a small potion and 100 gold.\n\n";
    Choice(game);
    if(GameStatusCheck(game.GetStatus())) return;
    
    cout << "Entering the dungeon, you encountered a few teritorial bats.\n";
    cout << "A bat attacks!\n\n";
    Battle(game, enemy1);
    if(GameStatusCheck(game.GetStatus())) return;

    cout << "Before you can recover, another bat attacks!\n\n";
    Battle(game, enemy2);
    if(GameStatusCheck(game.GetStatus())) return;

    game.GetStage()++;
}

void StageTwo(GameState &game) {
    int opt = 0;
    Enemy enemy1 = WolfCub(), enemy2 = FemaleWolf(), enemy3 = MaleWolf();

    game.GetPlayer().GetInventory().GetConsumables().push_back(SmallPotion());

    cout << "\nFLOOR 2\n\n";
    cout << "After you have beaten the bats, you continued.\n";
    cout << "Exploring the first floor, you found a small potion.\n\n";
    Choice(game);
    if(GameStatusCheck(game.GetStatus())) return;

    cout << "Suddenly, a wolf cub jumps at you!\n\n";
    Battle(game, enemy1);
    if(GameStatusCheck(game.GetStatus())) return;

    cout << "You easily beat the wolf cub. However, it is the least of your worries.\n";
    cout << "You hear a wolf approaching from the distance, presumably the mother.\n";
    cout << "You prepare for the battle.\n\n";
    Choice(game);
    if(GameStatusCheck(game.GetStatus())) return;

    cout << "\nAfter seeing the dead wolf cub, the female wolf immediately jumps at you!\n\n";
    Battle(game, enemy2);
    if(GameStatusCheck(game.GetStatus())) return;

    cout << "The mother wolf cried one last time before it perished.\n";
    cout << "That last cry brought the father into the room. It looks like you're in trouble...\n\n";
    Battle(game, enemy3);
    if(GameStatusCheck(game.GetStatus())) return;
    
    game.GetStage()++;
    
    // Temporary
    if(game.GetStatus() == Status::ONGOING) game.GetStatus() = Status::WIN;
}