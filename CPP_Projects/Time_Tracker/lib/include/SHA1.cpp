/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include "SHA1.hpp"

SHA1::SHA1(){
    init();
}
SHA1::SHA1(char* buffer){
    init();
    uint64 l = strlen(buffer)*BITS8;
    uint16 n = l / MSG_BLOCK;
    uint32 m_size = BITS64 * (n+1);
    
    message=pad(buffer,l,m_size);
    M=parse(n);
    
    //Compute SHA1
    compute(n);
}

SHA1::~SHA1(){
    delete[] digest;
    delete[] message;
    delete[] M;
}

void SHA1::init(){
    digest=new uint8[DIGEST_SIZE];
}

uint8* SHA1::getDigest(){
    return digest;
}

void SHA1::update(char* buffer){
    uint64 l = strlen(buffer)*BITS8;
    uint16 n = l / MSG_BLOCK;
    uint32 m_size = BITS64 * (n+1);
    
    message=pad(buffer,l,m_size);
    M=parse(n);
    
    //Compute SHA1
    compute(n);
}
char* SHA1::hexDigest(){
    char* hex=new char[DIGEST_SIZE*2];
        
    int j=0;
    for(int i=0;i<DIGEST_SIZE;i++){
        uint8 first,second;
        first=digest[i]>>4;
        second=digest[i]<<4;
        second>>=4;
        hex[j++]=getHex(first);
        hex[j++]=getHex(second);
    }
    return hex;
}
char SHA1::getHex(uint8 val){
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

uint8* SHA1::pad(char* buffer,const uint64& l,const uint32& m_size){
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
uint32* SHA1::parse(const uint16& n){
    uint16 n_blocks=(n+1)*16;//Tells how many 16x32 bit blocks are needed
    uint32* M_block=new uint32[n_blocks];
    
    int j=0;
    for(int i=0;i<n_blocks;i++){
        M_block[i]=(message[j++]<<24|message[j++]<<16|message[j++]<<8|message[j++]);
    }
    return M_block;
}
void SHA1::compute(const uint16& n){
    uint32 H[] = {
        0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476, 0xc3d2e1f0
    };
    uint32 K[] = {
        0x5a827999,         //0<=t<=19
        0x6ed9eba1,         //20<=t<=39
        0x8f1bbcdc,         //40<=t<=59
        0xca62c1d6          //60<=t<=79
    };
    for(int i=0;i<=n;i++){
        //1. Prep message schedule
        uint32 W[MSG_SCHED];
        for(int t=0;t<MSG_SCHED;t++){
            W[t]=0;
        }
        for(int t=0;t<MSG_SCHED;t++){
            if(t<16){
                if(i>0)W[t]=M[t+16];
                else W[t]=M[t];
            }
            else{
                //ROTL1(W(t-3) XOR W(t-8) XOR W(t-14) XOR W(t-16))
                uint32 wt = (W[t-3]^W[t-8]^W[t-14]^W[t-16]);
                W[t] = ROTL(1,wt);
            }
        }
        //2. Initialize five working vars
        uint32 a,b,c,d,e;
        a=H[0];
        b=H[1];
        c=H[2];
        d=H[3];
        e=H[4];
        //3. for t:= 0 - 79
        for(int t=0;t<MSG_SCHED;t++){
            uint32 f,k,T;
            if(t<20){
                f = Ch(b,c,d);
                k=K[0];
            }
            else if(t<40){
                f = Parity(b,c,d);
                k = K[1];
            }
            else if(t<60){
                f = Maj(b,c,d);
                k = K[2];
            }
            else{
                f = Parity(b,c,d);
                k = K[3];
            }
            T = ROTL(5,a) + f + e + k + W[t];
            e=d;
            d=c;
            c=ROTL(30,b);
            b=a;
            a=T;
        }
        //4. COmputer has val H(i)
        H[0]+=a;
        H[1]+=b;
        H[2]+=c;
        H[3]+=d;
        H[4]+=e;
    }
    int t=0;
    for(int i=0;i<DIGEST_SIZE;i++){
        digest[i++] = H[t]>>24;
        digest[i++] = H[t]>>16;
        digest[i++] = H[t]>>8;
        digest[i] = H[t++];
    }
}
uint32 SHA1::Ch(uint32 x,uint32 y,uint32 z){
    return (x&y)^(~x&z);
}
uint32 SHA1::Parity(uint32 x,uint32 y,uint32 z){
    return x^y^z;
}
uint32 SHA1::Maj(uint32 x,uint32 y,uint32 z){
    return (x&y)^(x&z)^(y&z);
}
uint32 SHA1::ROTL(uint16 n,uint32 x){
    return (x<<n)|(x>>(32-n));
}
