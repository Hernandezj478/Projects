/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include "SHA256.hpp"

SHA256::SHA256(){
    init();
}

SHA256::SHA256(char* buffer){
    init();
    uint64 l = strlen(buffer)*BITS8;
    uint16 n = l / MSG_BLOCK;
    uint32 m_size = BITS64 * (n+1);
    
    message=pad(buffer,l,m_size);
    
    M=parse(n);
    
    compute(n);
    //Digest will now have hashed value
}
SHA256::~SHA256(){
    delete[] digest;
    delete[] message;
    delete[] M;
}
void SHA256::init(){
    digest = new uint8[DIGEST_SIZE];
}
void SHA256::update(char* buffer){
    uint64 l = strlen(buffer)*BITS8;
    uint16 n = l / MSG_BLOCK;
    uint32 m_size = BITS64 * (n+1);
    
    message=pad(buffer,l,m_size);
    
    M=parse(n);
    
    compute(n);
}
uint8* SHA256::getDigest(){
    return digest;
}

char* SHA256::hexDigest(){
    char* hex=new char[BITS64];
    char* hexDigest=new char[BITS32];
    memcpy(hexDigest,digest,BITS32);
    int j=0;
    for(int i=0;i<BITS32;i++){
        //Replace bits for char printable value
        //to do this, we need to take two temp values, divide the 8-bits between
        //them. Then we can put into hex
        uint8 first,second;
        first=digest[i]>>4;
        second=digest[i]<<4;
        second>>=4;
        hex[j++]=getHex(first);
        hex[j++]=getHex(second);
    }
    delete[] hexDigest;
    return hex;
}
char SHA256::getHex(uint8 val){
    switch(val){
        case 0: return '0';break;
        case 1: return '1';break;
        case 2: return '2';break;
        case 3: return '3';break;
        case 4: return '4';break;
        case 5: return '5';break;
        case 6: return '6';break;
        case 7: return '7';break;
        case 8: return '8';break;
        case 9: return '9';break;
        case 10: return 'a';break;
        case 11: return 'b';break;
        case 12: return 'c';break; 
        case 13: return 'd';break;
        case 14: return 'e';break;
        case 15: return 'f';break;
    }
    return 0;
}
uint8* SHA256::pad(char* buffer,const uint64& l,const uint32& m_size){
    uint8* m_block;

    m_block = new uint8[m_size];

    //Copy buffer into message block
    int len = strlen(buffer);
    for(int i=0;i<len;i++){
        m_block[i]=(uint8)buffer[i];
    }

    //Append '1' bit
    m_block[len]=0x80;  // 1000 0000
    
    //Pad message block to be multiple of 512 bits
    len=m_size-8;
    for(int i=strlen(buffer)+1;i<len;i++){
        m_block[i]=0x0;
    }
    
    //Append 64-bit block equal to l in binary
    int d=56;
    for(len;len<m_size;len++){
        m_block[len]=l>>d;
        d-=8;
    }
    //This will return the padded message as a multiple of 512
    return m_block;
}
uint32* SHA256::parse(const uint16& n){
    uint16 n_blocks=(n+1)*16;//Tells how many 16x32 bit blocks are needed
    uint32* M_block=new uint32[n_blocks];
    
    int j=0;
    for(int i=0;i<n_blocks;i++){
        M_block[i]=(message[j++]<<24|message[j++]<<16|message[j++]<<8|message[j++]);
    }
    
    return M_block;
}
void SHA256::compute(const uint16& n){
     uint32 H[] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };
    uint32 K[] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
        0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 
        0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
        0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
        0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
        0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
        0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
        0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 
        0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };
    //Computation
    for(int i=0;i<(n+1);i++){
        uint32 W[BITS64];
        for(int j=0;j<BITS64;j++){
            W[j]=0;
        }
        //1. Prepare the message schedule Wt
        for(int t=0;t<BITS64;t++){
            if(t<16){
                if(i>0)W[t]=M[t+16];
                else W[t]=M[t];
            }
            //sig1(W(t-2)) + W(t-7) + sig0(W(t-15))+W(t-16)
            else W[t] = sig1(W[t-2]) + W[t-7] + sig0(W[t-15]) + W[t-16];
        }
        //2. Initialize 8 working variables a,b,c,d,e,f,g,h
        uint32 a,b,c,d,e,f,g,h;
        a=H[0];
        b=H[1];
        c=H[2];
        d=H[3];
        e=H[4];
        f=H[5];
        g=H[6];
        h=H[7];
        //3. Loop t:=0 to 63
        for(int t=0;t<BITS64;t++){
            uint32 T1 = h + SIG1(e) + Ch(e,f,g) + K[t] + W[t];
            uint32 T2 = SIG0(a) + Maj(a,b,c);
            h = g;
            g = f;
            f = e;
            e = d + T1;
            d = c;
            c = b;
            b = a;
            a = T1 + T2;
        }
        //4. Compute the intermediate hash value H(i)
        H[0] += a;
        H[1] += b;
        H[2] += c;
        H[3] += d;
        H[4] += e;
        H[5] += f;
        H[6] += g;
        H[7] += h;
    }
    
    int t=0;
    for(int i=0;i<BITS32;i++){
        digest[i++] = H[t] >> 24;
        digest[i++] = H[t] >> 16;
        digest[i++] = H[t] >> 8;
        digest[i] = H[t++];
    }
}
uint32 SHA256::SHR(uint16 n,uint32 x){
    return x>>n;
}
uint32 SHA256::ROTR(uint16 n,uint32 x){
    return (x>>n)|(x<<(32-n));
}
uint32 SHA256::Ch(uint32 x,uint32 y,uint32 z){
    return (x&y)^(~x&z);
}
uint32 SHA256::Maj(uint32 x,uint32 y,uint32 z){
    return (x&y)^(x&z)^(y&z);
}
uint32 SHA256::SIG0(uint32 x){
    return ROTR(2,x) ^ ROTR(13,x) ^ ROTR(22,x);
}
uint32 SHA256::SIG1(uint32 x){
    return ROTR(6,x) ^ ROTR(11,x) ^ ROTR(25,x);
}
uint32 SHA256::sig0(uint32 x){
    return ROTR(7,x) ^ ROTR(18,x) ^ SHR(3,x);
}
uint32 SHA256::sig1(uint32 x){
    return ROTR(17,x) ^ ROTR(19,x) ^ SHR(10,x);
}