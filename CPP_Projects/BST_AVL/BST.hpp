/* 
 * File:   BST.hpp
 * Author: Joseph Hernandez
 *
 * Created on December 8, 2022, 1:12 PM
 */

#ifndef BST_HPP
#define BST_HPP

#include "BSTNode.hpp"

#include <iostream>

using namespace std;

class BST{
public:
    BST();

    void insert(int);
    void deleteNode(int);
    
    void printLevel(int);
    void print();
    
    void inOrder();
    void preOrder();
    void postOrder();
    
    bool search(int);
    
private:
    BSTNode *root;
    
    BSTNode *searchVal(BSTNode*,int);
    
    BSTNode *newNode(int);
    BSTNode *insertNode(BSTNode*,int);
    BSTNode *deleteNode(BSTNode*,int);
    
    BSTNode* minVal(BSTNode*);
    
    int height(BSTNode*);
    
    void printLevel(BSTNode*,int);
    void print(BSTNode *);
    
    void printLeaf(BSTNode*);
    void printParent(BSTNode*);
    
    void inOrder(BSTNode*);
    void preOrder(BSTNode*);
    void postOrder(BSTNode*);

};

#endif /* BST_HPP */

