/*
 * File: PlayGame.cpp
 * Author: Joseph Hernandez
 * Created on 03/28/22
 * Last Modified 03/31/22
 * Purpose: PlayGame class implementation
 */

#include "PlayGame.h"
#include "Game.h"

PlayGame::PlayGame(){
    //Create game seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Show main menu and get player choice
    p_mChoice = mMenu("Welcome to the game of Mastermind!");
    
    //if player needs help, display help screen
    if(p_mChoice==2) {
        gameRules();
        p_mChoice = mMenu("Select your choice:");
    }
    //Game loop
    while(p_mChoice==1){
        Game game;
        //Ask if player wants to play again?
        p_mChoice = playAgain();
    }
}

void PlayGame::gameRules(){
    cout<<setw(58)<<"A code will generate a random sequence of colors\n";
    cout<<setw(50)<<"from a set of 8(eight) different colors:\n";
    cout<<setw(59)<<"Red, Orange, Yellow, Green, Blue, Indigo, Violet,\n";
    cout<<setw(20)<<"and White.\n";
    cout<<setw(47)<<"You will then try to guess the colors\n";
    cout<<setw(49)<<"and match them in the correct position.\n";
    cout<<setw(51)<<"The number of colors to match will depend\n";
    cout<<setw(45)<<"on the difficulty of your choosing: "<<endl;
    cout<<setw(38)<<"Easy   - 4 colors\n";
    cout<<setw(38)<<"Medium - 6 colors\n";
    cout<<setw(38)<<"Hard   - 8 colors\n";
    cout<<setw(61)<<"You will get hints of how many colors you correctly\n";
    cout<<setw(60)<<"guessed and how many were in the correct position.\n";
    cout<<setw(60)<<"You will only get 10 tries until the game is over!\n";
    cout<<setw(30)<<"Good luck!\n";
    cout<<endl;
}

int PlayGame::mMenu(string message){
    int mChoice;
    cout<<message<<endl;
    cout<<setw(10)<<"1. Play"<<endl;
    cout<<setw(10)<<"2. Help"<<endl;
    cout<<setw(10)<<"3. Quit"<<endl;
    cin>>mChoice;
    while(mChoice!=1&&mChoice!=2&&mChoice!=3){
        cout<<"ERROR: Input a valid response"<<endl;
        cin.clear();
        cin.ignore(1000,'\n');
        cin>>mChoice;
    }
    return mChoice;
}

int PlayGame::playAgain(){
    int pAgain;
    cout<<"Would you like to play another game?"<<endl;
    cout<<setw(10)<<"1. Play."<<endl;
    cout<<setw(10)<<"2. Quit."<<endl;
    cin>>pAgain;
    while(pAgain!=1&&pAgain!=2){
        cout<<"ERROR: Input a valid response"<<endl;
        cin.clear();
        cin.ignore(1000,'\n');
        cin>>pAgain;
    }
    return pAgain;
}