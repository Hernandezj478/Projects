/* 
 * File:   Menu.h
 * Author: Joseph Hernandez
 *
 * Created on November 4, 2022, 10:46 PM
 */

#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

class Menu{
    public:
        Menu();
        void printMainMenu();
        void printLogin();
        void printAdminMenu();
        void printRules();
        void printExit();
    private:
        static const int NUM=5;
        string menuSys[NUM];
};

#endif /* MENU_H */

