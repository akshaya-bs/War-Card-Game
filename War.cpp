#include "Game.h"
#include <iostream>

int main() {
    Game game;
    int gameMode;

    game.Welcome_Message();
    std::cin >> gameMode;

    if (gameMode == 1 || gameMode == 2) {
        game.Set_Game_Mode(gameMode);
        game.Start();
    }
    else {
        std::cout << "Invalid selection. Exiting the game.\n";
    }

    return 0;
}