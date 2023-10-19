/*
 * File: Game.cpp
 * Author: Joseph Hernandez
 * Created on 03/26/22
 * Last Modified 03/31/22
 * Purpose: Implementation of Game class
 */

#include "Game.h"
#include "Code.h"

Game::Game(){
    win = false;
    tries = 10;
    bool debugCode = false;
    bool firstTry = true;
    size = difficulty(debugCode);
    Code r_gCode(size);   //Random generated code
    Code p_gCode(size);   //Player generated code
    
    //Allow for duplicate code generation
    bool dup = duplicate();

    //Generate code
    r_gCode.setCode(dup);
    
    //Debug///////////////////
    if(debugCode==true)     //
        r_gCode.showCode(); //
    //////////////////////////
    
    //Get guess from player
    p_gCode.setCode();
    
    //Search array for matching pegs and
    //count how many correct/correct position
    do{
        win=r_gCode.compCode(p_gCode);
        if(win==false){
            //Display some banter to player
            banterMessage();
            firstTry = false;
            //--tries;  //Take out comment for number of tries
            //Display the number of tries remaining
            //if(tries>1) cout<<"Number of tries remaining: "<<tries<<endl;
            //else if(tries==1) cout<<"Last try!!"<<endl;
            
            //Get a new code from player
            p_gCode.setCode();
        }
    }while(win==false/*&&tries>1*/);    //Remove comment for loop w/ tries
    if(firstTry==true) specialWinMessage();
    else if(win==true&&firstTry==false/*&&tries<10&&tries>0*/)winMessage();
    //If player looses, display code
    //if(win==false){r_gCode.showCode();}   // Remove comment to show code
}

int Game::difficulty(bool& debugCode){
    int difficulty;
    cout<<"Choose a difficulty:"<<endl;
    cout<<setw(10)<<"1. Easy"<<endl;
    cout<<setw(12)<<"2. Medium"<<endl;
    cout<<setw(10)<<"3. Hard"<<endl;
    
    cin>>difficulty;
    if(difficulty==6969){
        debugCode = true;
        cout<<"Debug Mode Active"<<endl;
        cin>>difficulty;
    }
    while(difficulty!=1&&difficulty!=2&&difficulty!=3&&difficulty!=6969){
        cout<<"ERROR: Select valid a response..."<<endl;
        cin.clear();
        cin.ignore(1000,'\n');
        cin>>difficulty;
    }
    
    switch(difficulty){
        case 1: difficulty = 4;break;
        case 2: difficulty = 6;break;
        case 3: difficulty = 8;break;
    }
    return difficulty;
}

bool Game::duplicate(){
    bool dup = true;
    int ans;
    cout<<"Allow duplicate code to generate?"<<endl;
    cout<<setw(9)<<"1. Yes"<<endl;
    cout<<setw(8)<<"2. No"<<endl;
    cin>>ans;
    
    while(ans!=1&&ans!=2){
        cout<<"ERROR: Select a valid response..."<<endl;
        cin.clear();
        cin.ignore(1000,'\n');
        cin>>ans;
    }
    if(ans==2) dup = false;
    
    return dup;
}

void Game::winMessage(){
    int rndMessage = rand()%4;
    switch(rndMessage){
        case 0: cout<<"WINNER-WINNER!! Chicken Dinner!!"<<endl;break;
        case 1: cout<<"CONGRATULATIONS!! You won!"<<endl;break;
        case 2: cout<<"OH WOW!! You actually won!"<<endl;break;
        case 3: cout<<"NICE JOB!! You win!"<<endl;break;
    }
    
}

void Game::specialWinMessage(){
    cout<<"WOW! You must be a GENIUS! "
            <<"You cracked the code in the first try!"<<endl;
}

void Game::banterMessage(){
    int rndMessage = rand()%5;
    switch(rndMessage){
        case 0: cout<<"You're not going to win this one!"<<endl;break;
        case 1: cout<<"You think you can beat me?"<<endl;break;
        case 2: cout<<"AWHHHHH I am a GENIUS!"<<endl;break;
        case 3: cout<<"Just give up already!"<<endl;break;
        default: break;
    }
}