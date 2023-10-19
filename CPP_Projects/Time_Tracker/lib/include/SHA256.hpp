/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   SHA256.hpp
 * Author: Joseph Hernandez
 *
 * Created on April 9, 2023, 6:52 PM
 */

#ifndef SHA256_HPP
#define SHA256_HPP
#include<cstring>

typedef unsigned long long  uint64;
typedef unsigned int        uint32;
typedef unsigned short      uint16;
typedef unsigned char       uint8;



class SHA256{
    public:
        SHA256();
        SHA256(char*);
        ~SHA256();
        void update(char*);
        uint8* getDigest();
        char* hexDigest();
    private:
        const uint16 MSG_BLOCK = 512;        //Size of message blocks to parse
        const uint16 DIGEST_SIZE = 64;      // 64*8 = 256-bits
        const uint8 BITS64 = 64;
        const uint8 BITS32 = 32;
        const uint8 BITS16 = 16;
        const uint8 BITS8  = 8;
        
        //Member variables
        uint8* digest;
        uint8* message;
        uint32* M;

        //Private member functions
        void init();
        uint8* pad(char*,const uint64&,const uint32&);
        uint32* parse(const uint16&);
        void compute(const uint16&);
        
        uint32 SHR(uint16,uint32);
        uint32 ROTR(uint16,uint32);
        uint32 Ch(uint32, uint32,uint32);
        uint32 Maj(uint32,uint32,uint32);
        uint32 SIG0(uint32);
        uint32 SIG1(uint32);
        uint32 sig0(uint32);
        uint32 sig1(uint32);

        char getHex(uint8);
};

#endif /* SHA256_HPP */

