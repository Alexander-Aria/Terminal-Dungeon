#include "shop.hpp"
#include "utility.hpp"

#include <iostream>
using std::cout;

void ShopFunction(Player &player, const Shop &config){
    Shop shop(config);
    int opt = 0;

    cout << "\n_____________________________________________\n";
    cout << "Welcome Traveler!\n";
    cout << "Care to look at my wares?\n\n";
    while(true){
        cout << "Gold : " << player.GetGold() << "\n";
        ShowInventory(shop.GetInventory(), true);
        cout << "\n0 to finish.\n\n- ";
        NumInput(opt);

        if(opt > 0 && opt <= size(shop.GetInventory().GetConsumables())){
            if(shop.GetInventory().GetConsumables()[opt-1].GetValue() <= player.GetGold()){
                player.GetInventory().GetConsumables().push_back(shop.GetInventory().GetConsumables()[opt-1]);
                player.GetGold() -= shop.GetInventory().GetConsumables()[opt-1].GetValue();
                cout << "You purchased " << shop.GetInventory().GetConsumables()[opt-1].GetName() << " (" << shop.GetInventory().GetConsumables()[opt-1].GetValue() << ")\n";
                shop.GetInventory().GetConsumables().erase(shop.GetInventory().GetConsumables().begin() + opt-1);
            }
            else cout << "You don't have enough gold!\n";
        }
        else if(opt == 0) break;
        else cout << "Invalid Input!\n";
    }
    cout << "\nBest of luck for your adventure!\n\n";
}