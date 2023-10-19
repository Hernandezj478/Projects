/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   AdminPlayer.cpp
 * Author: aawri
 * Edited by: Joseph Hernandez
 * 
 * Created on April 27, 2023, 1:18 AM
 * Edited on April 27, 2023, 12:49PM
 */

#include "AdminPlayer.hpp"

AdminPlayer::AdminPlayer() {
     readDataIntoMap();
}
void AdminPlayer::adminSession(Menu& menu){
    Scanner sc;
    //Start admin loop
    int choice;
    system("clear");
    do{
        menu.printAdminMenu();
        cout<<setw(21)<<""<<"Selection: ";
        choice=sc.nextInt();
        switch(choice){
            case 1:system("clear");showUsers();break;//View Users
            case 2:system("clear");removeUser();break;//Remove User
        }
        system("clear");
    }while(choice!=3);
}
void AdminPlayer::readDataIntoMap(){
    fstream file("home/user_info.dat", std::ios::in | std::ios::binary);
    if (!file) {
        std::cout << "Error opening file!" << std::endl;
        return;
    }
    
    long cursor=0L;
    file.seekg(0, std::ios::end);
    long end_pos = file.tellg();
    file.seekg(0, std::ios::beg);
    while(cursor<end_pos){
        UserInfo info;
        file.seekg(cursor,ios::beg);
        file.read(reinterpret_cast<char*>(&info.id),sizeof(unsigned int));
        file.read(reinterpret_cast<char*>(&info.size),sizeof(int));
        info.name=new char[info.size];
        file.read(info.name,sizeof(char)*info.size);
        cursor+=(sizeof(int)+sizeof(int)+info.size);
        //Map users
        users[info.id]=info.name;
    }
    file.close();
}

void AdminPlayer::showUsers(){
    std::map<unsigned int,std::string>::iterator it;
    cout<<setw(21)<<""<<"User ID:";
    cout<<setw(5)<<""<<"User Name: "<<endl;
    
    for(it = users.begin(); it != users.end(); it++){
        cout<<setw(28)<<""<< it->first << setw(5)<<""<<it->second << std::endl;
    }
    //Wait for input to continue
    cout<<"\n\n";
    cout<<setw(21)<<""<<"Press ENTER to continue...";
    cin.get();
}

void AdminPlayer::removeUser(){
    Scanner sc;
    unsigned int id;
    cout<<setw(21)<<""<<"Enter User ID: ";
    id=sc.nextInt();
    //Remove user from passwd.bin
    fstream file,tmp;

    file.open("etc/passwd.bin",ios::in|ios::binary);
    tmp.open("etc/temp.bin",ios::out|ios::binary);
    long cursor=0L;
    file.seekg(0,ios::end);
    long size=file.tellg();
    while(cursor<size){
        LoginInfo info;
        file.seekg(cursor,ios::beg);
        file.read(reinterpret_cast<char*>(&info),sizeof(LoginInfo));
        if(info.id!=id){
            //Only write to tmp file if not id
            tmp.write(reinterpret_cast<char*>(&info),sizeof(LoginInfo));
        }
        cursor+=sizeof(LoginInfo);
    }
    file.close();
    tmp.close();
    
    //Remove old file
    remove("etc/passwd.bin");
    //Rename tmp file
    rename("etc/temp.bin","etc/passwd.bin");
    
    //Remove user info from userInfo.dat
    fstream userFile,tmpUserFile;
    userFile.open("home/user_info.dat",ios::in|ios::binary);
    tmpUserFile.open("home/tmp.dat",ios::out|ios::binary);
    cursor=0L;
    userFile.seekg(0,ios::end);
    size=userFile.tellg();
    
    while(cursor<size){
        UserInfo info;
        userFile.seekg(cursor,ios::beg);
        userFile.read(reinterpret_cast<char*>(&info.id),sizeof(unsigned int));
        userFile.read(reinterpret_cast<char*>(&info.size),sizeof(int));
        info.name=new char[info.size];
        userFile.read(info.name,info.size);
        
        if(id!=info.id){
            tmpUserFile.seekp(0,ios::cur);
            tmpUserFile.write(reinterpret_cast<char*>(&info.id),sizeof(unsigned int));
            tmpUserFile.write(reinterpret_cast<char*>(&info.size),sizeof(int));
            tmpUserFile.write(info.name,info.size);
        }
        cursor+=(sizeof(unsigned int)+sizeof(int)+info.size);
        delete[] info.name;
    }

    //Remove old file
    remove("home/user_info.dat");
    //Rename tmp file
    rename("home/tmp.dat","home/user_info.dat");
    
    //Delete user's scorecard
    string userCard = "saves/" + users[id] + "_" + to_string(id) + ".sav";
    remove(userCard.c_str());
    
    //Remove from map
    users.erase(id);
    
}