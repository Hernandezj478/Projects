/* 
 * File:   Player.h
 * Author: Joseph Hernandez
 * Created on November 3, 2022, 9:48 PM
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <cstring>
#include "ScoreCard.hpp"

//using namespace std;

class Player{
    public:
        Player();
        Player(string,unsigned int);
        void resetDKeep(int*,int);
        void setName(string);
        void selCat(Dice);
        void printCard();
        void throwDice(Dice&,int);
        void takeTurn(Dice);
        void saveCard();
        void setScore();
        void checkFile();
        void createFile();
        int keepDice();
        
        bool isEmpty(fstream&);
        bool isPlayerDone();
        
        inline int getScore(){return score;}
        inline string getName(){return userName;}
        
        void debugPlayer(Dice);
    private:
        int score=0;
        int numWins=0;
        string userName;
        ScoreCard card;
        unsigned int playerID;
        bool holdDice(char&,int);
        int *holdCheck(char,int);
};

#endif /* PLAYER_H */

