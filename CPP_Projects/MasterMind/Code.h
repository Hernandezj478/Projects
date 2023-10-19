/*
 * File: Code.h
 * Author: Joseph Hernandez
 * Created on 03/23/22
 * Last Modified 03/31/22
 * Purpose: Code class description
 */


#ifndef CODE_H
#define CODE_H

#include <iostream>
#include <cstring>
using namespace std;

class Code{
    private:
        int* gCode;
        int size;
        int rndDig();
    public:
        Code(int);
        ~Code();
        
        void setCode();
        void setCode(bool);
        void showCode() const;
        
        bool compCode(Code &);
        
        int getSize() const;
        int getCode(int) const;

};

#endif /* CODE_H */

