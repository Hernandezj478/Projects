/* 
 * File:   Application.hpp
 * Author: Joseph Hernandez
 *
 * Created on April 22, 2023, 12:16 PM
 */

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <fstream>
#include <thread>
#include <iostream>

#include "StandardUser.hpp"
#include "AdminUser.hpp"
#include "Menu.hpp"


class Application{
    public:
        Application();
        void run();
    private:
        Menu menu;
        
        void initMenu();
        void displayMenu();
        void checkFile();
        void createFile();
        void read();

        void logIn();
        bool createUser();

        bool foundEmail(std::fstream&,char*);
        bool passwdValid(std::fstream&,char*);
        Priv readPriv(std::fstream&);
        unsigned int readID(std::fstream&);
};

#endif /* APPLICATION_HPP */

