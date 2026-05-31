#include "main.hpp"

template <typename T>
void NumInput(T &num){
    while(!cin >> num){
        cin.clear;
        Ignore();
        cout << "Invalid input!\n";
        cout << "Try again : ";
    }
}

void Ignore(){cin.ignore(numeric_limits<streamsize>::max(),'\n');}

void Game(int save){
    GameState game;
    bool loop = true;

    while(loop){
        switch(game.GetStage()){
            case 0:
                Start(game.GetStage());
                break;
        }
        if(game.GetStage() == 1){
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

void Start(int &stage){
    int status = 0;
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
            Game(0);
            break;
        case 2:
            cout << "Invalid input!\n";
    }
}