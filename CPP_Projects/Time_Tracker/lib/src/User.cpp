/* 
 * File:   User.cpp
 * Author: Joseph Hernandez
 *
 * Created on April 11, 2023, 6:34 PM
 */

#include "User.hpp"
User::User(){
    email=nullptr;
}
User::~User(){
    if(email!=nullptr){
        delete[] email;
    }
    
}
bool User::newUser(){
    std::fstream file;
    //We assume the file has already been created.
    file.open("etc/passwd.bin",std::ios::in|std::ios::out|std::ios::binary|std::ios::ate);
    bool success;
    bool valid;
    Scanner sc;
    //Get email
    char* tmpEmail;
    char* tmpPasswd;
    do{
        std::cout<<"Enter email: ";
        tmpEmail=sc.nextChar();
        valid=emailFormat(tmpEmail);
        if(!valid){
           delete[] tmpEmail; 
        }
    }while(!valid);
    email=tmpEmail;
    //Now we need to verify if the email exists
    if(!findEmail(file)){
        do{
            std::cout<<"Enter Password: ";
            tmpPasswd=sc.nextChar();
            valid=passwdFormat(tmpPasswd);
            if(!valid){
                delete[] tmpPasswd;
            }
        }while(!valid);
        //The only time a new user will be created is from the main menu, therefore
        //the new users will ALWAYS be standard users.
        priv=Priv::Standard;
        //We need to hash the email and password to store into the passwd.bin file
        SHA256 passwdHash(tmpPasswd);
        char* digest=(char*)passwdHash.getDigest();
        //We need to set the userID -> will need to pull last user ID from the file
        setUID(file);
        //Now we need to write to the file. Since we have just read in the last
        //uID we are at the end of the file, so we can just append to the file
        writeUser(file,digest);
        success=true;
    }
    else success=false;
    
    delete[] tmpPasswd;
    file.clear();
    file.close();
    
    return success;
}
bool User::findEmail(std::fstream& file){
    //Search through the file to see if the email exists, if it does return true
    //else return false
    SHA1 hash(email);
    char* digest=(char*)hash.getDigest();
    long cur=file.tellg();
    long cursor=0L;
    file.seekg(0,std::ios::end);
    int size=file.tellg();
    char tmp[20];
    int emailBlock=0;
    while(cursor<size){
        //Iterate through the file, grab each email hash and compare
        file.seekg(cursor,std::ios::beg);
        file.read(tmp,sizeof(char)*20);
        
        for(int i=0;i<20;i++){
            if((digest[i]^tmp[i])!=0){ 
                break;
            }
            else{
                emailBlock++;
            }
        }
        cursor+=((sizeof(char)*20)+(sizeof(char)*32)+sizeof(int)+sizeof(unsigned int));
    }
    //delete[] tmp;
    file.clear();
    file.seekg(cur,std::ios::beg);
    if(emailBlock==20) return true;
    //Since the email doesnt exist, we can place the file pointer back to read
    //the previous user ID, this will allow us to increment the uID
    else{
        return false;
    }
}
bool User::emailFormat(char* email){
    char emailSet=0;
    int size=strlen(email);
    for(int i=0;i<size;i++){
        if(isalpha(email[i])){
            email[i]=tolower(email[i]);
            emailSet|=8;
        }
        else if(isdigit(email[i])){
            emailSet|=4;
        }
        else if(email[i]=='@'){
            emailSet|=2;
        }
        else if(email[i]=='.'){
            emailSet|=1;
        }
    }
    if((emailSet== 15) || (emailSet==11))
        return true;
    
    std::cout<<"Not a valid email address"<<std::endl;
    return false;
}
bool User::passwdFormat(char* passwd){
    //Password needs capital letter, lower case letter, number, length and
    //special character (! @ # $ &)
    //Use some sort of bit manip to check if all categories are set
    // x x x | _ _ _ _ _ -> last 5 bits will represent out conditions
    char passSet=0;
    int len = strlen(passwd);
    if(len>=8){
        passSet|=16;
    }
    for(int i=0;i<len;i++){
        if(isupper(passwd[i]))
            passSet|=8;
        if(islower(passwd[i]))
            passSet|=4;
        if(isdigit(passwd[i]))
            passSet|=2;
        if((passwd[i]=='!') || (passwd[i]=='@')
            || (passwd[i]=='#') || (passwd[i]=='$')
                || (passwd[i]=='&'))
            passSet|=1;
    }
    if(passSet!=31){
        std::cout<<"Password criteria not met"<<std::endl;
        std::cout<<"Need:\n\tAt least 8 characters\n\tCapital Letter\n\tLower Case Letter"
                "\n\tNumber\n\tSpecial Character(! @ # $ &)"<<std::endl;
        return false;
    }
    return true;
}
void User::setUID(std::fstream& file){
    unsigned int lastID;
    file.seekg(-(sizeof(int)),std::ios::end);
    file.read(reinterpret_cast<char*>(&lastID),sizeof(unsigned int));
    uID=lastID+1;
}
void User::writeUser(std::fstream& file,char* passwdDigest){
    //The format for the passwd.bin -> [emailhash][passwdhash][priv][uID]
    //Hash email
    file.clear();
    file.seekp(0,std::ios::end);
    SHA1 hash(email);
    char* emailDigest=(char*)hash.getDigest();
    file.write(emailDigest,sizeof(char)*20);
    file.write(passwdDigest,sizeof(char)*32);
    file.write(reinterpret_cast<char*>(&priv),sizeof(int));
    file.write(reinterpret_cast<char*>(&uID),sizeof(unsigned int));
}