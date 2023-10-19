/*
 *  File: main.cpp
 *  Author: Joseph Hernandez
 *  Created on 05/16/2022
 *  Last modified on 05/18/2022
 *  Purpose: Demonstrate bloom filter
 */


#include <iostream>
#include <math.h>

using namespace std;

#include "GeneralHashFunctions.h"

// n = bit-array size
// k = number of hash functions used
// m = number of expected elements to be inserted


int main(int argc, char** argv){
    string value;
    int m = 15;         // bit-array size
    bool array[m];      // bit-array
    int k = 2;          // number of hash functions used
    int n = 0;          // elements to be inserted
    float p;
    
    unsigned int index1;
    unsigned int index2;
    
    
    // Initialize array to be all 0s
    for(int i = 0; i < m; i++){
        array[i] = 0;
    }
    
    // Take in a string value
    cout<< "Enter string, type \"quit\" to end input." << endl;
    getline(cin,value);
    
    while(value != "quit"){
        n++;                                    // Set number of elements
        
        // Hash the value and mod with size
        index1 = RSHash(value) % m;
        index2 = JSHash(value) % m;
        array[index1] = 1;                      // Set array at index1 to 1
        array[index2] = 1;                      // Set array at index2 to 1
        getline(cin, value);
    }

    // Take value to search
    cout << "Enter value to search or \"quit\" to exit: " << endl;
    
    getline(cin, value);
    // Hash search value
    while(value != "quit"){
        index1 = RSHash(value) % m;
        index2 = JSHash(value) % m;
        // Check whether indices are occupied
        if(array[index1] == 1 && array[index2] == 1){
            cout << "Value might be in index!" << endl;
        }
        else{
            cout << "No value exist" << endl;
        }
        
        // Find probability of false positive
        p = pow((1-(exp(-1*((k*n)/(float)m)))),k);
        p *= 100;

        printf("Probability of false positive : %.2f%%\n", p);
        getline(cin, value);
    }
   
    return 0;
}
