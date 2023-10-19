/* 
 * File:   main.cpp
 * Author: Joseph Hernandez
 * Created on November 3, 2022, 5:29 PM
 */

#include "lib/src/Game.hpp"

void debug(Game&);

int main(int argc, char** argv) {
    Game game;
 

    bool debugGame = false;
    
    bool playGame = game.gameMenu(debugGame);
    if(debugGame){
        debug(game);
        return 0;
    }
    
    if(playGame){
        system("clear");
        game.start();
        game.end();
    }
    
    
    return 0;
}

void debug(Game &game){
    game.debugGame();
}