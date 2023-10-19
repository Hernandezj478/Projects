/* 
 * File:   AdminUser.hpp
 * Author: Joseph Hernandez
 *
 * Created on April 22, 2023, 8:43 PM
 */

#ifndef ADMINUSER_HPP
#define ADMINUSER_HPP

#include <map>
#include <string>
#include <stdio.h>

#include "StandardUser.hpp"
#include "User.hpp"
#include "Menu.hpp"

class AdminUser : public User{
    public:
        AdminUser();
        //Admin needs to be able to view all current users, add/remove users,
        //edit user information, edit user course total time
        void AdminSession();
    private:
        Menu menu;
        std::map<unsigned int,UserInfo> userList;
        
        void editUser();
        bool userIDCheck(unsigned int);
        
        void getUsers();
        bool defaultPasswd();
        void changePasswd();
        void initMenu();
        void initMenu(Menu&);
        void displayMenu(Menu);
        void displayMenu();
        void viewUsers();
        void removeUser();
};

#endif /* ADMIN_HPP */

