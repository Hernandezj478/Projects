/* 
 * File:   StandardUser.hpp
 * Author: Joseph Hernandez
 *
 * Created on April 16, 2023, 12:17 PM
 */

#ifndef STANDARDUSER_HPP
#define STANDARDUSER_HPP

#include <iomanip>
#include <map>
#include <string>
#include <cstring>


#include "Menu.hpp"
#include "User.hpp"
#include "Course.hpp"

class StandardUser : public User{
    public:
        StandardUser();
        virtual ~StandardUser();
        void menuInit();
        void standardSession(unsigned int);
        bool newStandard();
        
        const StandardUser& operator=(const UserInfo&);
        
        friend class AdminUser;
    private:
        char* fname;
        char* lname;
        unsigned int pID;
        unsigned int courseQTY;

        
        Menu menu;
        std::map<unsigned int,std::string> courseNames;
        
        void fillUserData(unsigned int);
        
        void regCourse(std::fstream&);
        bool courseCheck(unsigned int);
        void selectCourse();
        void displayMenu();
        void viewCourses();
        void editCourseTime();
        
        void write(std::fstream&);
        void read(std::fstream&);
};

#endif /* STANDARD_HPP */

