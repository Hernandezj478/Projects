/* 
 * File:   main.cpp
 * Author: Joseph Hernandez
 *
 * Created on December 8, 2022, 11:04 AM
 */

#include "BST.hpp"

#include <iostream>

using namespace std;

/*
        Create the following tree
                 50
               /   \
             30    70
            /  \   / \
          20  40  60  90
                     /  \
                    80  100
 */

int main(int argc, char** argv) {
    BST myTree;

    myTree.insert(50);
    myTree.insert(30);
    myTree.insert(20);
    myTree.insert(40);
    myTree.insert(70);
    myTree.insert(60);
    myTree.insert(90);
    myTree.insert(80);
    myTree.insert(100);
    
    cout<<"In Order   :";
    myTree.inOrder();
    cout<<endl;
    cout<<"Pre-Order  :";
    myTree.preOrder();
    cout<<endl;
    cout<<"Post-Order :";
    myTree.postOrder();
    cout<<endl;
    cout<<"Print:\n";
    myTree.print();
    cout<<endl;

    cout<<"Search for a value: ";
    int val;
    cin>>val;
    myTree.search(val)? cout<<val<<" found..." : cout<<val<<" not found...";
    
    return 0;
}
