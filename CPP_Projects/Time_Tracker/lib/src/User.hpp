/* 
 * File:   User.hpp
 * Author: Joseph Hernandez
 *
 * Created on April 11, 2023, 6:34 PM
 */

#ifndef USER_HPP
#define USER_HPP

#include <fstream>
#include <cstring>

#include "Enums.hpp"
#include "Scanner.hpp"
#include "SHA.hpp"

class User{
    public:
        User();
        virtual ~User();
        bool passwdFormat(char*);
        bool newUser();
    private:
        void setUID(std::fstream&);
        void writeUser(std::fstream&,char*);
        bool findEmail(std::fstream&);
        bool emailFormat(char*);
        
    protected:
        Priv priv;                      //Privilege level
        unsigned int uID;            //Save to passwd.bin

        char* email;                    //Save hash to passwd.bin
};

#endif /* USER_HPP */

