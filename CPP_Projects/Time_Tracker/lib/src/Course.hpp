/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Course.hpp
 * Author: Joseph Hernandez
 *
 * Created on April 15, 2023, 2:10 PM
 */

#ifndef COURSE_HPP
#define COURSE_HPP

#include <fstream>
#include <iostream>
#include <thread>

#include "TimeTracker.hpp"
#include "Menu.hpp"

using namespace std::chrono;

class Course{
    public:
        Course();
 
        void courseSession(std::fstream&);
        void regCourse(std::fstream&,unsigned int);
        bool punchIn(std::fstream&);
        bool punchOut(std::fstream&);
        void printTime(std::fstream&);
        void displayMenu();
        void logSessionTime(std::fstream& file);
        bool findCourse(std::fstream&,unsigned int);
        void read(std::fstream&);
        void write(std::fstream&);
        
        void editTotalTime(std::fstream&,seconds);

        Menu menu;
        
    private:
        Time totalTime;
        TimeTracker session;
        
        bool clockIn;
        unsigned int courseNo;
        
        void initMenu();
        void calcTime(std::fstream&);
        bool punchCheck(std::fstream&);
};


#endif /* COURSE_HPP */

