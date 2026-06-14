#include "gamestate.hpp"
#include "stages.hpp"
#include "enemy.hpp"
#include "battle.hpp"
#include "shop.hpp"
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
                InventoryAccess(game.GetPlayer(), BattleState::OUTBATTLE);
                break;
        }
    }
}

void StageZero(GameState &game){
    int opt = 0;
    Enemy enemy = Dummy();

    cout << "Do you want to play the tutorial?\n";
    cout << "1. Yes\n2. No\n\n- ";
    NumInput(opt);

    if(opt == 1){
        cout << "\nTUTORIAL\n\n";
        Battle(game, enemy);
    }
    game.GetPlayer().GetStats().GetHealth() = game.GetPlayer().GetStats().GetMaxHealth();
    game.GetStage()++;
}

void StageOne(GameState &game){
    Enemy enemy1 = Bat(), enemy2 = Bat();

    game.GetPlayer().GetInventory().GetConsumables().push_back(SmallPotion());
    game.GetPlayer().GetGold() = 100;

    cout << "\nFLOOR 1\n\n";
    cout << "You are a lone adventurer looking for treasures inside a dungeon.\n";
    cout << "You entered a dungeon with a small potion and 100 gold.\n\n";
    Choice(game);
    if(!IsRunning(game.GetStatus())) return;
    
    cout << "Entering the dungeon, you encountered a few teritorial bats.\n";
    cout << "A bat attacks!\n\n";
    Battle(game, enemy1);
    if(!IsRunning(game.GetStatus())) return;

    cout << "Before you can recover, another bat attacks!\n\n";
    Battle(game, enemy2);
    if(!IsRunning(game.GetStatus())) return;

    cout << "You found the entrance to the next floor. Do you still want to explore this floor?\n";
    if(YesorNo()) StageOneExtra(game);
    if(!IsRunning(game.GetStatus())) return;

    game.GetStage()++;
}

void StageOneExtra(GameState &game){
    Enemy enemy1 = AlphaBat();

    cout << "You decided to continue exploring the first floor before you head to the second floor.\n";
    cout << "You see a bat nest up ahead. A bat, seemingly larger and more powerful is guarding the nest.\n";
    cout << "Behind the nest is a chest.\n";
    Choice(game);
    if(!IsRunning(game.GetStatus())) return;

    cout << "You charge towards the large bat!\n";
    Battle(game, enemy1);
    if(!IsRunning(game.GetStatus())) return;

    game.GetPlayer().GetInventory().GetConsumables().push_back(LargePotion());
    cout << "You opened the chest...\n";
    cout << "You got a Large Potion!\n\n";
}

void StageTwo(GameState &game){
    Enemy enemy1 = WolfCub(), enemy2 = FemaleWolf(), enemy3 = MaleWolf();

    game.GetPlayer().GetInventory().GetConsumables().push_back(SmallPotion());

    cout << "\nFLOOR 2\n\n";
    cout << "After you have beaten the bats, you continued.\n";
    cout << "Exploring the first floor, you found a small potion.\n\n";
    Choice(game);
    if(!IsRunning(game.GetStatus())) return;

    cout << "Suddenly, a wolf cub jumps at you!\n\n";
    Battle(game, enemy1);
    if(!IsRunning(game.GetStatus())) return;

    cout << "You easily beat the wolf cub. However, it is the least of your worries.\n";
    cout << "You hear a wolf approaching from the distance, presumably the mother.\n";
    cout << "You prepare for the battle.\n\n";
    Choice(game);
    if(!IsRunning(game.GetStatus())) return;

    cout << "\nAfter seeing the dead wolf cub, the female wolf immediately jumps at you!\n\n";
    Battle(game, enemy2);
    if(!IsRunning(game.GetStatus())) return;

    cout << "You found the entrance to the next floor. Do you still want to explore this floor?\n";
    if(YesorNo()) StageTwoExtra(game);
    if(!IsRunning(game.GetStatus())) return;
    
    game.GetStage()++;
}

void StageTwoExtra(GameState &game){
    Enemy enemy1 = MaleWolf();

    cout << "You decided to continue exploring the first floor before you head to the third floor.\n";
    cout << "You found a wolf den, inside lies a male wolf guarding the den.\n";
    cout << "Inside the den lies seemingly a magical stone you might be able to use.\n";
    Choice(game);
    if(!IsRunning(game.GetStatus())) return;

    cout << "After preparing yourself, you charge into the den!\n";
    Battle(game, enemy1);
    if(!IsRunning(game.GetStatus())) return;

    game.GetPlayer().GetInventory().GetConsumables().push_back(PowerStone());
    cout << "You got a Power Stone!\n\n";
}

void StageThree(GameState &game){
    Enemy enemy1 = Bandit();

    cout << "\nFLOOR 3\n\n";
    cout << "As you continue going deeper into the dungeon, you saw a dim light in the distance...\n";
    cout << "An old shack lies in front of you with a sign hanging from the side, [SHOP]. Do you want to go in?\n";
    if(YesorNo()) {
        cout << "\nYou decided to go in the shack...\n";
        ShopFunction(game.GetPlayer(), ShopConfigOne());
    }
    else cout << "\nYou decided to ignore the shack and continue with your journey...\n";
    
    Choice(game);
    if(!IsRunning(game.GetStatus())) return;

    cout << "As you continue, you have a subtle feeling that someone is watching you...\n";
    cout << "You turned your back and dodged just in time as a bandit tries to attack you from behind!\n";
    Battle(game, enemy1);
    if(!IsRunning(game.GetStatus())) return;

    cout << "After defeating the bandit and the old shack, you came to the realization that you aren't the only human in this dungeon.\n";
    cout << "You wonder if there are actually a settlement inside...\n\n";

    cout << "You found the entrance to the next floor. Do you still want to explore this floor?\n";
    if(YesorNo()) StageThreeExtra(game);
    if(!IsRunning(game.GetStatus())) return;
    game.GetStage()++;

    // Temporary
    if(game.GetStatus() == Status::ONGOING) game.GetStatus() = Status::WIN;
}

void StageThreeExtra(GameState &game){
    
}