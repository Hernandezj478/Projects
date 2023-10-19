
/* 
 * File:   Structs.hpp
 * Author: Joseph Hernandez
 *
 * Created on April 11, 2023, 6:35 PM
 */

#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <chrono>
using namespace std::chrono;

struct Time{
    seconds SS;
};
struct RunTime{
    system_clock::time_point start;
    system_clock::time_point stop;
};
struct Session{
    Time time;
    RunTime runTime;
};

struct UserInfo{
    unsigned int uID;
    unsigned int pID;
    unsigned int courseQTY;
    std::string email;
    std::string fname;
    std::string lname;
};

struct ConfInfo{
    char emailDigest[20];
    char passwdDigest[32];
    int priv;
    unsigned int uID;
};

#endif /* STRUCTS_HPP */

