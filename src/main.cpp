#include "gamestate.hpp"
#include "stages.hpp"
#include "utility.hpp"

#include <iostream>

using std::cout;
using std::cin;

void Game(bool developermode){
    GameState game(developermode);
    bool loop = true;
    int devstage = 0;

    if(developermode){
        cout << "\n____________________________________\n";
        cout << "DEVELOPER MODE\n\n";
        cout << "Choose stage (0-10) : ";
        NumInput(devstage);
        game.GetStage() = devstage;
    }

    while(loop){
        switch(game.GetStage()){
            case 0:
                StageZero(game);
                break;
            case 1:
                StageOne(game);
                break;
            case 2:
                StageTwo(game);
                break;
            case 3:
                StageThree(game);
                break;
            default:
                cout << "Error : Out of the stage range!\n";
                return;
        }
        if(game.GetStatus() == Status::WIN){
            cout << "Congratulations!\n";
            cout << "You won the game!\n";
            cout << "Thanks for playing!\n";
            loop = false;
        }
        else if(game.GetStatus() == Status::LOSE){
            cout << "You lose!\n";
            loop = false;
        }
        else if(game.GetStatus() == Status::TURNBACK){
            cout << "Fearing the danger ahead, you decided to turn back and left.\n";
            loop = false;
        }
    }
}

int main(){
    int opt, status = 0;

    while(true){
        cout << "______________________________\n";
        cout << "Terminal Dungeon\n";
        cout << "0. Exit\n1. Start\n2. Start (Developer Mode)\n\n- ";
        NumInput(opt);
        switch(opt){
            case 0:
                cout << "Exiting...\n";
                return 0;
            case 1:
                Game(false);
                break;
            case 2:
                Game(true);
                break;
            default:
                cout << "Invalid input!\n";
                break;
        }
    }
}