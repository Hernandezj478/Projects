/*
 * File: Game.h
 * Author: Joseph Hernandez
 * Created on 03/26/22
 * Last Modified 03/31/22
 * Purpose: Game class description
 */

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <iomanip>
using namespace std;



class Game{
    private:
        bool win;
        int tries;
        int size;
        
        bool duplicate();
        int difficulty(bool&);
        void winMessage();
        void specialWinMessage();
        void banterMessage();
    public:
        Game();
        bool getWin() const{return win;}
};

#endif

