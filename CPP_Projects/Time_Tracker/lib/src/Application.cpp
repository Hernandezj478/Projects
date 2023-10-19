/* 
 * File:   Application.cpp
 * Author: Joseph Hernandez
 *
 * Created on April 22, 2023, 12:16 PM
 */

#include "Application.hpp"

Application::Application(){
    //Initialize Menu
    initMenu();
    //Check if passwd.bin exist
    checkFile();
}
void Application::initMenu(){
    std::string title="Welcome";
    menu.editTitle(title);
    std::string op="Login";
    menu.addOption(op);
    op="Create User";
    menu.addOption(op);
    op="Exit";
    menu.addOption(op);
}
void Application::displayMenu(){
    std::cout<<menu.getTitle()<<std::endl;
    for(int i=0;i<menu.size();i++){
        std::cout<<i+1<<". "<<menu[i]<<std::endl;
    }
}
void Application::checkFile(){
    std::fstream file;
    file.open("etc/passwd.bin",std::ios::in|std::ios::binary);
    if(!file.is_open()){
        createFile();
    }
    else
        file.close();
}
void Application::createFile(){
    std::fstream file;
    file.open("etc/passwd.bin",std::ios::out|std::ios::binary);
    //Create default admin
    char name[] = "admin";
    char passwd[] = "password";
    Priv priv=Priv::Admin;
    int userID = 0;
    
    
    SHA1 nameHash(name);
    SHA256 passwdHash(passwd);
    
    char* nameDigest = (char*)nameHash.getDigest();
    char* passwdDigest = (char*)passwdHash.getDigest();
    
    file.seekp(0,std::ios::beg);
    file.write(nameDigest,sizeof(char)*20);
    file.write(passwdDigest,sizeof(char)*32);
    file.write(reinterpret_cast<char*>(&priv),sizeof(int));
    file.write(reinterpret_cast<char*>(&userID),sizeof(int));
    
    
    file.close();
}
void Application::run(){
    int choice;
    do{
        displayMenu();
        Scanner sc;
        choice=sc.nextInt();
        bool nU=true;
        switch(choice){
            case 1:system("clear");logIn();break;//Login
            case 2:system("clear");nU=createUser();break;//Create User
        }
        if(!nU)std::this_thread::sleep_for(std::chrono::seconds(1));
        system("clear");
    }while(choice!=3);
}
void Application::logIn(){
    //We need to have the user enter their email and password to gain successful
    //entry to their account
    
    std::fstream file;
    file.open("etc/passwd.bin",std::ios::in|std::ios::binary);
    file.clear();
    Scanner sc;
    std::cout<<"Email: ";
    char* email=sc.nextChar();
    //Format email -> lowercase all alpha
    int len=strlen(email);
    for(int i=0;i<len;i++){
        if(isalpha(email[i])){
            email[i]=tolower(email[i]);
        }
    }
    //Search through file to find email
    if(foundEmail(file,email)){
        //Check password
        std::cout<<"Password: ";
        char* passwd=sc.nextChar();
        if(passwdValid(file,passwd)){
            //Get privilege
             Priv priv=readPriv(file);
            if(priv==Priv::Admin){
                AdminUser* admin=new AdminUser;
                system("clear");
                admin->AdminSession();
                delete admin;
            }
            else{
                //Get user ID
                unsigned int id=readID(file);
                StandardUser* user = new StandardUser;
                system("clear");
                user->standardSession(id);
                delete user;
            }
        }
    }
    else{
        std::cout<<"No email on record"<<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    
    file.clear();
    file.close();
}
bool Application::foundEmail(std::fstream& file,char* email){
    
    SHA1 hash(email);
    char* digest = (char*)hash.getDigest();
    
    file.seekg(0,std::ios::end);
    long size = file.tellg();
    long cursor=0L;
    while(cursor<size){
        char inDigest[20];
        file.seekg(cursor,std::ios::beg);
        file.read(inDigest,sizeof(char)*20);
        if(memcmp(inDigest,digest,sizeof(char)*20)==0){
            return true;
        }
        cursor+=(sizeof(char)*20+sizeof(char)*32+sizeof(int)+sizeof(int));
    }
    return false;
}
bool Application::passwdValid(std::fstream& file,char* passwd){
    SHA256 hash(passwd);
    char* digest=(char*)hash.getDigest();
    char inDigest[20];
    //Read from the file
    file.seekp(0,std::ios::cur);
    file.read(inDigest,sizeof(char)*32);
    
    if(strcmp(inDigest,digest)!=0)
        return false;
    return true;
    
}
Priv Application::readPriv(std::fstream& file){
    file.seekg(0,std::ios::cur);
    Priv priv;
    file.read(reinterpret_cast<char*>(&priv),sizeof(int));
    
    return priv;
}
unsigned int Application::readID(std::fstream& file){
    file.seekg(0,std::ios::cur);
    unsigned int id;
    file.read(reinterpret_cast<char*>(&id),sizeof(int));
    return id;
}
bool Application::createUser(){
    StandardUser* user=new StandardUser;
    bool nu = user->newStandard();
    delete user;
    return nu;
}
void read(){
    std::fstream file;
    file.open("etc/passwd.bin",std::ios::in|std::ios::binary);
    file.clear();
    char* name=new char[20];
    char* passwd=new char[32];
    Priv priv;
    unsigned int userID;

    file.seekg(0,std::ios::beg);

    file.read(name,sizeof(char)*20);
    file.read(passwd,sizeof(char)*32);
    file.read(reinterpret_cast<char*>(&priv),sizeof(int));
    file.read(reinterpret_cast<char*>(&userID),sizeof(unsigned int));

    delete[] name;
    delete[] passwd;
    file.close();
}