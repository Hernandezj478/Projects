/*
 * File: Code.cpp
 * Author: Joseph Hernandez
 * Created on 03/23/22
 * Last Modified 03/31/22
 * Purpose: Implementation of Code class
 */

#include "Code.h"

Code::Code(int size){
    this->size=size;
    gCode = new int[size];
    gCode = nullptr;
}

Code::~Code(){
    delete gCode;
}

void Code::setCode(){//User defined colors
    enum{RED,ORANGE,YELLOW,GREEN,BLUE,INDIGO,VIOLET,WHITE};
    
    string p_guess;                 //Player guess
    int* code = new int[size];      //Create a color array
    gCode = code;
    
    cout<<"\nYour choices are:\nR, O, Y, G, B, I, V, or W"<<endl;
    cout<<"Enter your guess: ";
    cin>>p_guess;
    while(p_guess.length()>size){
        cout<<"ERROR: Too many input values..."<<endl;
        cout<<"Input size is "<<size<<endl;
        cin.clear();
        cin.ignore(1000,'\n');
        cin>>p_guess;
    }
    
    for(int i =0;i<size;i++){
        p_guess[i]=toupper(p_guess[i]);//Change to upper case char for compare
        
        //Validate user input, do not allow for anything other than char input
        while(p_guess[i]!='R'&&p_guess[i]!='O'&&p_guess[i]!='Y'&&p_guess[i]!='G'&&
                p_guess[i]!='B'&&p_guess[i]!='I'&&p_guess[i]!='V'&&p_guess[i]!='W'){
            cout<<"ERROR: "<<p_guess[i]<<" is not a valid color choice!"<<endl;
            cout<<"Enter valid color: ";
            cin.clear();
            cin.ignore();
            cin>>p_guess[i];
            p_guess[i]=toupper(p_guess[i]);
        }
        //Assign the color selected to appropriate enum color(0-7)
        switch(p_guess[i]){
            case 'R': this->gCode[i]=RED;break;
            case 'O': this->gCode[i]=ORANGE;break;
            case 'Y': this->gCode[i]=YELLOW;break;
            case 'G': this->gCode[i]=GREEN;break;
            case 'B': this->gCode[i]=BLUE;break;
            case 'I': this->gCode[i]=INDIGO;break;
            case 'V': this->gCode[i]=VIOLET;break;
            case 'W': this->gCode[i]=WHITE;break;
        }
    }
}

void Code::setCode(bool dup){//Create random colors w or w/o duplicate colors
    int temp, rand1,rand2;
    int* code = new int[size];
    gCode = code;
    //Allow duplicates
    if(dup==true){
        for(int i=0;i<size;i++){
            gCode[i]=rndDig();
        }
    }
    //Do not allow duplicates
    else if(dup==false){
        const int LEN = 8;
        int SHUFFLE = 10;
        int tmpCode[LEN];
        for(int i=0;i<LEN;i++){
            tmpCode[i]=i;
        }
        //Shuffle to get random order
        for(int i=0;i<SHUFFLE;i++){
            rand1=rndDig();
            rand2=rndDig();
            while(rand1==rand2){
                rand2=rndDig();
            }
            temp = tmpCode[rand1];
            tmpCode[rand1]=tmpCode[rand2];
            tmpCode[rand2]=temp;
        }
        //Assign shuffled colors to code(w/ length of lvl of difficulty)
        for(int i=0;i<size;i++){
            gCode[i]=tmpCode[i];
        }
    }
}

void Code::showCode() const{
    cout<<"\nThe code was: "<<endl;
        for(int i=0;i<size;i++){
            switch(gCode[i]){
                case 0: cout<<"R";break;    //Red
                case 1: cout<<"O";break;    //Orange
                case 2: cout<<"Y";break;    //Yellow
                case 3: cout<<"G";break;    //Green
                case 4: cout<<"B";break;    //Blue
                case 5: cout<<"I";break;    //Indigo
                case 6: cout<<"V";break;    //Violet
                case 7: cout<<"W";break;    //White
            }
        }
    cout<<endl;
}

bool Code::compCode(Code &other){
    bool gameWin = false;
    const int COLORSIZE = 8;
    int colArray[] = {0,0,0,0,0,0,0,0};  //Hold correct colors(random gen code)
    int pColArray[] = {0,0,0,0,0,0,0,0}; //Hold player colors
    int match[] = {0,0};//match[0] = number of match, match[1] is correct pos
    //Count how many occurrences of each color in the random gen code
    for(int i=0;i<this->size;i++){
        switch(this->gCode[i]){
            case 0: colArray[0]++;break;    //Red
            case 1: colArray[1]++;break;    //Orange
            case 2: colArray[2]++;break;    //Yellow
            case 3: colArray[3]++;break;    //Green
            case 4: colArray[4]++;break;    //Blue
            case 5: colArray[5]++;break;    //Indigo
            case 6: colArray[6]++;break;    //Violet
            case 7: colArray[7]++;break;    //White
        }
    }
    //Count how many occurrences of each color in player code
    for(int i=0;i<other.getSize();i++){
        switch(other.getCode(i)){
            case 0: pColArray[0]++;break;   //Red
            case 1: pColArray[1]++;break;   //Orange
            case 2: pColArray[2]++;break;   //Yellow
            case 3: pColArray[3]++;break;   //Green
            case 4: pColArray[4]++;break;   //Blue
            case 5: pColArray[5]++;break;   //Indigo
            case 6: pColArray[6]++;break;   //Violet
            case 7: pColArray[7]++;break;   //White
        }
    }
    //Count how many colors (player code) match (random gen code)
    for(int i=0;i<COLORSIZE;i++){
        if(colArray[i]<=pColArray[i]){
            match[0]+=colArray[i];
        }
        else if(colArray[i]>pColArray[i]){
            match[0]+=pColArray[i];
        }
    }
    //Count how many colors (player code) in correct position (random gen code)
    for(int i=0;i<size;i++){
        if(this->gCode[i]==other.getCode(i)){
            match[1]++;
        }
    }
    //Win if total match = size of color array (random gen code)
    if(match[1]==size) {
        gameWin=true;
    }
    //Output how many are in the correct position and how many correct in total
    else{
        cout<<"Correct Position: "<<match[1]<<endl;
        cout<<"Wrong Position:   "
                <<match[0]-match[1]<<endl;
    }
    return gameWin;
}

int Code::getSize() const{
    return size;
}

int Code::getCode(int i) const{
    return gCode[i];
}

int Code::rndDig(){
    return rand()%8;
}