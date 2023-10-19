/*
 * File: Course.cpp
 * Author: Joseph Hernandez
 * 
 * Created on April 15, 2023, 2:07PM
 */


#include "Course.hpp"


Course::Course(){
    initMenu();
}
void Course::courseSession(std::fstream& file){

    system_clock::time_point timePoint;
    long cursor=file.tellg();
    file.seekg(0,std::ios::cur);
    read(file);
    file.read(reinterpret_cast<char*>(&timePoint),sizeof(system_clock::time_point));
    file.seekg(cursor,std::ios::beg);
    
}
void Course::initMenu(){
    //Set title
    std::string title = "Course " + std::to_string(courseNo) + ":";
    menu.editTitle(title);
    //Option 1: Clock in
    std::string op = "Clock In";
    menu.addOption(op);
    //Option 2: Clock out
    op = "Clock Out";
    menu.addOption(op);
    //Option 3: Back
    op = "Back (Previous Menu)";
    menu.addOption(op);
}
void Course::displayMenu(){
    
    //Display Title
    std::cout<<menu.getTitle()<<"\n";
    //Display Total Time
    hours h = duration_cast<hours>(totalTime.SS);
    minutes m = duration_cast<minutes>(totalTime.SS);
    seconds s = totalTime.SS;
    std::cout<<h.count()<<"h "<<m.count()%60<<"m "<<s.count()%60<<"s\n\n";
    //Loop to display all options
    int size = menu.size();
    for(int i=0;i<size;i++){
        std::cout<<i+1<<". "<<menu[i]<<std::endl;
    }
}
void Course::regCourse(std::fstream& file,unsigned int cID){
      
    //Get courseNo
    courseNo = cID;
    //Initialize total time
    seconds s(0);
    totalTime.SS = s;
    std::cout<<s.count()<<"s\n";
    //Set clockIn status to false
    clockIn=false;
    
    //Clear the eofbit
    file.clear();
    //Assuming we do not have a duplicate course registered and saved in 
    //      [lastname]_[personalID].dat, we will be writing to the end of the file
    //file.seekp(0,std::ios::end);
    file.seekp(0,std::ios::cur);
    file.write(reinterpret_cast<char*>(&courseNo),sizeof(unsigned int));
    write(file);
    //Save random time point to fill 
    std::chrono::system_clock::time_point rndTime = std::chrono::system_clock::now();
    file.write(reinterpret_cast<char*>(&rndTime),sizeof(std::chrono::system_clock::time_point));
    file.seekp(0,std::ios::beg);
}
void Course::printTime(std::fstream& file){
    
    //Pull information from file, then display the time
    long cursor = file.tellg();
    read(file);
    file.seekg(cursor,std::ios::beg);
    
    hours h = duration_cast<hours>(totalTime.SS);
    minutes m = duration_cast<minutes>(totalTime.SS);
    seconds s = totalTime.SS;
    
    std::cout<<h.count()<<"h "<<m.count()%60<<"m "<<s.count()%60<<"s\n";
}
void Course::calcTime(std::fstream& file){
    //This will be calculated after session has been updated with the current
    //time. If the user has not punched out. The total time will be at 0.
    //Add the session time and add to the time pulled from the file [personalID].dat
    long cursor = file.tellg();
    std::chrono::seconds time=session.getTimeSec();
    read(file);
    totalTime.SS += time;
    file.seekp(cursor,std::ios::beg);
    write(file);
    file.seekg(cursor,std::ios::beg);
}
bool Course::punchIn(std::fstream& file){
    long cursor=file.tellg();
    //We need to store the current position in the file to return the file 
    //pointer back to the previous position when starting this function.
    //This is to make read/write easier since we will always be pointing right
    //after the course number in the file.
    //The file format is -> [courseNo][clockIn][totalTime][start] - 108-bits total
   
    //Check if user is already clocked in
    if(!punchCheck(file)){
        session.punchIn();
        std::chrono::seconds tmp = session.getTimeSec();
        
        clockIn=true;
        file.seekp(0,std::ios::cur);
        long pos=file.tellg();
        write(file);
        std::chrono::system_clock::time_point timePoint=session.getSessionStart();
        file.write(reinterpret_cast<char*>(&timePoint),
                sizeof(std::chrono::system_clock::time_point));
        file.seekg(cursor,std::ios::beg);
    }
    else{
        std::cout<<"Already Clocked In\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        //Move the file pointer to the correct pos to read in start time
        long pos=cursor+sizeof(bool)+sizeof(std::chrono::seconds);
        file.seekg(pos,std::ios::beg);
        session.setSessionStart(file);
        //Move file pointer back to beg of segment block
        file.seekg(cursor,std::ios::beg);
    }
    return clockIn;
}
bool Course::punchOut(std::fstream& file){
    //We need to store the current position in the file to return the file 
    //pointer back to the previous position when starting this function.
    long cursor=file.tellg();
    //Check if clocked in
    if(punchCheck(file)){
        //Read in the punch time from the file
        long pos = cursor+(sizeof(bool)+sizeof(std::chrono::seconds));
        file.seekg(pos,std::ios::beg);
        session.setSessionStart(file);
        file.seekg(cursor,std::ios::beg);
        session.punchOut();
        std::chrono::seconds tmp(session.getTimeSec());
        clockIn=false;
        file.seekp(0,std::ios::cur);
        write(file);
        system_clock::time_point timePoint=session.getSessionStart();
        file.write(reinterpret_cast<char*>(&timePoint),
                sizeof(system_clock::time_point));
        file.seekg(cursor,std::ios::beg);
        calcTime(file);
    }
    else{
        std::cout<<"Already Clocked Out\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    return true;
}
void Course::read(std::fstream& file){
    //system_clock::time_point tPoint;
    
    file.seekg(0,std::ios::cur);
    file.read(reinterpret_cast<char*>(&clockIn),sizeof(bool));
    file.read(reinterpret_cast<char*>(&totalTime.SS),sizeof(seconds));
}
void Course::write(std::fstream& file){
    //Save clock in state, total time (in seconds)
    file.seekp(0,std::ios::cur);
    file.write(reinterpret_cast<char*>(&clockIn),sizeof(bool));
    file.write(reinterpret_cast<char*>(&totalTime.SS),sizeof(seconds));
    //Add start time out of write function
}
bool Course::punchCheck(std::fstream& file){
    //File format -> [courseNo][clockIn][TotalTime][clock start]
    long cursor = file.tellg();
    bool punch;
    file.read(reinterpret_cast<char*>(&punch),sizeof(bool));
    file.seekg(cursor,std::ios::beg);
    return punch;
}
void Course::logSessionTime(std::fstream& file){
    //This is assuming we have already opened up the log file and will append
    //to the end of the log
    
    hours h = duration_cast<hours>(session.getTimeSec());
    minutes m = duration_cast<minutes>(session.getTimeSec());
    seconds s = session.getTimeSec();
    
    time_t start = system_clock::to_time_t(session.getSessionStart());
    time_t end = system_clock::to_time_t(session.getSessionEnd());
    
    file<<"Course No.: " << courseNo<<"\n";
    file<<ctime(&start);
    file<<ctime(&end);
    file<<h.count()<<"h "<<m.count()%60<<"m "<<s.count()%60<<"s\n";
}
bool Course::findCourse(std::fstream& file,unsigned int cID){
    //File format -> [courseNo][clockInSate][totalTime][startTime]
    long cursor=0L;
    file.seekg(0,std::ios::end);
    long size = file.tellg();
    unsigned int in;
    while(cursor<size){
        //Iterate through file until we find the correct course
        file.seekg(cursor,std::ios::beg);
        file.read(reinterpret_cast<char*>(&in),sizeof(unsigned int));
        if(in!=cID){
            //Move to the next block of memory
            cursor+=(sizeof(int)+sizeof(bool)+sizeof(std::chrono::seconds)+
                    sizeof(std::chrono::system_clock::time_point));
        }
        else{
            //Save the course ID
            courseNo=in;
            return true;
        }
    }
    return false;
}
void Course::editTotalTime(std::fstream& file,seconds totalSecs){
    totalTime.SS=totalSecs;
    clockIn=false;
    
    //We know that the file will be at the end of the course info block, so we 
    //need to skip back two chunks to set to the total time in the file and status: 
    // file format ->  [course ID][clockInStatus][totalTime][time point]
    //                 [ 32-bits ][   32-bits   ][ 64-bits ]
    long cursor=sizeof(seconds)+sizeof(bool);
    file.seekp(-(cursor),std::ios::cur);
    std::cout<<"pos: "<<file.tellp()<<std::endl;
    std::this_thread::sleep_for(seconds(2));
    write(file);
    file.seekp(0,std::ios::cur);
    system_clock::time_point currTime=system_clock::now();
    file.write(reinterpret_cast<char*>(&currTime),sizeof(system_clock::time_point));
}