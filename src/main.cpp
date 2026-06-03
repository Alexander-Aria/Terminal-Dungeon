#include "main.hpp"

template <typename T>
void NumInput(T &num){
    while(!(cin >> num)){
        cin.clear();
        Ignore();
        cout << "Invalid input!\n";
        cout << "Try again : ";
    }
}

void Ignore(){cin.ignore(numeric_limits<streamsize>::max(),'\n');}

void Game(){
    GameState game;
    bool loop = true;

    while(loop){
        switch(game.GetStage()){
            case 0:
                StageZero(game.GetStage(), game);
                game.GetStage()++;
                break;
        }
        if(game.GetStage() == 10){
            cout << "Congratulations!\n";
            cout << "You won the game!\n";
            cout << "Thanks for playing!\n";
            loop = false;
        }
        else if(game.GetStage() == -1){
            cout << "You died!\n";
            loop = false;
        }
    }
}

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

void InventoryAccess(Player &player){
    int itemnum = 1, opt = 0;   

    if(size(player.GetInventory().GetConsumables()) == 0) cout << "You don't have any consumables!\n";
    else{
        for(auto &i : player.GetInventory().GetConsumables()){
            cout << itemnum << ". " << i.GetName() << "\n";
            itemnum++;
        }
        itemnum = 1;
        NumInput(opt);
        player.GetStats().GetHealth() += player.GetInventory().GetConsumables()[opt-1].GetHealth();
        if(player.GetStats().GetHealth() > player.GetStats().GetMaxHealth()) player.GetStats().GetHealth() = player.GetStats().GetMaxHealth();
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
    int basedamage = round(10 * attackerstats.GetStrength()/defenderstats.GetDefense());
    int damage; 
    
    if(defend){
        damage = 0.5 * RNG.Int(round(0.8 * basedamage), round(1.2 * basedamage));
        defend = false;
    }
    else damage = RNG.Int(round(0.8 * basedamage), round(1.2 * basedamage));

    cout << "The attacker dealt " << damage << " damage!\n";
    return damage;
}

void StageZero(int &stage, GameState &game){
    char choice = 'n';
    Enemy wolfcub(Stats(50, 50, 3, 5), "Wolf Cub", "A young wolf cub.");

    cout << "Do you want to play the tutorial? y/n?";
    cin >> choice;
    Ignore();
    if(choice == 'y'){
        Battle(stage, game, wolfcub);
    }
    stage++;
}

int main(){
    int opt, status = 0;

    cout << "______________________________\n";
    cout << "Terminal Dungeon\n";
    cout << "0. Exit\n1. Start\n\n- ";
    NumInput(opt);
    switch(opt){
        case 0:
            cout << "Exiting...\n";
            return 0;
        case 1:
            Game();
            break;
        case 2:
            cout << "Invalid input!\n";
    }
}