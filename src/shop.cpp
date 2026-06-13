#include "shop.hpp"
#include "utility.hpp"

#include <iostream>
using std::cout;

void ShopFunction(Player &player, const Shop &config){
    Shop shop(config);
    int opt = 0;

    while(true){
        cout << "\n_____________________________________________\n";
        cout << "Welcome Traveler!\n";
        cout << "Care to look at my wares?\n\n";
        cout << "0. Finish\n1. Buy\n2. Sell\n\n- ";
        NumInput(opt);

        switch(opt){
            case 0:
                cout << "\nBest of luck for your adventure!\n\n";
                return;
            case 1:
                Buy(player, shop);
                break;
            case 2:
                Sell(player, shop);
                break;
            default:
                cout << "Invalid Input!\n";
        }
    }
}

void Buy(Player &player, Shop &shop){
    int opt = 0;

    while(true){
        cout << "Gold : " << player.GetGold() << "\n";
        ShowEquipment(shop.GetInventory(), true);
        ShowInventory(shop.GetInventory(), true);
        cout << "\n-2 to buy weapon.\n-1 to buy armor.\n0 to finish.\n\n- ";
        NumInput(opt);

        if(opt > 0 && opt <= size(shop.GetInventory().GetConsumables())){
            if(shop.GetInventory().GetConsumables()[opt-1].GetValue() <= player.GetGold()){
                player.GetGold() -= shop.GetInventory().GetConsumables()[opt-1].GetValue();
                player.GetInventory().GetConsumables().push_back(shop.GetInventory().GetConsumables()[opt-1]);
                cout << "You bought " << shop.GetInventory().GetConsumables()[opt-1].GetName() << ".\n\n";
                shop.GetInventory().GetConsumables().erase(shop.GetInventory().GetConsumables().begin() + opt-1);
            }
            else cout << "You don't have enough gold!\n";
        }
        else if(opt == -1){
            if(shop.GetInventory().GetArmor().GetValue() <= player.GetGold()){
                cout << "You bought " << shop.GetInventory().GetArmor().GetName() << ".\n\n";
                player.GetInventory().GetArmor() = shop.GetInventory().GetArmor();
                shop.GetInventory().GetArmor() = NoArmor();
                player.BuffUpdate();
            }
            else cout << "You don't have enough gold!\n";
        }
        else if(opt == -2){
            if(shop.GetInventory().GetWeapon().GetValue() <= player.GetGold()){
                cout << "You bought " << shop.GetInventory().GetWeapon().GetName() << ".\n\n";
                player.GetInventory().GetWeapon() = shop.GetInventory().GetWeapon();
                shop.GetInventory().GetWeapon() = NoWeapon();
                player.BuffUpdate();
            }
            else cout << "You don't have enough gold!\n";
        }
        else if(opt == 0) return;
        else cout << "Invalid Input!\n";
    }
}

void Sell(Player &player, Shop &shop){
    int opt = 0;

    while(true){
        cout << "Gold : " << player.GetGold() << "\n";
        ShowInventory(player.GetInventory(), true);
        cout << "\n0 to finish.\n\n- ";
        NumInput(opt);

        if(opt > 0 && opt <= size(player.GetInventory().GetConsumables())){
            player.GetGold() += player.GetInventory().GetConsumables()[opt-1].GetValue();
            shop.GetInventory().GetConsumables().push_back(player.GetInventory().GetConsumables()[opt-1]);
            player.GetInventory().GetConsumables().erase(player.GetInventory().GetConsumables().begin() + opt-1);
            cout << player.GetInventory().GetConsumables()[opt-1].GetName() << " was sold for " << player.GetInventory().GetConsumables()[opt-1].GetValue() << ".\n\n";
        }
        else if(opt == 0) return;
        else cout << "Invalid Input!\n";
    }
}