/*
 * file: Menu.cpp
 * Author: Joseph Hernandez
 * 
 * Create on April 13, 2023, 11:30PM
 */

#include "Menu.hpp"
#include <iostream>

int Menu::size(){
    return options.size();
}
void Menu::editTitle(std::string input){
    title=input;
}
void Menu::addOption(std::string option){
    options.push_back(option);
}
void Menu::removeOption(int option){
    options.erase(options.begin()+option);
}
const char* Menu::operator[](int index){
    return options[index].c_str();
}