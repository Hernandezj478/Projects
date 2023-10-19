/*
 * File: PlayGame.h
 * Author: Joseph Hernandez
 * Created on 03/28/22
 * Last Modified 03/31/22
 * Purpose: PlayGame class description
 */

#ifndef PLAYGAME_H
#define PLAYGAME_H

#include <iostream>
#include <string>
#include <ctime>

using namespace std;


class PlayGame{
    private:
        int p_mChoice;
    public:
        PlayGame();
        void gameRules();
        int mMenu(string);
        int playAgain();
};

#endif /* PLAYGAME_H */