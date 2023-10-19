/* 
 * File:   main.cpp
 * Author: Joseph Hernandez
 *
 * Created on December 13, 2022, 12:08 PM
 */

#include <iostream>
#include <string>

using namespace std;

//Hash function that will take any length string
int myHash(const string &);

int main(int argc, char** argv) {
    int value=myHash("JCH");
    cout<<value<<endl;
    return 0;
}

int myHash(const string &str){
    
    //Key Pad Hash
    string value;
    
    for(int i=0;i<str.length();i++){
        if((str[i]>='a' && str[i]<='c') ||
           (str[i]>='A' && str[i]<='C')){
            value+=to_string(2);
        }
        else if((str[i]>='d' && str[i]<='f')||
                (str[i]>='D' && str[i]<='F')){
            value+=to_string(3);
        }
        else if((str[i]>='g' && str[i]<='i')||
                (str[i]>='G' && str[i]<='I')){
            value+=to_string(4);
        }
        else if((str[i]>='j' && str[i]<='l')||
                (str[i]>='J' && str[i]<='L')){
            value+=to_string(5);
        }
        else if((str[i]>='m' && str[i]<='o')||
                (str[i]>='M' && str[i]<='N')){
            value+=to_string(6);
        }
        else if((str[i]>='p' && str[i]<='s')||
                (str[i]>='P' && str[i]<='S')){
            value+=to_string(7);
        }
        else if((str[i]>='t' && str[i]<='v')||
                (str[i]>='T' && str[i]<='V')){
            value+=to_string(8);
        }
        else if((str[i]>='w' && str[i]<='z')||
                (str[i]>='W' && str[i]<='Z')){
            value+=to_string(9);
        }
    }
    return stoi(value);
}