/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   SHA1.hpp
 * Author: Joseph Hernandez
 *
 * Created on April 10, 2023, 1:21 PM
 */

#ifndef SHA1_HPP
#define SHA1_HPP

#include <cstring>
#include <iostream>

typedef unsigned long long  uint64;
typedef unsigned int        uint32;
typedef unsigned short      uint16;
typedef unsigned char       uint8;

class SHA1{
    public:
        SHA1();
        SHA1(char*);
        ~SHA1();
        void update(char*);
        uint8* getDigest();
        char*  hexDigest();
    private:
        static const uint16 MSG_BLOCK = 512;
        static const uint16 MSG_SCHED = 80;
        static const uint8 DIGEST_SIZE = 20;
        static const uint8 BITS64 = 64;
        static const uint8 BITS32 = 32;
        static const uint8 BITS16 = 16;
        static const uint8 BITS8  = 8;
        
        uint8* digest;
        uint8* message;
        uint32* M;
        
        void init();
        
        uint8* pad(char*,const uint64&,const uint32&);
        uint32* parse(const uint16&);
        void compute(const uint16&);
        
        
        
        uint32 Ch(uint32,uint32,uint32);
        uint32 Parity(uint32,uint32,uint32);
        uint32 Maj(uint32,uint32,uint32);
        
        uint32 ROTL(uint16,uint32);
        
        uint32 ft(int,uint32,uint32,uint32);
        uint32 kt(int,uint32[]);
        
        char getHex(uint8);
};

#endif /* SHA1_HPP */

