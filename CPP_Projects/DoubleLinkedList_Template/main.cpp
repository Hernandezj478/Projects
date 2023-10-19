/*
    Author: Joseph Hernandez
    Date:   October 13th, 2022  10:45PM
    Purpose:Linked List Demonstration
 */

//System Libraries
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

//User Libraries
#include "List.h"

//Global/Universal Constants -- No Global Variables
//Science, Math, Conversions, Higher Dimensioned constants only

//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv) {
    //Set the Random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare variables
    List<int> listInt;
    List<char> listChar;
    List<float> listFloat;
    List<string> listStng;

    listChar.fillList(200);
    
    int n=100;

    char number;
    cout<<"Search for any character: ";
    cin>>number;
    int found = listChar.search(number);
    
    (found != -1) ? (cout << endl << number << " was found at link "
            <<found+1<<" in the list...\n"
            "Moving to the front of the list."<<endl) 
            : (cout<<number<<" was not found"<<endl);
    
    listChar.prntLst();
    
    cout<<"Sorting list..."<<endl;
    listChar.sort();
    found=listChar.search(number);
    listChar.prntLst();
    
    //Delete all the allocated memory     
    listInt.destroy();
    listChar.destroy();
    listFloat.destroy();
    listStng.destroy();
    
    //Exit stage right
    return 0;
}





