#pragma once
#ifndef GAME_H
#define GAME_H

#include "Deck.h"
#include "SidePile.h"
#include <string>

class Game {
private:
    Deck Player_Deck;
    Deck Computer_Deck;
    SidePile Player_Pile;
    SidePile Computer_Pile;
    int Player_Wins;
    int Computer_Wins;
    int Game_Mode;
    int Max_Rounds;

    void Setup_Game();
    void Play_Round();
    void View_Options();
    void Display_Game_Result() const;
    

public:
    Game();
    void Start();
    void Set_Game_Mode(int mode);
    void Set_Max_Rounds(int rounds);
    void Welcome_Message() const;
};

#endif // GAME_H