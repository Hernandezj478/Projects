/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   AdminPlayer.hpp
 * Author: aawri
 * Edited by: Joseph Hernandez
 * 
 * 
 * Created on April 27, 2023, 1:18 AM
 * Edited  on April 27, 2023, 12:49PM
 */

#ifndef ADMINPLAYER_HPP
#define ADMINPLAYER_HPP
#include <map>
#include <string>
#include <iostream>
#include <fstream>

#include "Menu.hpp"
#include "Enums.hpp"

using namespace std;

class AdminPlayer {
public:
    AdminPlayer();
    
    void adminSession(Menu&);
    
    
private:
    //Structs to help hold temporary info
    struct LoginInfo{
        char nameDigest[20];
        char passwdDigest[32];
        Privilege priv;
        unsigned int id;
    };
    
    struct UserInfo{
        unsigned id;
        int size;
        char* name;
    };

    std::map<unsigned int, std::string> users;
    
    
    void readDataIntoMap();
    void showUsers();
    void removeUser();
};

#endif /* ADMINPLAYER_HPP */

