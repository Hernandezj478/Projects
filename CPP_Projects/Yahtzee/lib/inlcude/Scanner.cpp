/* 
 * File:   Scanner.hpp
 * Author: Joseph Hernandez
 *
 * Created on April 10, 2023, 12:36 PM
 */

#include "Scanner.hpp"

char* Scanner::readBuffer(){
    char* buffer=new char[128];
    std::cin.getline(buffer,128);
    
    int length = strlen(buffer)+1;
    
    char* str = new char[length];
    
    for(int i=0;i<length-1;i++){
        str[i]=buffer[i];
    }
    str[length-1]='\0';
    delete[] buffer;
    return str;
}
char* Scanner::nextChar(){
    char* str = readBuffer();
    return str;
}
int Scanner::nextInt(){
    bool isInt = false;
    int val;
    do{
        char* str = readBuffer();
        
        int length=strlen(str);
        try{
            for(int i=0;i<length;i++){
                if(!isdigit(str[i])){
                    throw 21;
                }
            }
            isInt=true;
            val = atoi(str);
            delete[] str;
        }catch(int e){
            //errMessage(e);
            throw std::runtime_error("Expecting Integer value");
        }
    }while(!isInt);
    return val;
}
float Scanner::nextFloat(){
    bool isFloat = false;
    float val;
    do{
        char* str = readBuffer();
        int length=strlen(str);
        try{
            for(int i=0;i<length;i++){
                if(!(isdigit(str[i])|str[i]=='.')){
                    throw 22;
                }
            }
            isFloat=true;
            char* endptr;
            val = strtof(str,&endptr);
            delete[] endptr;
            delete[] str;
        }catch(int e){
            //errMessage(e);
            throw std::runtime_error("Expecting Floating point value");
        }
    }while(!isFloat);
    
    return val;
}
char* Scanner::nextAlphaNum(){
    bool isAlNum = false;
    char* str;
    do{
        str=readBuffer();
        int length = strlen(str);
        try{
            for(int i=0;i<length;i++){
                if(!isalnum(str[i])){
                    throw 23;
                }
            }
            isAlNum=true;
        }catch(int e){
            //errMessage(e);
            throw std::runtime_error("Expecting Alpha-Numeric value");
        }
    }while(!isAlNum);
    return str;
}
char* Scanner::nextAlpha(){
    bool isAlpha=false;
    char* str;
    do{
        str=readBuffer();
        int length=strlen(str);
        try{
            for(int i=0;i<length;i++){
                if(!isalpha(str[i])){
                    throw 24;
                }
            }
            isAlpha=true;
        }catch(int e){
            //errMessage(e);
            throw std::runtime_error("Expecting Alpha characters");
        }
    }while(!isAlpha);
    return str;
}
void Scanner::errMessage(int e){
    switch(e){
        case 21: std::cout<<"ERROR "<<e<<": "<<"Expected Integer Value"<<std::endl;
        case 22: std::cout<<"ERROR "<<e<<": "<<"Expecting Floating point value"<<std::endl;
        case 23: std::cout<<"ERROR "<<e<<": "<<"Expecting Alpha-Numeric value"<<std::endl;
        case 24: std::cout<<"ERROR "<<e<<": "<<"Expecting Alpha characters"<<std::endl;
    }
}