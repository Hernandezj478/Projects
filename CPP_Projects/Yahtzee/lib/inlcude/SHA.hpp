/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   SHA.hpp
 * Author: Joseph Hernandez
 *
 * Created on April 12, 2023, 12:51 PM
 */

#ifndef SHA_HPP
#define SHA_HPP

#ifndef uint8
typedef unsigned char uint8;
#endif
#ifndef uint16
typedef unsigned short uint16;
#endif
#ifndef uint32
typedef unsigned int uint32;
#endif
#ifndef uint64
typedef unsigned long long uint64;
#endif
#ifndef BITS8
static const uint8 BITS8 = 8;
#endif
#ifndef BITS16
static const uint8 BITS16 = 16;
#endif
#ifndef BITS32
static const uint8 BITS32 = 32;
#endif
#ifndef BITS62
static const uint8 BITS64 = 64;
#endif

#include "SHA1.hpp"
#include "SHA256.hpp"

#endif /* SHA_HPP */

