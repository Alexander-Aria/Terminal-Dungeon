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
                player.GetInventory() = Inventory(AllItems(), LongSword(), Crossbow(), LightChainmailArmor());
                player.GetStats() = {10000, 10000, 10000, 10000};
            }
            else{
                player.GetInventory() = Inventory({}, IronSword(), NoRanged(), LeatherArmor());
            }
        }

        int &GetStage(){return stage;}
        Status &GetStatus(){return status;}
        Player &GetPlayer(){return player;}

        void BattleStateReset(){
            player.GetStats().GetTempStrengthBoost() = 0;
            player.GetStats().GetTempDefenseBoost() = 0;
            player.GetBlock() = false;
            player.GetInventory().GetRanged().GetAmmoAmount() = player.GetInventory().GetRanged().GetMaxAmmo();
        }
};

void Game(bool developermode);
inline bool IsRunning(Status &status) {return (status == Status::ONGOING);}
