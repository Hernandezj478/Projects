
/* 
 * File:   Scanner.hpp
 * Author: Joseph Hernandez
 *
 * Created on April 10, 2023, 12:36 PM
 */

#ifndef SCANNER_HPP
#define SCANNER_HPP
#include <cstdlib>
#include <cstring>
#include <iostream>

class Scanner{
    public:
        char* nextChar();
        char* nextAlpha();
        char* nextAlphaNum();
        int nextInt();
        float nextFloat();
        
    private:
        char* readBuffer();
        void errMessage(int);
};

#endif /* SCANNER_HPP */

