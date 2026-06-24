#include "gamestate.hpp"
#include "stages.hpp"
#include "enemy.hpp"
#include "battle.hpp"
#include "shop.hpp"
#include "utility.hpp"

#include <iostream>
#include <memory>

using std::cout;
using std::cin;
using std::unique_ptr;
using std::make_unique;

void Choice(GameState &game){
    bool done = false;
    int opt = 0;

    while(!done){
        cout << "_____________________________\n";
        cout << "Player Lv." << game.GetPlayer().GetLevel() << "\n";
        cout << "Player EXP : " << game.GetPlayer().GetExp() << "/250\n";
        cout << "Gold : " << game.GetPlayer().GetGold() << "\n\n";
        cout << "0. Turn Back (Give Up)\n1. Continue\n2. Check Stats\n3. Items\n\n- ";
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
                game.GetPlayer().StatsCheck();
                break;
            case 3:
                game.GetPlayer().InventoryAccess(BattleState::OUTBATTLE);
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
    auto enemy1 = make_unique<BatEnemy>(Bat()), enemy2 = make_unique<BatEnemy>(Bat());

    game.GetPlayer().GetInventory().GetConsumables().push_back(SmallPotion());
    game.GetPlayer().GetGold() = 100;

    cout << "\nAREA 1\n\n";
    cout << "You are a lone adventurer looking for treasures inside a dungeon.\n";
    cout << "You entered the dungeon with a small potion and 100 gold.\n\n";
    Choice(game);
    if(!IsRunning(game.GetStatus())) return;
    
    cout << "Entering the dungeon, you encountered a few teritorial bats.\n";
    cout << "A bat attacks!\n\n";
    Battle(game, *enemy1);
    if(!IsRunning(game.GetStatus())) return;

    cout << "Before you can recover, another bat attacks!\n\n";
    Battle(game, *enemy2);
    if(!IsRunning(game.GetStatus())) return;

    cout << "You found the entrance to the next area. Do you still want to explore this area?\n";
    if(YesorNo()) StageOneExtra(game);
    if(!IsRunning(game.GetStatus())) return;

    game.GetStage()++;
}

void StageOneExtra(GameState &game){
    auto enemy1 = make_unique<BatEnemy>(AlphaBat());

    cout << "You decided to continue exploring area 1 before you head to area 2.\n";
    cout << "You see a bat nest up ahead. A bat, seemingly larger and more powerful is guarding the nest.\n";
    cout << "Behind the nest is a chest.\n\n";
    Choice(game);
    if(!IsRunning(game.GetStatus())) return;

    cout << "You charge towards the large bat!\n";
    Battle(game, *enemy1);
    if(!IsRunning(game.GetStatus())) return;

    game.GetPlayer().GetInventory().GetConsumables().push_back(LargePotion());
    cout << "You opened the chest...\n";
    cout << "You got a Large Potion!\n\n";
}

void StageTwo(GameState &game){
    auto enemy1 = make_unique<WolfEnemy>(WolfCub()), enemy2 = make_unique<WolfEnemy>(FemaleWolf());

    game.GetPlayer().GetInventory().GetConsumables().push_back(SmallPotion());

    cout << "\nAREA 2\n\n";
    cout << "After you have beaten the bats, you continued.\n";
    cout << "You found a small potion on the way.\n\n";
    Choice(game);
    if(!IsRunning(game.GetStatus())) return;

    cout << "You hear rustling behind you...\n";
    cout << "A wolf cub jumps at you!\n\n";
    Battle(game, *enemy1);
    if(!IsRunning(game.GetStatus())) return;

    cout << "You easily beat the wolf cub. However, it is the least of your worries.\n";
    cout << "You hear a wolf approaching from the distance, presumably the mother.\n";
    cout << "You prepare for the battle.\n\n";
    Choice(game);
    if(!IsRunning(game.GetStatus())) return;

    cout << "\nAfter seeing the dead wolf cub, the female wolf immediately jumps at you!\n\n";
    Battle(game, *enemy2);
    if(!IsRunning(game.GetStatus())) return;

    cout << "You found the entrance to the next area. Do you still want to explore this Area?\n";
    if(YesorNo()) StageTwoExtra(game);
    if(!IsRunning(game.GetStatus())) return;
    
    game.GetStage()++;
}

void StageTwoExtra(GameState &game){
    auto enemy1 = make_unique<WolfEnemy>(MaleWolf());

    cout << "You decided to continue exploring area 2 before you head to area 3.\n";
    cout << "You found a wolf den, inside lies a male wolf guarding the den.\n";
    cout << "Inside the den lies seemingly a magical stone you might be able to use.\n\n";
    Choice(game);
    if(!IsRunning(game.GetStatus())) return;

    cout << "\nAfter preparing yourself, you charge into the den!\n\n";
    Battle(game, *enemy1);
    if(!IsRunning(game.GetStatus())) return;

    game.GetPlayer().GetInventory().GetConsumables().push_back(PowerStone());
    cout << "You got a Power Stone!\n\n";
}

void StageThree(GameState &game){
    auto enemy1 = make_unique<BanditEnemy>(Bandit());

    cout << "\nAREA 3\n\n";
    cout << "As you continue going deeper into the dungeon, you saw a dim light in the distance...\n";
    cout << "An old shack lies in front of you with a sign hanging from the side, [SHOP]. Do you want to go in?\n\n";
    if(YesorNo()) {
        cout << "\nYou decided to go in the shack...\n";
        ShopFunction(game.GetPlayer(), ShopConfigOne());
    }
    else cout << "\nYou decided to ignore the shack and continue with your journey...\n\n";
    
    Choice(game);
    if(!IsRunning(game.GetStatus())) return;

    cout << "As you continue, you have a subtle feeling that someone is watching you...\n";
    cout << "You turned your back and dodged just in time as a bandit tries to attack you from behind!\n\n";
    Battle(game, *enemy1);
    if(!IsRunning(game.GetStatus())) return;

    cout << "After running into the bandit and finding the old shop, you came to the realization that you aren't the only human in this dungeon.\n";
    cout << "You wonder if there are actually a settlement inside...\n\n";

    cout << "You found the entrance to the next area. Do you still want to explore this Area?\n";
    if(YesorNo()) StageThreeExtra(game);
    if(!IsRunning(game.GetStatus())) return;
    game.GetStage()++;
}

void StageThreeExtra(GameState &game){
    cout << "You decided to continue exploring area 3 before you head to the area 4.\n";
    cout << "You found an empty camp. The previous bandit must have camped here.\n";
    cout << "You rummaged the camp and found 100 gold!\n\n";

    game.GetPlayer().GetGold() += 100;
}

void StageFour(GameState &game){
    auto enemy1 = make_unique<BanditEnemy>(Bandit()), enemy2 = make_unique<BanditEnemy>(BanditLeader());

    cout << "\nAREA 4\n\n";
    cout << "As you continue down into area 4, you run across bandit camp in the way.\n";
    cout << "There lies two bandits. One of them is a regular bandit and the other one is different.\n";
    cout << "He seems tougher and with better equipments. A shiny crossbow in his left hand catches your attention.\n\n";

    Choice(game);
    if(!IsRunning(game.GetStatus())) return;

    cout << "\nThe regular bandit notices you and attacks first!\n\n";
    Battle(game, *enemy1);
    if(!IsRunning(game.GetStatus())) return;

    cout << "\nAfter the leader bandit watch as his henchman fall, he decided to play a bit more carefully and intelligently.\n\n";
    Battle(game, *enemy2);
    if(!IsRunning(game.GetStatus())) return;

    cout << "You got a crossbow!\n\n";
    game.GetPlayer().ChangeEquipment(Crossbow());

    cout << "You found the entrance to the next area. Do you still want to explore this area?\n";
    if(YesorNo()) StageFourExtra(game);
    if(!IsRunning(game.GetStatus())) return;
}

void StageFourExtra(GameState &game){
    auto enemy1 = make_unique<GolemEnemy>(BrokenGolem());

    cout << "While exploring area 4, you found an abandoned temple.\n";
    cout << "In the front lies a couple of bandit corpses as well as a magical golem guarding the temple.\n";
    cout << "The golem seems to be heavily damaged and vulnerable.\n";

    Choice(game);
    if(!IsRunning(game.GetStatus())) return;

    cout << "\nAfter preparing yourself, you charge into battle!\n\n";

    Battle(game, *enemy1);
    if(!IsRunning(game.GetStatus())) return;

    game.GetPlayer().GetInventory().GetConsumables().push_back(ArmorStone());
    game.GetPlayer().GetInventory().GetConsumables().push_back(LargePotion());
    cout << "After defeating the broken golem, you rummaged the temple and found an armor stone and a large potion.\n\n";
}

void StageFive(GameState &game){
    auto enemy1 = make_unique<GuardEnemy>(PatrolGuard()), enemy2 = make_unique<GuardEnemy>(PatrolGuard());

    cout << "\nAREA 5\n\n";
    cout << "Area 5 is unlike the previous ones. \n";
    cout << "A few lanterns are standing. On the side of the lanterns hangs an unfamiliar flag.\n";
    cout << "A path leads the way.\n";
    cout << "Before you continue, you decided to take a break.\n\n";

    Choice(game);
    if(!IsRunning(game.GetStatus())) return;

    cout << "As you go down the path, two patrolling guards block your path.\n";
    cout << "They are not the bandits. Their uniforms are strikingly similar to the flag on the lanterns.\n";
    cout << "Before you can interact with them, they immediately raised their sword towards you! Do they think you're a part of the bandits?\n";
    cout << "You tried to reason with them but they don't seem to understand what you said.\n";
    cout << "You don't have any other choice but to fight them.\n\n";

    Battle(game, *enemy1);
    if(!IsRunning(game.GetStatus())) return;

    Battle(game, *enemy2);
    if(!IsRunning(game.GetStatus())) return;

    cout << "You did not want to fight them. You still don't understand why they are so agressive.\n";
    cout << "Still puzzled, you continued forward.\n\n";

    cout << "You found the entrance to the next area. Do you still want to explore this area?\n";
    if(YesorNo()) StageFiveExtra(game);
    if(!IsRunning(game.GetStatus())) return;

    // Temporary
    if(game.GetStatus() == Status::ONGOING) game.GetStatus() = Status::WIN;
}

void StageFiveExtra(GameState &game){

}

void StageSix(GameState &game){

}

void StageSixExtra(GameState &game){
    
}

void StageSeven(GameState &game){

}

void StageSevenExtra(GameState &game){

}

void StageEight(GameState &game){

}

void StageEightExtra(GameState &game){

}

void StageNine(GameState &game){

}

void StageNineExtra(GameState &game){
    
}

void StageTen(GameState &game){

}

void StageTenExtra(GameState &game){

}
