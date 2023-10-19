/*
 * File: TimeTracker.cpp
 * Author: Joseph Hernandez
 * 
 * Created on April 14, 2023, 12:04PM
 * 
 */

#include "TimeTracker.hpp"
void TimeTracker::punchIn(){
    seconds s(0);
    session.time.SS = s;
    session.runTime.start=system_clock::now();
}
void TimeTracker::punchOut(){
    session.runTime.stop=system_clock::now();
    //Calculate session duration
    session.time.SS = duration_cast<seconds>(session.runTime.stop-session.runTime.start);
}
void TimeTracker::setSessionTime(seconds s){
    session.time.SS = s;
}
void TimeTracker::setSessionStart(std::fstream& file){
    long cursor=file.tellg();
    file.read(reinterpret_cast<char*>(&session.runTime.start),
            sizeof(system_clock::time_point));//64-bit size
    file.seekg(cursor,std::ios::beg);
}
seconds TimeTracker::getTimeSec(){
    return session.time.SS;
}

