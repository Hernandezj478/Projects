/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   ScoreCard.h
 * Author: Joseph Hernandez
 *
 * Created on November 3, 2022, 12:42 AM
 */

#ifndef SCORECARD_H
#define SCORECARD_H

#include <string>
#include <stack>
#include <functional>
#include <fstream>
#include "Dice.hpp"


class ScoreCard{
    public:
        ScoreCard();//Default Constructor
        void printScoreCard();
        void printCategories();
        void saveCard(string,string);
        void replaceCard(string,string);
        int getScore();
        
        bool setScoreCell(string,Dice);
        bool isCardFull();
        
        static string format(string);
        
        inline int getCurrGame(){return currGame;}
        
        void debugCard();
        
    private:
        short currGame = 0;
        static const short numGames = 5;
        static const short upRows   = 9;
        static const short lwRows   = 11;
        static const short bSize    = 13;
        
        //Bit vector to hold if section is filled
        bool bit_vector[bSize];
        //Stack to hold YAHTZEE BONUS
        vector<int> bonus;
        // container to hold upper section values (up to 5 games)
        int upperSec[numGames][upRows];
        // container to hold lower section values (up to 5 games)
        int lowerSec[numGames][lwRows];
        // containter to hold upper section names
        string upperName[upRows];
        // container to hold lower section names
        string lowerName[lwRows];
};

#endif /* SCORECARD_H */

