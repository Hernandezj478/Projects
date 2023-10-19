/*
 * File: Menu.cpp
 * Author: Joseph Hernandez
 * Created on November 4, 2022, 10:48 PM
 * 
 */

#include "Menu.hpp"

Menu::Menu(){
    string mainMenu, rules, login, adminMenu, ending;
    getline(fstream("res/Menu/MainMenu.txt"),mainMenu,'\0');
    menuSys[0]=mainMenu;
    getline(fstream("res/Menu/Rules.txt"),rules,'\0');
    menuSys[1]=rules;
    getline(fstream("res/Menu/LoginMenu.txt"),login,'\0');
    menuSys[2]=login;
    getline(fstream("res/Menu/AdminMenu.txt"),adminMenu,'\0');
    menuSys[3]=adminMenu;
    getline(fstream("res/Menu/End.txt"),ending,'\0');
    menuSys[4]=ending;
}

void Menu::printMainMenu(){
    cout<<menuSys[0]<<endl;
}

void Menu::printRules(){
    cout<<menuSys[1]<<endl;
}

void Menu::printLogin(){
    cout<<menuSys[2]<<endl;
}

void Menu::printAdminMenu(){
    cout<<menuSys[3]<<endl;
}

void Menu::printExit(){
    cout<<endl<<endl<<menuSys[4]<<endl;
}