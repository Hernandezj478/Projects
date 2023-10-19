/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include "Dice.hpp"

Dice::Dice(){
    size=0;
    string one,two,three,four,five,six;
    
    getline(fstream("res/Faces/One.txt"),one,'\0');
    getline(fstream("res/Faces/Two.txt"),two,'\0');
    getline(fstream("res/Faces/Three.txt"),three,'\0');
    getline(fstream("res/Faces/Four.txt"),four,'\0');
    getline(fstream("res/Faces/Five.txt"),five,'\0');
    getline(fstream("res/Faces/Six.txt"),six,'\0');
    
    picDie[Face::ONE]=one;
    picDie[Face::TWO]=two;
    picDie[Face::THREE]=three;
    picDie[Face::FOUR]=four;
    picDie[Face::FIVE]=five;
    picDie[Face::SIX]=six;
}

Dice::Dice(int s){
    size=s;
    string one,two,three,four,five,six;
    
    getline(fstream("res/Faces/One.txt"),one,'\0');
    getline(fstream("res/Faces/Two.txt"),two,'\0');
    getline(fstream("res/Faces/Three.txt"),three,'\0');
    getline(fstream("res/Faces/Four.txt"),four,'\0');
    getline(fstream("res/Faces/Five.txt"),five,'\0');
    getline(fstream("res/Faces/Six.txt"),six,'\0');
    
    picDie[Face::ONE]=one;
    picDie[Face::TWO]=two;
    picDie[Face::THREE]=three;
    picDie[Face::FOUR]=four;
    picDie[Face::FIVE]=five;
    picDie[Face::SIX]=six;
}

void Dice::setSize(int s){
    size=s;
}

void Dice::printDice(){    
    int counter=1;
    cout<<endl;
    for(int i=0;i<size;i++){
        cout<<"  Dice "<<counter++<<endl;
        cout<<picDie[dice[i]]<<endl;
    }
}

void Dice::rollDice(int *keep,int length){
    //Compare the dice kept to the dice array
    int count=0;
    Face val;
    for(int i=0;(i<size);i++){
        count%=length;//Always give 0-(n-1) where n is the length given
        if(i!=keep[count++]){
            int rnd = rand()%6;
            val=static_cast<Face>(rnd);
            dice[i]=val;
            count--;
        }
    }
    sort();
}

void Dice::rollDice(){
    dice.clear();
    Face val;
    int rnd;
    for(int i=0;i<size;i++){
        rnd=rand()%6;
        val=static_cast<Face>(rnd);
        dice.push_back(val);
    }
    sort();
}

int Dice::getDiceVal(Face val){
    int score=0;
    switch(val){
        //Add all the ones in dice
        case Face::ONE:{
            for(int i=0;i<size;i++){
                if(dice[i]==Face::ONE){
                    score+=1;
                }
            }
            break; 
        }
        //Add all the twos in dice
        case Face::TWO:{
            for(int i=0;i<size;i++){
                if(dice[i]==Face::TWO){
                    score+=2;
                }
            }
            break;
        }
        //Add all the threes in dice
        case Face::THREE:{
            for(int i=0;i<size;i++){
                if(dice[i]==Face::THREE){
                    score+=3;
                }
            }
            break;
        }
        //Add all the fours in dice
        case Face::FOUR:{
            for(int i=0;i<size;i++){
                if(dice[i]==Face::FOUR){
                    score+=4;
                }
            }
            break;
        }
        //Add all the fives in dice
        case Face::FIVE:{
            for(int i=0;i<size;i++){
                if(dice[i]==Face::FIVE){
                    score+=5;
                }
            }
            break;
        } 
        case Face::SIX:{
            for(int i=0;i<size;i++){
                if(dice[i]==Face::SIX){
                    score+=6;
                }
            }
            break;
        }
        //Add all dice
        case Face::ALL: {
            for(int i=0;i<size;i++){
                //Count ones
                if(dice[i]==Face::ONE)         score+=1;
                else if(dice[i]==Face::TWO)    score+=2;
                else if(dice[i]==Face::THREE)  score+=3;
                else if(dice[i]==Face::FOUR)   score+=4;
                else if(dice[i]==Face::FIVE)   score+=5;
                else if(dice[i]==Face::SIX)    score+=6;
            }
            break;//add all dice
        }
    }
    return score;
}

bool Dice::is3Kind(){
    //At least 3 are the same face
    Face face=dice[0];                     //Set first die as face to match
                                           //Move to next die
    int count=1;                           //Count 1 die for the face
    for(int i=1;i<size;i++){
        if(dice[i]==face) {                //curr die = face
            count++;                       //increment number of match
            if(count>=3)return true;
        }
        else{
            face=dice[i]; count=1;         //Set curr die as face to match
        }  
    }
    if(count<3) return false;              //If the count < 3 then no 3 kind
    return true;
}

bool Dice::is4Kind(){
    Face face=dice[0];                  //Set first die as face to match
                                        //Move to next die
    int count=1;                        //Count 1 die for face
    for(int i=1;i<size;i++){
        if(dice[i]==face){             //curr die = face -> increment number of match
            count++;
            if(count>=4)return true;
        }      
        else{ face=dice[i]; count=1;}  //Set curr die as face to match
    }
    if(count<4) return false;       //If count < 4 then no 4 kind
    return true;
}

bool Dice::isFullHouse(){
    //Full House
    //3 of one die 2 of another
    Face fFace = dice[0];
    Face sFace;
    int i=1;
    int frst=1;
    int scnd=1;
    for(i;i<size;i++){
        if(dice[i]==fFace){
            frst++;
        }
        else{
            sFace=dice[i];
            i++;
            break;
        }
    }
    
    for(i;i<size;i++){
        if(dice[i]==sFace){
            scnd++;
        }
    }
    
    if(frst==2 && scnd==3 || frst==3 && scnd==2) return true;
    
    return false;
}

bool Dice::isSStraight(){
    //Small Straight
    //4 Consecutive face values
    //Find starting face value
    Face val = dice[0];
    //Iterate to the next die
    //So we can increment through the enum face class
    int temp=(int)val;
    //Number of consecutive face values
    int consec=1;
    for(int i=1;i<size;i++){
        if((Face)(temp+1)==dice[i]){
            consec++;
            temp++;
            val=(Face)temp;
            if(consec==4)return true;
        }
        else if((Face)temp!=dice[i]){
            val=dice[i];
            temp=(int)val;
            consec=1;
        }
    }
    if(consec<4)return false;
    
    return true;
}

bool Dice::isLStraight(){
    //large Straight
    //5 Consecutive face values
    //Find starting face value
    Face val = dice[0];
    //Iterate to the next die
    //So we can increment through the enum face class
    int temp=(int)val;
    //Number of consecutive face values
    for(int i=1;i<size;i++){
        if((Face)(temp+1)==dice[i]){
            temp++;
            val=(Face)temp;
        }
        else{
            return false;
        }
    }
    return true;
}

bool Dice::isYahtzee(){
    //All 5 die the same
    Face face=dice[0];
    for(int i=0;i<size;i++){
        if(dice[i]!=face)return false;
    }
    return true;
}

void Dice::merge(int *array, int beg, int mid, int end){
    const int array1 = mid - beg + 1;
    const int array2 = end - mid;
 
    int *lArray = new int[array1];
    int *rArray = new int[array2];

    for (int i = 0; i < array1; i++)
        lArray[i] = array[beg + i];
    for (int j = 0; j < array2; j++)
        rArray[j] = array[mid + 1 + j];
 
    int indxA1 = 0;
    int indxA2 = 0;
    int indx   = beg;

    while (indxA1 < array1 && indxA2 < array2) {
        if (lArray[indxA1] <= rArray[indxA2]) {
            array[indx] = lArray[indxA1];
            indxA1++;
        }
        else {
            array[indx] = rArray[indxA2];
            indxA2++;
        }
        indx++;
    }
    
    while (indxA1 < array1) {
        array[indx] = lArray[indxA1];
        indxA1++;
        indx++;
    }
    while (indxA2 < array2) {
        array[indx] = rArray[indxA2];
        indxA2++;
        indx++;
    }
    delete[] lArray;
    delete[] rArray;
}

void Dice::mergeSort(int *array,int beg,int end){
    if(beg>=end)return;
    int mid = beg + (end - beg)/2;
    mergeSort(array,beg,mid);
    mergeSort(array,mid+1,end);
    merge(array,beg,mid,end);
}

void Dice::sort(){
    std::sort(&dice[0],&dice[size]);
}

void Dice::sort(int *array,int len){
    mergeSort(array,0,len);
}

void Dice::arrayToVec(int* array){
    for(int i=0;i<size;i++){
        cout<<"array["<<i<<"]="<<array[i]<<endl;
        dice[i]=(Face)array[i];
    }
}

int* Dice::vecToArray(){
    int* array=new int[size];
    for(int i=0;i<size;i++){
        cout<<"dice["<<i<<"]="<<(int)dice[i]<<endl;
        array[i]=(int)dice[i];
    }
    return array;
}


void Dice::debugDice(){
    dice.clear();
    int val;
    Face face;
    cout<<"Dice Debug:"<<endl;
    cout<<"Enter Desired Dice:";
    for(int i=0;i<size;i++){
        cin>>val;
        face=(Face)(val-1);
        dice.push_back(face);
    }
    printDice();
}