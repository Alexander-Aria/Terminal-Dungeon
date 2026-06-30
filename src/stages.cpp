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
    auto enemy = Dummy();

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
    auto enemy1 = Bat(), enemy2 = Bat();

    game.GetPlayer().GetInventory().GetConsumables().push_back(SmallPotion());
    game.GetPlayer().GetGold() = 100;

    cout << "\nAREA 1\n\n";

    cout << "You are a lone adventurer looking for treasures inside a dungeon.\n";
    cout << "You entered the dungeon with a small potion and 100 gold.\n\n";
    Choice(game);
    if(!IsRunning(game.GetStatus())) return;
    
    cout << "Entering the dungeon, you encountered a few teritorial bats.\n";
    cout << "A bat attacks!\n\n";
    Battle(game, enemy1);
    if(!IsRunning(game.GetStatus())) return;

    cout << "Before you can recover, another bat attacks!\n\n";
    Battle(game, enemy2);
    if(!IsRunning(game.GetStatus())) return;

    cout << "You found the entrance to the next area. Do you still want to explore this area?\n";
    if(YesorNo()) StageOneExtra(game);
    if(!IsRunning(game.GetStatus())) return;

    game.GetStage()++;
}

void StageOneExtra(GameState &game){
    auto enemy1 = AlphaBat();

    cout << "You decided to continue exploring area 1 before you head to area 2.\n";
    cout << "You see a bat nest up ahead. A bat, seemingly larger and more powerful is guarding the nest.\n";
    cout << "Behind the nest is a chest.\n\n";
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
    auto enemy1 = WolfCub(), enemy2 = FemaleWolf();

    game.GetPlayer().GetInventory().GetConsumables().push_back(SmallPotion());

    cout << "\nAREA 2\n\n";

    cout << "After you have beaten the bats, you continued.\n";
    cout << "You found a small potion on the way.\n\n";
    Choice(game);
    if(!IsRunning(game.GetStatus())) return;

    cout << "You hear rustling behind you...\n";
    cout << "A wolf cub jumps at you!\n\n";
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

    cout << "You found the entrance to the next area. Do you still want to explore this Area?\n";
    if(YesorNo()) StageTwoExtra(game);
    if(!IsRunning(game.GetStatus())) return;
    
    game.GetStage()++;
}

void StageTwoExtra(GameState &game){
    auto enemy1 = MaleWolf();

    cout << "You decided to continue exploring area 2 before you head to area 3.\n";
    cout << "You found a wolf den, inside lies a male wolf guarding the den.\n";
    cout << "Inside the den lies seemingly a magical stone you might be able to use.\n\n";
    Choice(game);
    if(!IsRunning(game.GetStatus())) return;

    cout << "\nAfter preparing yourself, you charge into the den!\n\n";
    Battle(game, enemy1);
    if(!IsRunning(game.GetStatus())) return;

    game.GetPlayer().GetInventory().GetConsumables().push_back(PowerStone());
    cout << "You got a Power Stone!\n\n";
}

void StageThree(GameState &game){
    auto enemy1 = Bandit();

    cout << "\nAREA 3\n\n";

    cout << "As you continue going deeper into the dungeon, you saw a dim light in the distance...\n";
    cout << "An old shack lies in front of you with a sign hanging from the side, [SHOP]. Do you want to go in?\n\n";
    if(YesorNo()) {
        cout << "\nYou decided to go in the shack...\n\n";
        cout << "\"Welcome Traveler!\"\n";
        cout << "\"Care to look at my wares?\"";
        ShopFunction(game.GetPlayer(), ShopConfigOne());
        cout << "\nBest of luck for your adventure!\n\n";
    }
    else cout << "\nYou decided to ignore the shack and continue with your journey...\n\n";
    
    Choice(game);
    if(!IsRunning(game.GetStatus())) return;

    cout << "As you continue, you have a subtle feeling that someone is watching you...\n";
    cout << "You turned your back and dodged just in time as a bandit tries to attack you from behind!\n\n";
    Battle(game, enemy1);
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
    auto enemy1 = Bandit(), enemy2 = BanditLeader();

    cout << "\nAREA 4\n\n";

    cout << "As you continue down into area 4, you run across bandit camp in the way.\n";
    cout << "There lies two bandits. One of them is a regular bandit and the other one is different.\n";
    cout << "He seems tougher and with better equipments. A shiny crossbow in his left hand catches your attention.\n\n";

    Choice(game);
    if(!IsRunning(game.GetStatus())) return;

    cout << "\nThe regular bandit notices you and attacks first!\n\n";
    Battle(game, enemy1);
    if(!IsRunning(game.GetStatus())) return;

    cout << "\nAfter the leader bandit watch as his henchman fall, he decided to play a bit more carefully and intelligently.\n\n";
    Battle(game, enemy2);
    if(!IsRunning(game.GetStatus())) return;

    cout << "You got a crossbow and a small potion!\n\n";
    game.GetPlayer().ChangeEquipment(Crossbow());
    game.GetPlayer().GetInventory().GetConsumables().push_back(SmallPotion());

    cout << "You found the entrance to the next area. Do you still want to explore this area?\n";
    if(YesorNo()) StageFourExtra(game);
    if(!IsRunning(game.GetStatus())) return;
    game.GetStage()++;
}

void StageFourExtra(GameState &game){
    auto enemy1 = BrokenGolem();

    cout << "While exploring area 4, you found an abandoned temple.\n";
    cout << "In the front lies a couple of bandit corpses as well as a magical golem guarding the temple.\n";
    cout << "The golem seems to be heavily damaged and vulnerable.\n";

    Choice(game);
    if(!IsRunning(game.GetStatus())) return;

    cout << "\nAfter preparing yourself, you charge into battle!\n\n";

    Battle(game, enemy1);
    if(!IsRunning(game.GetStatus())) return;

    game.GetPlayer().GetInventory().GetConsumables().push_back(ArmorStone());
    game.GetPlayer().GetInventory().GetConsumables().push_back(LargePotion());
    cout << "\nAfter defeating the broken golem, you rummaged the temple and found an armor stone and a large potion.\n\n";
}

void StageFive(GameState &game){
    auto enemy1 = PatrolGuard(), enemy2 = PatrolGuard();

    cout << "\nAREA 5\n\n";

    cout << "Area 5 is unlike the previous ones. \n";
    cout << "A few lanterns are standing. On the side of the lanterns hangs an unfamiliar flag.\n";
    cout << "A path leads the way.\n";
    cout << "Before you continue, you decided to take a break.\n\n";

    Choice(game);
    if(!IsRunning(game.GetStatus())) return;

    cout << "\nAs you go down the path, two patrolling guards block your path.\n";
    cout << "They are not the bandits. Their uniforms are strikingly similar to the flag on the lanterns.\n";
    cout << "Before you can interact with them, they immediately raised their sword towards you! Do they think you're a part of the bandits?\n";
    cout << "You tried to reason with them but they don't seem to understand what you said.\n";
    cout << "You don't have any other choice but to fight them.\n\n";

    Battle(game, enemy1);
    if(!IsRunning(game.GetStatus())) return;

    Battle(game, enemy2);
    if(!IsRunning(game.GetStatus())) return;

    cout << "\nYou did not want to fight them. You still don't understand why they are so agressive.\n";
    cout << "Still puzzled, you continued forward.\n\n";

    cout << "You found the entrance to the next area. Do you still want to explore this area?\n";
    if(YesorNo()) StageFiveExtra(game);
    if(!IsRunning(game.GetStatus())) return;
    game.GetStage()++;
}

void StageFiveExtra(GameState &game){
    auto enemy1 = IceGolem();

    cout << "\nAREA 6\n\n";

    cout << "As you continue exploring area 5, the path is becoming whiter and the air colder...\n";
    cout << "Soon enough, you are surrounded by ice and snow. In front of you lies a cave.\n";
    cout << "A subtle thumping sound can be heard inside the cave. You prepare yourself.\n\n";

    Choice(game);
    if(!IsRunning(game.GetStatus())) return;

    cout << "\nAs you were about to go in, strong freezing wind blew towards you.\n";
    cout << "The freezing cold is weakening you.\n\n";
    game.GetPlayer().GetStats().GetTempStrengthBoost() = -2;

    Battle(game, enemy1);
    if(!IsRunning(game.GetStatus())) return;

    game.GetPlayer().GetInventory().GetConsumables().push_back(LifeStone());
    cout << "The ice golem dropped a life stone!\n\n";

    cout << "After defeating the ice golem, you peeked into the cave.\n";
    cout << "The cave seems very deep and cold.\n";
    cout << "Trembling from the cold, you decided that it's not worth exploring the cave.\n\n";
}

void StageSix(GameState &game){
    auto enemy1 = TrainedWolf();

    cout << "Entering area 6, you found a small village.\n";
    cout << "No flag is in sight and the people seem friendly.\n";
    cout << "However, the village is strangely silent. The people are doing nothing but working.\n\n";

    cout << "On the side of the street lies a shop.\n";
    cout << "Do you want to enter?\n\n";
    if(YesorNo()) {
        cout << "\nYou decided to go in the shop...\n\n";
        cout << "\"What do you... Wait, are you a traveler?\"\n";
        cout << "\"Quick, into my basement.\"\n\n";

        cout << "\"I know we just met but we need your help.\"\n";
        cout << "\"The nearest clan recently enslaved the entire village.\"\n";
        cout << "\"We were forced to give all of our earnings to them.\"\n";
        cout << "\"We're lucky the bandits from the South are giving us aids. We would've starved without them.\"\n\n";
        
        cout << "\"You seem to be a tough fighter. They're coming soon. Can you defeat them?\"\n";
        cout << "\"You can even buy some of my wares I hid from them.\"\n";
        ShopFunction(game.GetPlayer(), ShopConfigTwo());

        cout << "\"Thank you traveler. May god bless you.\"\n\n";

        cout << "Taking the warning, you prepare yourself.\n\n";
    }
    else cout << "\nYou decided to take a break.\n\n";

    Choice(game);
    if(!IsRunning(game.GetStatus())) return;

    cout << "\nYou hear a carriage coming. It's that flag again.\n";
    cout << "It is guarded by an archer and a trained wolf.\n";
    cout << "The carriage stops in front of the shop.\n\n";    

    cout << "You sneaked into the side of the carriage and successfully assasinated the coachman!\n";
    cout << "The wolf immediately strikes!\n\n";

    Battle(game, enemy1);
    if(!IsRunning(game.GetStatus())) return;

    cout << "\nKnowing that she's outmatched, the archer fled into the fog.\n";
    cout << "Do you want to chase her?\n";

    if(YesorNo()) {
        StageSixExtra(game);
        if(!IsRunning(game.GetStatus())) return;
        cout << "\nYou came back into the village.\n\n";
    }
    else cout << "\nGoing into the fog seems like a bad idea. You decided to let her go.\n\n";

    cout << "The once silent village is filled with cheers and applauses.\n";
    cout << "\"Thank you so much hero!\"\n";
    cout << "\"I know you've saved us, but they will come back if we don't fight back.\"\n";
    cout << "\"You don't have to do it alone hero. We will talk to the bandits from the South to assist you.\"\n\n";

    cout << "You see a bandit in the distance...\n";
    cout << "Maybe they're not so bad afterall.\n\n";
    game.GetStage()++;
}

void StageSixExtra(GameState &game){
    auto enemy1 = Archer();

    cout << "You chased the archer into the fog.\n";
    cout << "The lack of vision makes it hard to defend yourself. She could be anywhere.\n\n";
    game.GetPlayer().GetStats().GetTempDefenseBoost() = -2;

    cout << "Maybe this was a bad idea...\n\n";

    Battle(game, enemy1);
    if(!IsRunning(game.GetStatus())) return;

    game.GetPlayer().ChangeEquipment(ShortBow());
    cout << "\nThe archer dropped a short bow!\n\n";
}

void StageSeven(GameState &game){
    auto enemy1 = RoyalGuard();

    cout << "\nAREA 7\n\n";

    cout << "You continued your journey into area 7. But, your goal has changed.\n";
    cout << "You started your journey to search for treasures. Now, an entire village is counting on you.\n\n";

    cout << "You have reached the gate of the clan fortress.\n";
    cout << "It is guarded by two royal guards and archers.\n\n";

    Choice(game);
    if(!IsRunning(game.GetStatus())) return;

    cout << "\nAs you're thinking of a plan, multiple arrows shoot from the bushes!\n";
    cout << "The royal guards are seemingly unaffected by the arrows due to their heavy armor.\n\n";

    cout << "It must be the bandits.\n";
    cout << "Seeing an opening, you rush towards the two royal guards!\n";
    cout << "However, the formation of the royal guards makes it near impossible to break through.\n";
    cout << "Just then, a bandit leader rushes in and takes one of the guards into a fight!\n\n";

    cout << "With a single guard in front of you, it becomes much easier to strike!\n\n";

    Battle(game, enemy1);
    if(!IsRunning(game.GetStatus())) return;

    cout << "\nAfter defeating the royal guard, you saw the bandit leader having trouble with the other guard.\n";
    cout << "You immediately strike the royal guard from behind!\n\n";

    cout << "The bandit leader looks at you and wordlessly nods.\n";
    cout << "You nod back and continue the assault into the fortress!\n\n";

    cout << "This seems like a point of no return...\n";
    game.GetStage()++;
}

void StageEight(GameState &game){
    auto enemy1 = Knight();

    Choice(game);
    if(!IsRunning(game.GetStatus())) return;

    cout << "\nYou rushed into the clan leader's throne.\n";
    cout << "There he is, the leader. You pulled out your bow and shoots!\n";
    cout << "The arrow hits what sounds like pure metal.\n\n";

    cout << "\"You'll need fight harder than that.\"\n\n";

    Battle(game, enemy1);
    if(!IsRunning(game.GetStatus())) return;

    cout << "\nThe clan's most powerful fighter has fallen.\n";
    cout << "Shocked, the clan leader immediately ran.\n";
    cout << "Without hesitation, you chase him.\n";
    game.GetStage()++;
}

void StageNine(GameState &game){
    auto enemy1 = FireGolem();

    cout << "\nYou chased the clan leader into a cave below a volcano.\n";
    cout << "\"Is he insane? He's trapped there!\" You thought.\n\n";

    cout << "AS you go deeper into the cave, you can hear something rumbling deeper.\n";
    cout << "You prepare yourself for the worst.\n\n";

    Choice(game);
    if(!IsRunning(game.GetStatus())) return;

    cout << "Suddenly, a golem rushed towards you!\n\n";

    Battle(game, enemy1);
    if(!IsRunning(game.GetStatus())) return;
    game.GetStage()++;
    
    // Temporary
    if(game.GetStatus() == Status::ONGOING) game.GetStatus() = Status::WIN;
}

void StageTen(GameState &game){

}
