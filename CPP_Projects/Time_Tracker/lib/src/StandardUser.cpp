/* 
 * File:   StandardUser.cpp
 * Author: Joseph Hernandez
 *
 * Created on April 16, 2023, 12:17 PM
 */

#include "StandardUser.hpp"

StandardUser::StandardUser(){
    menuInit();
    fname=nullptr;
    lname=nullptr;
}
StandardUser::~StandardUser(){
    if(fname!=nullptr){
        delete[] fname;
    }
    if(lname!=nullptr){
        delete[] lname;
    }
}
void StandardUser::menuInit(){
    //Title
    std::string title = "User Menu:";
    menu.editTitle(title);
    //1. View Courses
    std::string op = "View Course";
    menu.addOption(op);
    //2. Select Course
    op = "Select Course";
    menu.addOption(op);
    //3. Register Course
    op = "Register Course";
    menu.addOption(op);
    //4. Log out
    op = "Logout";
    menu.addOption(op);
}
void StandardUser::displayMenu(){
    std::cout<<menu.getTitle()<<std::endl;
    int size=menu.size();
    for(int i=0;i<size;i++){
        std::cout<<i+1<<". "<<menu[i]<<std::endl;
    }
}
void StandardUser::standardSession(unsigned int uID){
    //We need just the uID to start the process of gathering the appropriate
    //information. This assumes the uID exists and has been pulled from the 
    //passwd.bin file
    this->uID=uID;
    std::fstream file;
    std::string fileName = "home/db/" + std::to_string(uID) + ".dat";
    file.open(fileName,std::ios::in|std::ios::out|std::ios::binary);
    file.read(reinterpret_cast<char*>(&pID),sizeof(unsigned int));
    read(file);
    //Clear eof bit
    file.clear();
    file.seekg(0,std::ios::beg);
    //Now that we have the relevant information, we can proceed to have the user
    //Select the course they want to proceed to the course menu
    int choice;
    do{
        displayMenu();
        Scanner sc;
        choice=sc.nextInt();
        switch(choice){
            case 1: system("clear");viewCourses();break;//View courses - iterate through the map only if it has elements
            case 2: system("clear");selectCourse();break;//Select the course and start the course session
            case 3: regCourse(file);break;//Register course
        }
        system("clear");
    }while(choice!=4);
    file.clear();
    file.close();
}
void StandardUser::fillUserData(unsigned int uID){
    //Open the file with the appropriate user ID
    std::fstream file;
    std::string fileName = "home/db/" + std::to_string(uID) + ".dat";
    file.open(fileName,std::ios::in|std::ios::binary);
    this->uID=uID;
    file.read(reinterpret_cast<char*>(&pID),sizeof(unsigned int));
    read(file);
    file.clear();
    file.close();
}
bool StandardUser::newStandard(){
    //This assumes there is not a user with the current 
    std::cout<<"Create Account: "<<std::endl;
    Scanner sc;
    //Call the new user function, this will return true/false -> false if user exists
    if(this->newUser()){
        //Get personal ID
        std::cout<<"Enter Personal ID: ";
        pID=sc.nextInt();
        //Get first name
        std::cout<<"Enter First Name: ";
        fname=sc.nextChar();
        //Get last name
        std::cout<<"Enter Last Name: ";
        lname=sc.nextChar();
        //Set the number of courses
        courseQTY=0;

        //Now we need to save all of this information into the file -> [userID].dat
        std::string fileName = "home/db/" + std::to_string(this->uID) + ".dat";
        std::fstream file;
        file.open(fileName,std::ios::out|std::ios::binary);
        write(file);
        file.clear();
        file.close();
        return true;
    }
    else{
        std::cout<<"User Already Exists..."<<std::endl;
    }
    return false;
}
void StandardUser::write(std::fstream& file){
    //File format -> [pID][emailSize][fnameSize][lnameSize][courseQTY]
    //              { [email][fname][lname]{ [courseNo][cnameSize][courseName] }
    //We will write the course information when the user creates a course
    
    int emailSize=strlen(email)+1;
    int fnameSize=strlen(fname)+1;
    int lnameSize=strlen(lname)+1;
    
    file.seekp(0,std::ios::cur);
    file.write(reinterpret_cast<char*>(&pID),sizeof(unsigned int));
    file.write(reinterpret_cast<char*>(&emailSize),sizeof(int));
    file.write(reinterpret_cast<char*>(&fnameSize),sizeof(int));
    file.write(reinterpret_cast<char*>(&lnameSize),sizeof(int));
    file.write(reinterpret_cast<char*>(&courseQTY),sizeof(unsigned int));
    file.write(email,sizeof(char)*emailSize);
    file.write(fname,sizeof(char)*fnameSize);
    file.write(lname,sizeof(char)*lnameSize);
}
void StandardUser::read(std::fstream& file){
    //Get the email Size
    int emailSize,fnameSize,lnameSize;
    file.seekg(0,std::ios::cur);
    file.read(reinterpret_cast<char*>(&emailSize),sizeof(int));
    file.read(reinterpret_cast<char*>(&fnameSize),sizeof(int));
    file.read(reinterpret_cast<char*>(&lnameSize),sizeof(int));
    file.read(reinterpret_cast<char*>(&courseQTY),sizeof(unsigned int));
    
    //Get the email/fname/lname ready to read in
    this->email=new char[emailSize];
    fname=new char[fnameSize];
    lname=new char[lnameSize];
    //Read in email/fname/lname
    file.read(email,sizeof(char)*emailSize);
    file.read(fname,sizeof(char)*fnameSize);
    file.read(lname,sizeof(char)*lnameSize);
    
    //check if qty>0 so we can read in the remainder of the course information
    for(int i=0;i<courseQTY;i++){
        unsigned int cID;
        int cNameSize;
        char* cName;
        file.seekg(0,std::ios::cur);
        file.read(reinterpret_cast<char*>(&cID),sizeof(unsigned int));
        file.read(reinterpret_cast<char*>(&cNameSize),sizeof(int));
        //Allocate memory for the course name
        cName = new char[cNameSize];
        //Read in the course name
        file.read(cName,sizeof(char)*cNameSize);
        //Map the courses number to the course name
        courseNames[cID]=cName;
    }
}
void StandardUser::regCourse(std::fstream& file){
    
    courseQTY++;
    file.seekp(sizeof(int)*4,std::ios::beg);
    file.write(reinterpret_cast<char*>(&courseQTY),sizeof(int));
    Scanner sc;
    //get course number
    std::cout<<"Course Number:";
    unsigned int cID = (unsigned int)sc.nextInt();
    //Need to check that this course does not exists
    if(courseCheck(cID)){
        //get course name
        std::cout<<"Course Name: ";
        char* cName=sc.nextChar();
        int size=strlen(cName);
        //We can just append the course info to the file: lname_uID.dat
        file.seekp(0,std::ios::end);
        file.write(reinterpret_cast<char*>(&cID),sizeof(unsigned int));
        file.write(reinterpret_cast<char*>(&size),sizeof(int));
        file.write(cName,sizeof(char)*size);
        //Return the file pointer to the beg of the file
        file.seekg(0,std::ios::beg);
        
        
        
        //Now we need to create an empty file for the course
        std::string name=lname;
        std::string userID=std::to_string(uID);
        std::string fileName = "home/usr/"+name+"_"+userID+".dat";
        std::fstream course_file;
        course_file.open(fileName,std::ios::out|std::ios::binary|std::ios::app);
        
        Course currCourse;
        currCourse.regCourse(course_file,cID);
        
        //Update map
        courseNames[cID]=cName;
        
        course_file.close();
    }
    
}
bool StandardUser::courseCheck(unsigned int cID){
    //This is based on us already reading in the file information, including
    //the map of all courses and their names. So, we can iterate thought the map,
    //referencing its first member variable
    std::map<unsigned int,std::string>::iterator itr=courseNames.begin();
    for(itr;itr!=courseNames.end();itr++){
        if(itr->first==cID)
            return false;
    }
    return true;
}
void StandardUser::viewCourses(){
    //Print out contents of the map
    //only if the map is not empty
    if(!courseNames.empty()){
        std::cout<<"Course Number:"<<std::setw(16)<<"Course Name:\n";
        std::map<unsigned int,std::string>::iterator itr = courseNames.begin();
        for(itr;itr!=courseNames.end();itr++){
            std::cout<<std::setw(6)<<""<<itr->first;
            std::cout<<std::setw(6)<<""<<itr->second<<std::endl;
        }
        std::cout<<"\n\nPress ENTER to continue...";
        std::cin.get();
        system("clear");
    }
    else{
        std::cout<<"No courses registered\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}
void StandardUser::selectCourse(){
    //Course info will be stored in file: lastname_uID.dat
    //We need to get the course ID from the user
    std::cout<<"Enter course ID:";
    Scanner sc;
    int cID = sc.nextInt();
    std::map<unsigned int,std::string>::iterator itr = courseNames.find(cID);
    system("clear");
    if(itr!=courseNames.end()){
        std::string name = lname;
        std::string userID = std::to_string(uID);
        std::string fileName = "home/usr/"+name+"_"+userID+".dat";
        std::fstream file;
        file.open(fileName,std::ios::in|std::ios::out|std::ios::binary);
        
        Course course;
        std::string title=courseNames[cID] + "-" + std::to_string(cID);
        course.menu.editTitle(title);
        //Now we need to grab that course from the file
        //      To do this, we will need to iterate through the file until we
        //      find the correct course -> file: lname_uID.dat
        course.findCourse(file,cID);
        long cur=file.tellg();
        //When we find the course, the file pointer will be at the end of the
        //course ID, once we do then we can clock in/out
        //Fill all information from the file
        course.courseSession(file);
        int choice;
        do{
            file.clear();
            file.seekg(cur,std::ios::beg);
            course.displayMenu();

            Scanner sc;
            choice=sc.nextInt();
            switch(choice){
                case 1:system("clear");course.punchIn(file);break;//Clock in
                case 2:
                    system("clear");
                    std::fstream log;
                    std::string name = lname;
                    std::string personalID = std::to_string(pID);
                    std::string logName = "var/logs/"+name+"_"+personalID+".log";
                    log.open(logName,std::ios::out|std::ios::binary|std::ios::app);
                    
                    course.punchOut(file);
                    course.logSessionTime(log);
                    
                    log.close();
            }
            system("clear");
        }while(choice!=3);
        file.close();
    }
    else{
        std::cout<<"No Courses on Record"<<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        system("clear");
    }
}
void StandardUser::editCourseTime(){
    using namespace std::chrono;
    using namespace std::literals::chrono_literals;
    
    Scanner sc;
    
    //View logs
    std::cout<<"Would you like to view the user logs (Y/N)?\n";
    char choice;
    std::cin>>choice;
    choice=toupper(choice);
    while((choice!='Y')&&(choice!='N')){
        std::cout<<"ERROR: Input error"<<std::endl;
        std::cout<<"Would you like to view the user logs (Y/N)\n";
        std::cin>>choice;
        choice=toupper(choice);
    }
    std::cin.ignore(1000,'\n');
    std::string name = lname;
    std::string personalID = std::to_string(pID);
    std::string logName = "var/logs/" + name + "_" + personalID + ".log";
    
    if(choice=='Y'){
        //Print log
        std::fstream logFile;
        logFile.open(logName,std::ios::in);
        std::string line;
        while(true){
            if(!logFile.good())break;
            getline(logFile,line);
            std::cout<<line<<std::endl;
        }
        std::cout<<"Press ENTER to continue...";
        std::cin.get();
        logFile.close();
    }
    
    
    std::cout<<"Enter Course ID: ";
    int cID=sc.nextInt();
    std::map<unsigned int,std::string>::iterator itr=courseNames.find(cID);
    if(itr!=courseNames.end()){
        system_clock::time_point logTimePoint = system_clock::now();
        std::cout<<"Enter Hours: ";
        int HH=sc.nextInt();
        std::cout<<"Enter Minutes: ";
        int MM=sc.nextInt();
        std::cout<<"Enter Seconds: ";
        int SS=sc.nextInt();

        hours h(HH);
        minutes m(MM);
        seconds s(SS);
        
        
        std::string userID = std::to_string(uID);
        std::string fileName = "home/usr/"+name+"_"+userID+".dat";
        std::fstream file;
        file.open(fileName,std::ios::in|std::ios::out|std::ios::binary|std::ios::ate);
        if(!file.is_open()){
            std::cout<<"Cannot open "<<fileName<<std::endl;
            std::this_thread::sleep_for(5s);
        }
        
        Course course;
        std::string title=courseNames[cID] + "-" + std::to_string(cID);
        course.menu.editTitle(title);
        file.seekg(0,std::ios::beg);
        course.findCourse(file,cID);
        course.read(file);
        //We need to get the course clock in status
        seconds totalSecs = duration_cast<seconds>(h) + duration_cast<seconds>(m) + s;
        file.clear();
        file.seekp(0,std::ios::cur);
        course.editTotalTime(file,totalSecs);
        file.close();
        
        //Log admin time edit
        time_t timeLog = system_clock::to_time_t(logTimePoint);
        
        
        std::fstream logFile;
        logFile.open(logName,std::ios::out|std::ios::app);
        logFile<<"ADMIN CHANGE: "<<std::endl;
        logFile<<"Course Number: "<<cID<<std::endl;
        logFile<<ctime(&timeLog);
        logFile<<"Time Adjust: ";
        logFile<<h.count()<<"h "<<m.count()<<"m "<<s.count()<<"s\n";
    }
    else{
        std::cout<<"Course Not Registered\n";
        std::this_thread::sleep_for(2s);
    }
    
}
const StandardUser& StandardUser::operator=(const UserInfo& info){
    email=new char[info.email.length()];
    fname=new char[info.fname.length()];
    lname=new char[info.lname.length()];
    
    this->uID=info.uID;
    this->pID=info.pID;
    this->courseQTY=info.courseQTY;
    this->email=(char*)info.email.c_str();
    this->fname=(char*)info.fname.c_str();
    this->lname=(char*)info.lname.c_str();
    return *this;
}
