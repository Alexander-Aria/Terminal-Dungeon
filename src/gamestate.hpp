#pragma once

#include "player.hpp"

enum class Status{
    ONGOING = 0,
    WIN = 1,
    LOSE = -1,
    TURNBACK = -2
};

class GameState{
    private:
        int stage = 0;
        Status status = Status::ONGOING;
        Player player;
    public:
        GameState(bool developermode){
            if(developermode){
                player.GetGold() = 10000;
                player.GetInventory() = Inventory(AllItems());
                player.GetStats() = {10000, 10000, 10000, 10000};
            }
        }

        int &GetStage(){return stage;}
        Status &GetStatus(){return status;}
        Player &GetPlayer(){return player;}

        void BattleStateReset(){
            player.GetStats().GetStrengthBoost() = 0;
            player.GetStats().GetDefenseBoost() = 0;
        }
};

void Game(bool developermode);
inline bool IsRunning(Status &status) {return (status == Status::ONGOING);}
