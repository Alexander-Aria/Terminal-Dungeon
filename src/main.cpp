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
    cout << enemy.GetDescription() << "\n";
    while(status == 0){
        cout << "__________________________\n";
        cout << "Player Health : " << game.GetStats().GetHealth() << "\n";
        cout << enemy.GetName() << " Health : " << enemy.GetStats().GetHealth() << "\n\n";

        PlayerTurn(game, enemy, playerdefend, enemydefend);
        EnemyTurn(game, enemy, playerdefend, enemydefend);

    }
    if(status = -1 && stage != 0) cout << "You lose!\n";
    else cout << "You won!\n";
    return status;
}

int StatusCheck(Stats &playerstats, Stats &enemystats){
    // WIP
}

void PlayerTurn(GameState &game, Enemy &enemy, bool &playerdefend, bool &enemydefend){
    int opt = 0;

    cout << "1. Attack\n2. Defend\n3. Items\n4. Surrender\n\n- ";
    NumInput(opt);
    switch(opt){
        case 1:
            if(enemydefend) enemy.GetStats().GetHealth() -= 0.5 * Attack(game.GetStats(), enemy.GetStats());
            else enemy.GetStats().GetHealth() -= Attack(game.GetStats(), enemy.GetStats());
            break;
        case 2:
            playerdefend = true;
            break;
        case 3:
            // WIP
            break;
        case 4:
            game.GetStats().GetHealth() = 0;
            break;
    }
}

void EnemyTurn(GameState &game, Enemy &enemy, bool &playerdefend, bool &enemydefend){
    Random RNG;
    int range[2];

    if(enemy.GetName() == "Dummy") {
        range[0] = 0;
        range[1] = 0;
    }

    switch(RNG.Int(range[0], range[1])){
        case 0:
            cout << enemy.GetName() << " does nothing!\n";
            break;
    }
}

int Attack(Stats &attackerstats, Stats &defenderstats){
    Random RNG;
    int basedamage = round(10 * attackerstats.GetStrength()/defenderstats.GetDefense());
    int damage = RNG.Int(round(0.8 * basedamage), round(1.2 * basedamage));

    cout << "The attacker dealt " << damage << " damage!\n";
    return damage;
}

void StageZero(int &stage, GameState &game){
    char choice = 'n';
    Enemy dummy(Stats(10000, 10000, 0, 10000), "Dummy", "Test Dummy.");

    cout << "Do you want to play the tutorial? y/n?";
    cin >> choice;
    Ignore();
    if(choice == 'y'){
        cout << "Try interacting with the dummy. You can surrender to continue.\n";
        Battle(stage, game, dummy);
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