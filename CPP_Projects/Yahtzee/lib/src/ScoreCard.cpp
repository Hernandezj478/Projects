/*
 * 
 * 
 */
#include <thread>
#include "ScoreCard.hpp"
//Default Constructor
//Set each of the sections with their appropriate names and initialize each
//section
ScoreCard::ScoreCard(){
    //Upper Section Boxes
    upperName[0]=("Aces");
    upperName[1]=("Twos");
    upperName[2]=("Threes");
    upperName[3]=("Fours");
    upperName[4]=("Fives");
    upperName[5]=("Sixes");
    upperName[6]=("Total Score");
    upperName[7]=("Bonus");
    upperName[8]=("Total");
    
    //Lower Section Boxes
    lowerName[0]=("3 Of A Kind");
    lowerName[1]=("4 Of A Kind");
    lowerName[2]=("Full House");
    lowerName[3]=("Sm Straight");
    lowerName[4]=("Lg Straight");
    lowerName[5]=("Yahtzee");
    lowerName[6]=("Chance");
    lowerName[7]=("Yahtzee BONUS");
    lowerName[8]=("Total Lower");
    lowerName[9]=("Total Upper");
    lowerName[10]=("Grand Total");
    
    for(int i=0;i<bSize;i++){
        bit_vector[i]=0;
    }
    int fillUp[upRows];
    int fillLw[lwRows];
    for(int i=0;i<upRows;i++){
        fillUp[i]=-1;
    }
    for(int i=0;i<lwRows;i++){
        fillLw[i]=-1;
    }
    //Initialize Upper Section scores
    for(int i=0;i<numGames;i++){
        for(int j=0;j<upRows;j++){
            upperSec[i][j]=fillUp[j];
        }
    }
    //Initialize Lower Section scores
    for(int i=0;i<numGames;i++){
        for(int j=0;j<lwRows;j++){
            lowerSec[i][j]=fillLw[j];
        }
    }
}

//Save the score card to a file with player name
void ScoreCard::saveCard(string name,string id){
    fstream out;
    out.open("saves/" + name + "_" + id +".sav", ios::out | ios::binary);
    //Save Current Game
    out.seekp(0,ios::beg);
    out.write(reinterpret_cast<char*>(&currGame),sizeof(short));
    long cursor=out.tellg();
    for(int i=0;i<upRows;i++){
        for(int j=0;j<numGames;j++){
            out.seekp(cursor,ios::beg);
            out.write(reinterpret_cast<char*>(&upperSec[j][i]),sizeof(int));
            cursor+=sizeof(int);
        }
    }
    for(int i=0;i<lwRows;i++){
        for(int j=0;j<numGames;j++){
            out.seekp(cursor,ios::beg);
            out.write(reinterpret_cast<char*>(&lowerSec[j][i]),sizeof(int));
            cursor+=sizeof(int);
        }
    }
    
    out.close();
}

//Replace score card with saved card if current game <5
void ScoreCard::replaceCard(string name,string id){
    fstream in;
    in.open("saves/" + name + "_" + id +".sav", ios::in | ios::out | ios::binary);
    string temp;
    short val;
    //Get current game
    in.seekg(0,ios::beg);
    in.read(reinterpret_cast<char*>(&val),sizeof(short));
    currGame=val+1;
    long cursor=in.tellg();
    if(currGame<5){
        for(int i=0;i<upRows;i++){
            for(int j=0;j<numGames;j++){
                in.seekg(cursor,ios::beg);
                in.read(reinterpret_cast<char*>(&upperSec[j][i]),sizeof(int));
                cursor+=sizeof(int);
            }
        }
        cout<<endl;
        for(int i=0;i<lwRows;i++){
            for(int j=0;j<numGames;j++){
                in.seekg(cursor,ios::beg);
                in.read(reinterpret_cast<char*>(&lowerSec[j][i]),sizeof(int));
                cursor+=sizeof(int);
            }
        }
    }
    else currGame=0;
    in.close();
}

void ScoreCard::printScoreCard(){
    string header   ="_______________________________________________________________\n";
    string headTitle="| Upper Section  | Game 1 | Game 2 | Game 3 | Game 4 | Game 5 |\n";
    string spacer   ="|-------------------------------------------------------------|\n";
    string bSepr8r  ="|_____________________________________________________________|\n";
    string lwrSec   ="| Lower Section  |        |        |        |        |        |\n"; 
    
    //Print headers
    cout<<endl;
    cout<<setw(21)<<""<<header;
    cout<<setw(21)<<""<<headTitle;
    cout<<setw(21)<<""<<spacer;
    //Print Upper Section
    for(int i=0;i<upRows;i++){
        if(upperName[i].length()==4)cout<<setw(21)<<""<<"| "
                <<upperName[i]<<setw(12)<<"|";
        else if(upperName[i].length()==6)cout<<setw(21)<<""<<"| "
                <<upperName[i]<<setw(10)<<"|";
        else if(upperName[i].length()==11)cout<<setw(21)<<""<<"| "
                <<upperName[i]<<setw(5)<<"|";
        else cout<<setw(21)<<""<<"| "<<upperName[i]<<setw(11)<<"|";
        
        for(int j=0;j<numGames;j++){
            if(upperSec[j][i]==-1)cout<<setw(4)<<""<<setw(5)<<"|";
            else cout<<setw(4)<<upperSec[j][i]<<setw(5)<<"|";
        }
        cout<<endl;
        if(i>=5 && i<=9)cout<<setw(21)<<""<<spacer;
    }
    cout<<setw(21)<<""<<bSepr8r;
    
    
    //Print Lower Section
    cout<<setw(21)<<""<<lwrSec;
    cout<<setw(21)<<""<<spacer;
    for(int i=0;i<lwRows;i++){
        
        if(lowerName[i].length()==6)cout<<setw(21)<<""
                <<"| "<<lowerName[i]<<setw(10)<<"|";
        else if(lowerName[i].length()==7)cout<<setw(21)<<""
                <<"| "<<lowerName[i]<<setw(9)<<"|";
        else if(lowerName[i].length()==10)cout<<setw(21)<<""
                <<"| "<<lowerName[i]<<setw(6)<<"|";
        else if(lowerName[i].length()==11)cout<<setw(21)<<""
                <<"| "<<lowerName[i]<<setw(5)<<"|";
        else if(lowerName[i].length()==12)cout<<setw(21)<<""
                <<"| "<<lowerName[i]<<setw(4)<<"|";
        else if(lowerName[i].length()==13)cout<<setw(21)<<""
                <<"| "<<lowerName[i]<<setw(3)<<"|";
        else cout<<setw(21)<<""<<"| "<<lowerName[i]<<setw(2)<<"|";
        
        for(int j=0;j<numGames;j++){
            if(lowerSec[j][i]==-1)cout<<setw(4)<<""<<setw(5)<<"|";
            else cout<<setw(4)<<lowerSec[j][i]<<setw(5)<<"|";
        }
        cout<<endl;
        if(i>=7&&i<=9)cout<<setw(21)<<""<<spacer;
    }
    cout<<setw(21)<<""<<bSepr8r;
}

void ScoreCard::printCategories(){
    string category;
    getline(fstream("res/Menu/Categories.txt"),category,'\0');
    cout<<category<<endl;
}

bool ScoreCard::setScoreCell(string scoreSec, Dice dice){
    Face val;
    
    scoreSec=format(scoreSec);
    //Upper Section
    //Count all ones
    if(scoreSec.compare(upperName[0])==0 && bit_vector[0]!=1){
        val=Face::ONE; upperSec[currGame][0]=dice.getDiceVal(val);
        bit_vector[0]=1;
        return true;
    }
    //Count all twos
    else if(scoreSec.compare(upperName[1])==0 && bit_vector[1]!=1){
        val=Face::TWO; upperSec[currGame][1]=dice.getDiceVal(val);
        bit_vector[1]=1;
        return true;
    }
    //Count all Threes
    else if(scoreSec.compare(upperName[2])==0 && bit_vector[2]!=1){
        val=Face::THREE; upperSec[currGame][2]=dice.getDiceVal(val);
        bit_vector[2]=1;
        return true;
    }
    //Count all Fours
    else if(scoreSec.compare(upperName[3])==0 && bit_vector[3]!=1){
        val=Face::FOUR; upperSec[currGame][3]=dice.getDiceVal(val);
        bit_vector[3]=1;
        return true;
    }
    //Count all Fives
    else if(scoreSec.compare(upperName[4])==0 && bit_vector[4]!=1){
        val=Face::FIVE; upperSec[currGame][4]=dice.getDiceVal(val);
        bit_vector[4]=1;
        return true;
    }
    //Count all Sixes
    else if(scoreSec.compare(upperName[5])==0 && bit_vector[5]!=1){
        val=Face::SIX; upperSec[currGame][5]=dice.getDiceVal(val);
        bit_vector[5]=1;
        return true;
    }
    //Lower Section
    //3 of a kind
    else if(scoreSec.compare(lowerName[0])==0 && bit_vector[6]!=1){
        //Check if at least 3 faces are the same
        if(!dice.is3Kind()) lowerSec[currGame][0]=0;
        else{val=Face::ALL; lowerSec[currGame][0]=dice.getDiceVal(val);}
        bit_vector[6]=1;
        return true;
    }
    //4 of a kind
    else if(scoreSec.compare(lowerName[1])==0 && bit_vector[7]!=1){
        //Check if at least 4 faces are the same
        if(!dice.is4Kind()) lowerSec[currGame][1]=0;
        else{val=Face::ALL; lowerSec[currGame][1]=dice.getDiceVal(val);}
        bit_vector[7]=1;
        return true;
    }
    //Full House
    else if(scoreSec.compare(lowerName[2])==0 && bit_vector[8]!=1){
        //Check if 3/2 dice are the same
        if(!dice.isFullHouse()) lowerSec[currGame][2]=0;
        else lowerSec[currGame][2]=25;
        bit_vector[8]=1;
        return true;
    }
    //Small Straight
    else if(scoreSec.compare(lowerName[3])==0 && bit_vector[9]!=1){
        //Check if 4 dice are in ascending order
        if(!dice.isSStraight())lowerSec[currGame][3]=0;
        else lowerSec[currGame][3]=30;
        bit_vector[9]=1;
        return true;
    }
    //Large Straight
    else if(scoreSec.compare(lowerName[4])==0 && bit_vector[10]!=1){
        //Check if 5 dice are in ascending order
        if(!dice.isLStraight()) lowerSec[currGame][4]=0;
        else lowerSec[currGame][4]=40;
        bit_vector[10]=1;
        return true;
    }
    //YAHTZEE
    else if(scoreSec.compare(lowerName[5])==0){
        //Check all 5 die are the same
        if(dice.isYahtzee() && bit_vector[11]!=1){
            lowerSec[currGame][5]=50;
        }
        //Check if YAHTZEE has been filled, if so push onto bonus stack
        else if(dice.isYahtzee() && bit_vector[11]==1){bonus.push_back(100);}
        else {lowerSec[currGame][5]=0;}
        lowerSec[currGame][7]=0;
        bit_vector[11]=1;
        return true;
    }
    //Chance
    else if(scoreSec.compare(lowerName[6])==0 && bit_vector[12]!=1){
        //Add up all the die
        val=Face::ALL; lowerSec[currGame][6]=dice.getDiceVal(val);
        bit_vector[12]=1;
        return true;
    }
    else{
        printScoreCard();
        cout<<setw(21)<<""<<scoreSec<<":"<<endl;
        cout<<setw(21)<<""<<"Section Filled/Not Correct Selection"<<endl;
        cout<<setw(21)<<""<<"Make another selection"<<endl;
        cout<<setw(21)<<""<<"If no option available, "<<endl;
        cout<<setw(21)<<""<<"select an empty cell to earn 0 points."<<endl;
        dice.printDice();
    }
    return false;
}

bool ScoreCard::isCardFull(){
    //Iterate through bit vector to indicate whether each section is filled
    int counter=0;
    for(int i=0;i<bSize;i++){
        //If the current section is filled, mark as true
        if(this->bit_vector[i]==1) counter++;
    }
    if(counter!=bSize)return false;
    return true;
}

int ScoreCard::getScore(){
    //Initialize totals boxes for scoring
    upperSec[currGame][6]=0;
    upperSec[currGame][7]=0;
    upperSec[currGame][8]=0;
    
    lowerSec[currGame][8]=0;
    lowerSec[currGame][9]=0;
    lowerSec[currGame][10]=0;
    
    //Add ace-six score (0-5) rows=9; 9-3=6
    int rows=upRows-3;
    
    for(int i=0;i<rows;i++){//i<6
        for(int j=currGame;j<=currGame;j++){
            upperSec[currGame][6]+=upperSec[j][i];
        }
    }
    //Check if bonus is applicable(score >= 63)
    if(upperSec[currGame][6]>=63) upperSec[currGame][7]=35;
    //Add Upper Score Total
    upperSec[currGame][8]=upperSec[currGame][7]+upperSec[currGame][6];
    
    
    //Add Lower Section Total
    //Add 3kind-chance (0-6) rows=11; 11-4=7
    rows=lwRows-4;
    //Add lower section scores
    for(int i=0;i<rows;i++){//i<7
        for(int j=currGame;j<=currGame;j++){
            lowerSec[currGame][8]+=lowerSec[currGame][i];
        }
    }
    //Count Yahtzee bonus (if any)
    int i=0;
    while(!bonus.empty()){
        lowerSec[currGame][7]+=bonus[i++];
    }
    lowerSec[currGame][8]+=lowerSec[currGame][7];
    //Get Totals
    //Lower Section Total with yahztee bonus
    lowerSec[currGame][9]=upperSec[currGame][8];
    //Upper Section Total
    lowerSec[currGame][10]=lowerSec[currGame][9]+lowerSec[currGame][8];
    
    //Return total score
    return lowerSec[currGame][10];
}

string ScoreCard::format(string word){
    string cellScore=word;
    //Capitalize first character
    bool cap = true;//Indicate whether a letter has been capitalized
    for(int i=0;i<cellScore.length();i++){
        //Check if character is in the alphabet
        // and that we have not capitalized a letter yet.
        if(isalpha(cellScore[i]) && cap==true){
            //set character to upper case (letter - 32)
            cellScore[i] = toupper(word[i]);
            cap=false;
        }else if(isspace(cellScore[i])){
            cap=true;
        }
    }
    if(cellScore=="Ones")cellScore="Aces";
    return cellScore;
}

void ScoreCard::debugCard(){
    for(int i=0;i<bSize;i++){
        cout<<bit_vector[i]<<" ";
    }
    cout<<endl;
}