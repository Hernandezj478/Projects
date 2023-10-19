/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   TimeTracker.hpp
 * Author: Joseph Hernandez
 *
 * Created on April 11, 2023, 6:34 PM
 */

#ifndef TIMETRACKER_HPP
#define TIMETRACKER_HPP
#include <fstream>

#include "Structs.hpp"

using namespace std::chrono;
class TimeTracker{
    public:
        void punchIn();
        void punchOut();
        seconds getTimeSec();
        void setSessionTime(seconds);
        void logSession(std::fstream&,unsigned int);
        void setSessionStart(std::fstream&);
        system_clock::time_point getSessionStart(){return session.runTime.start;}
        system_clock::time_point getSessionEnd(){return session.runTime.stop;}
    private:
        Session session;
};

#endif /* TIMETRACKER_HPP */

