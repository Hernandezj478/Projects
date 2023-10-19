/* 
 * File:   AdminUser.cpp
 * Author: Joseph Hernandez
 *
 * Created on April 22, 2023, 8:43 PM
 */
#include "AdminUser.hpp"

AdminUser::AdminUser(){
    initMenu();
    //Get list of all users
    getUsers();
}
void AdminUser::initMenu(){
    std::string title = "Admin Menu";
    menu.editTitle(title);
    //View Users
    std::string op = "View Users";
    menu.addOption(op);
    //Edit user
    op="Edit User";
    menu.addOption(op);
    //Remove User
    op="Remove User";
    menu.addOption(op);
    //Logout
    op="Logout";
    menu.addOption(op);
}
void AdminUser::displayMenu(){
    std::cout<<menu.getTitle()<<":"<<std::endl;
    for(int i=0;i<menu.size();i++){
        std::cout<<i+1<<". "<<menu[i]<<std::endl;
    }
}
void AdminUser::getUsers(){
    //Get the total number of users, to do this, we can take the total file size
    //and divide it by the number of bits each user takes up -> passwd.bin format:
    // [email   ][password][priv   ][userID ] 
    // [160-bits][256-bits][32-bits][32-bits] => 480-bits (60 bytes)
    std::string fileName = "etc/passwd.bin";
    std::fstream file;
    file.open(fileName,std::ios::in|std::ios::binary);
    file.seekg(0,std::ios::end);
    int userBlock=sizeof(char)*20+sizeof(char)*32+sizeof(int)+sizeof(int);
    int fileSize = file.tellg();
    file.seekg(0,std::ios::beg);
    int numUsers = fileSize / userBlock;
    file.clear();
    file.close();
    
    
    //Now that we have the total number of users, we can iterate though, grabbing
    //the information we need from each user db file, we will need:
    //         user ID, email, first name, last name, personal ID,
    for(int i=1;i<numUsers;i++){
        std::fstream uFile;
        std::string ufileName = "home/db/" + std::to_string(i) + ".dat";
        uFile.open(ufileName,std::ios::in|std::ios::out|std::ios::binary|std::ios::app);
        
        if(!uFile.is_open()){
            continue;
        }
        
        //Create a new user and put into map
        StandardUser user;
        uFile.seekg(0,std::ios::beg);
        uFile.read(reinterpret_cast<char*>(&user.pID),sizeof(unsigned int));
        user.read(uFile);
        //Place user info into a struct that holds: user ID, email, personal ID,
        // first name, last name
        UserInfo info;
        info.uID=user.uID;
        info.pID=user.pID;
        info.courseQTY=user.courseQTY;
        info.email=(user.email);
        info.fname=(user.fname);
        info.lname=(user.lname);
        
        userList[i]=info;
        
        uFile.clear();
        uFile.close();
    }

}
void AdminUser::AdminSession(){
    //Need to make sure admin default password is reset.
    if(defaultPasswd()){
        changePasswd();
    }
    Scanner sc;
    int choice;
    do{
        displayMenu();
        choice=sc.nextInt();
        switch(choice){
            case 1: system("clear");viewUsers();break;//View Users
            case 2: system("clear");editUser();break;//Edit User
            case 3: system("clear");removeUser();break;//Remove User
        }
        system("clear");
    }while(choice!=4);
}
void AdminUser::viewUsers(){
    std::map<unsigned int,UserInfo>::iterator itr = userList.begin();
    
    for(itr;itr!=userList.end();itr++){
        std::cout<<"User ID: "<<itr->first<<" \n\tStudent ID:";
        std::cout<<itr->second.pID<<" \n\t\tName: "<<itr->second.lname<<", "<<
                itr->second.fname<<" \n\t\tEmail: "<<itr->second.email<<std::endl;
    }
    std::cout<<"\n\nPress ENTER to continue...";
    std::cin.get();
}
void AdminUser::editUser(){
    //Get the user ID the admin will change
    std::cout<<"Enter User ID to Edit: ";
    Scanner sc;
    unsigned int id=sc.nextInt();
    
    //Make sure the user ID exist -> passwd.bin && [uID].dat
    if(userIDCheck(id)){
        //Create a new standard user object, then fill with the appropriate data
        StandardUser user;
        user.fillUserData(id);
        
        Menu menu;
        initMenu(menu);
        std::string title="Edit User " + std::to_string(id) + ": "
                            + userList[id].lname+", "+userList[id].fname
                            + " - " + userList[id].email;
        menu.editTitle(title);
        int choice;
        //Edit the user
        do{            
            displayMenu(menu);
            Scanner sc;
            choice=sc.nextInt();

            switch(choice){
                case 1:system("clear");user.viewCourses();break;//View course
                case 2:system("clear");user.editCourseTime();break;//Edit course
                //case 3:system("clear");break;//Remove course
            }
            system("clear");
        }while(choice!=3);
    }
    else{
        std::cout<<"No User Exists..."<<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}
void AdminUser::removeUser(){
    //Ask admin what user ID to remove
    std::cout<<"Enter User ID to remove: ";
    Scanner sc;
    unsigned int userID=sc.nextInt();
    //Search for the userID
    if(userIDCheck(userID)){
        //We need to iterate through the passwd file until we find the userID
        // [email][password][privilege][userID]
        std::fstream in;
        in.open("etc/passwd.bin",std::ios::in|std::ios::binary);
        std::fstream out;
        out.open("var/temp.bin",std::ios::out|std::ios::binary);
        
        //Find the userID in the file
        long cursor=0L;
        in.seekg(0,std::ios::end);
        long size=in.tellg();
        
        unsigned int srchID;
        
        while(cursor<size){
            ConfInfo info;
            in.seekg(cursor,std::ios::beg);
            in.read(reinterpret_cast<char*>(&info),sizeof(ConfInfo));
            if(info.uID==userID){
                //Found the block we want to delete
                std::cout<<"User removed"<<std::endl;
            }
            else{
                //Copy the contents into the new temp file
                out.write(reinterpret_cast<char*>(&info),sizeof(ConfInfo));
            }
            cursor+=sizeof(ConfInfo);
        }
        in.close();
        out.close();
        
        //delete old file
        remove("etc/passwd.bin");
        //rename temp file
        rename("var/temp.bin","etc/passwd.bin");
        //Now we need to clean up any other files associated with the user
        // i.e. [uID].dat & [lastName]_[userID].dat & [lastName]_[personalID].log
        //We have the list of all users in the map, grab that info and use it to
        //remove these unwanted files
        std::map<unsigned int,UserInfo>::iterator itr = userList.find(userID);
        if(itr!=userList.end()){
            //We now have the correct user info, remove [uID].dat
            std::string fileName = "home/db/" + std::to_string(userID) + ".dat";
            remove(fileName.c_str());
            //Remove [lastName]_[userID].dat
            fileName = "home/usr/" + itr->second.lname + "_" 
                    + std::to_string(userID) + ".dat";
            remove(fileName.c_str());
            //Remove [lastName]_[personalID].log
            fileName = "var/logs/" + itr->second.lname + "_" 
                    + std::to_string(itr->second.pID) + ".log";
            remove(fileName.c_str());
        }
        //Remove user info from map
        userList.erase(userID);
    }
    else{
        std::cout<<"User does not exist"<<std::endl;
    }
}
void AdminUser::initMenu(Menu& menu){
    std::string title="Edit User";
    menu.editTitle(title);
    std::string op="View Courses";
    menu.addOption(op);
    op="Edit Course";
    menu.addOption(op);
    /*op="Remove Course";
    menu.addOption(op);*/
    op="Back";
    menu.addOption(op);
}
void AdminUser::displayMenu(Menu menu){
    std::cout<<menu.getTitle()<<std::endl;
    for(int i=0;i<menu.size();i++){
        std::cout<<i+1<<". "<<menu[i]<<std::endl;
    }
}
bool AdminUser::userIDCheck(unsigned int id){
    bool valid1,valid2;
    
    
    std::fstream passwdFile;
    passwdFile.open("etc/passwd.bin",std::ios::in);
    passwdFile.seekg(0,std::ios::end);
    long pSize=passwdFile.tellg();
    //Find the user ID -> [  email ][password][  priv ][userID ]
    //                    [160 bits][256 bits][32 bits][32 bits]
    
    long cursor=((sizeof(char)*20)+(sizeof(char)*32)+sizeof(int));
    
    while(cursor<pSize){
        unsigned int fID;
        passwdFile.seekg(cursor,std::ios::beg);
        passwdFile.read(reinterpret_cast<char*>(&fID),sizeof(unsigned int));
        if(fID!=id){
            cursor+=((sizeof(char)*20)+(sizeof(char)*32)+sizeof(int)+sizeof(unsigned int));
            valid1=false;
        }
        else{
            valid1=true;
            break;
        }
    }
    passwdFile.clear();
    passwdFile.close();
    
    std::fstream userDat;
    std::string uDatName = "home/db/" + std::to_string(id) + ".dat";
    userDat.open(uDatName,std::ios::in);
    if(!userDat.is_open()){
        valid2=false;
    }
    else{
        userDat.close();
        valid2=true;
    }
    
    return (valid1&&valid2);
}
bool AdminUser::defaultPasswd(){
    char passwd[] = "password";
    SHA256 hash(passwd);
    char* digest=(char*)hash.getDigest();
    
    long cursor=sizeof(char)*20;
    
    std::fstream file;
    file.open("etc/passwd.bin",std::ios::in|std::ios::binary|std::ios::ate);
    file.seekg(cursor,std::ios::beg);

    char fileDigest[32];
    file.read(fileDigest,sizeof(char)*32);
    
    file.close();

    if(memcmp(fileDigest,digest,32)==0)
        return true;
    return false;
}
void  AdminUser::changePasswd(){
    bool valid;
    char* passwd;
    do{
       Scanner sc;
        std::cout<<"WARNING: Default Password!\n";
        std::cout<<"New Password:";
        passwd = sc.nextChar(); 
        valid=this->passwdFormat(passwd);
        if(!valid){
            delete[] passwd;
        }
    }while(!valid);
    
    SHA256 hash(passwd);
    char* digest=(char*)hash.getDigest();
    //Replace password
    std::fstream file;
    file.open("etc/passwd.bin",std::ios::in|std::ios::out|std::ios::binary|std::ios::ate);
    
    long cursor=sizeof(char)*20;
    
    file.seekp(cursor,std::ios::beg);
    file.write(digest,sizeof(char)*32);
    
    file.close();
}