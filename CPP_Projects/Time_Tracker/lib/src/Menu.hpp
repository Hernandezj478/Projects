/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Menu.hpp
 * Author: Joseph Hernandez
 *
 * Created on April 11, 2023, 6:34 PM
 */

#ifndef MENU_HPP
#define MENU_HPP
#include <vector>
#include <string>

class Menu{
    public:
        int size();
        
        const char* getTitle(){return title.c_str();}
        void editTitle(std::string);
        void addOption(std::string);
        void removeOption(int);
        const char* operator[](int);
    private:
        std::string title;
        std::vector<std::string> options;
};

#endif /* MENU_HPP */

