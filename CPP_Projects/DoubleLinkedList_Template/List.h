/* 
 * File:   List.h
 * Author: Joseph Hernandez
 *
 * Created on October 13, 2022, 10:30 PM
 */

#include <iostream>    //Input/Output Library
#include <cstdlib>     //NULL pointer
#include <iomanip>     //setw()
using namespace std;   //Library Name-space

#ifndef LIST_H
#define LIST_H

template<class T>
struct Link{
        T data;         //Some type of data
        Link<T> *lnkNext;  //Next Link in the chain
        Link<T> *lnkPrev;  //Previous link in the chain
        Link(){}
        Link(T val){
            data=val;
            lnkNext=NULL;
            lnkPrev=NULL;
        }
};

template<class T>
class List{
    private:
        Link<T>* head;
        int size;

    public:
        List();
        List(const List&);
        void prntLst();
        void destroy();
        void fillList(int);
        void pshFrnt(T);        //Push a link to the front
        void pshBack(T);        //Push a link to the end
        void popFrnt();         //Pull/pop a link from the front
        void popBack();         //Pull/pop a link from the back
        
        Link<T> *at(int);
        void replace(int,T);
        void remove(int);
        void sort();
        int search(T);
        
        
        T operator[](const int&);
};

template<class T>
List<T>::List(){
    //Initialize head ptr
    head=nullptr;
}

template<class T>
List<T>::List(const List &val){
    //Check if the list that is being passed in has a NULL head node
    Link<T> *headPtr = val.head;
    if(headPtr==NULL){
            //If head is NULL, no elements exist and we should assign the head/tail as NULL
            head=NULL;
    }
    else{
            // Set up the first link in new list and copy contents
            Link<T> *copy = new Link<T>;
            head=copy;
            copy->lnkPrev=NULL;
            copy->lnkNext=NULL;
            copy->data=headPtr->data;

            //Set up headPtr for while loop
            headPtr=headPtr->lnkNext;

            while(headPtr!=NULL){
                    copy->lnkNext=new Link<T>;
                    copy->lnkNext->lnkPrev=copy;
                    copy->lnkNext->lnkNext=NULL;
                    // Move to new link
                    copy=copy->lnkNext;
                    copy->data=headPtr->data;

                    //Move cursor to next link
                    headPtr=headPtr->lnkNext;
            }
    }
}

template<class T>
void List<T>::fillList(int n){
    n<=0 ? 1 : n;
    int count=0;
    while(count<n){
        this->pshBack((rand()%94)+33);
        count++;
    }
}

template<class T>
void List<T>::prntLst(){
    Link<T> *ptr=head;
    int count=0;
    int perLine=10;
    while(ptr!=NULL){
        if(count%perLine==0 && count!=0)cout<<endl;
        cout<<setw(3)<<ptr->data<<" ";
        ptr=ptr->lnkNext;
        count++;
    }
    cout<<endl;
}

template<class T>
void List<T>::destroy(){
    Link<T> *front=head;
    while(front!=NULL){
        Link<T> *temp=front;
        front=front->lnkNext;
        delete temp;
    }
}

template<class T>
void List<T>::pshFrnt(T n){
    Link<T> *link=new Link<T>(n);
    Link<T> *ptr=head;
    if(head!=NULL){
        ptr->lnkPrev=link;
        link->lnkNext=ptr;
        head=link;
    }
    else{
        link->lnkNext=NULL;
        link->lnkPrev=NULL;
        this->head=new Link<T>;
        head=link;
    }
}

template<class T>
void List<T>::pshBack(T n){
    Link<T> *link=new Link<T>(n);
    Link<T> *ptr=head;
    
    if(ptr!=NULL){
        while(ptr->lnkNext!=NULL){
            ptr=ptr->lnkNext;
        }
        ptr->lnkNext=link;
        link->lnkPrev=ptr;
    }
    else{
        head=new Link<T>;
        head=link;
        head->lnkNext=NULL;
        head->lnkPrev=NULL;
    }
}

template<class T>
void List<T>::popFrnt(){
    Link<T> *temp;
    
    //Empty list, do nothing
    if(head==NULL)return;
    
    //Assign temporary Link to head
    Link<T> *ptr=head;
    if(ptr->lnkNext==NULL){
        temp=head;
        head->lnkNext=NULL;
        head->lnkPrev=NULL;
    }
    else{
        temp=ptr;
        ptr=ptr->lnkNext;
        ptr->lnkPrev=NULL;
        head=ptr;
    }
    //Delete previous link
    delete temp;
}

template<class T>
void List<T>::popBack(){
    Link<T> *temp;
    
    //Empty list, do nothing
    if(head==NULL)return;
    
    Link<T> *ptr=head;
    if(ptr->lnkNext==NULL){
        temp=head;
        head->lnkNext=NULL;
        head->lnkPrev=NULL;
    }
    else{
        while(ptr->lnkNext!=NULL){
            ptr=ptr->lnkNext;
        }
        temp=ptr;
        ptr=ptr->lnkPrev;
        ptr->lnkNext=NULL;
    }
    delete temp;
}

template<class T>
Link<T>* List<T>::at(int index){
    Link<T> *front=head;
    int count=0;
    while(front!=NULL && count!=index){
        front=front->lnkNext;
        count++;
    }
    return front;
}

template<class T>
void List<T>::replace(int indx, T val){
    Link<T> *front=head;
    int count=0;
    while(front!=NULL && count!=indx){
        front=front->lnkNext;
        count++;
    }
    front->data=val;
}

template<class T>
void List<T>::remove(int indx){
    Link<T> *ptr=head;
    int count=0;
   
    while(count<=indx){
        ptr=ptr->lnkNext;
        count++;
    }
    //Once link is found, delete link
    ptr->lnkPrev->lnkNext=ptr->lnkNext;
    ptr->lnkNext->lnkPrev=ptr->lnkPrev;
    delete ptr;
}

template<class T>
void List<T>::sort(){
    Link<T> *ptr = head;
    Link<T> *nextPtr;
    while(ptr!=NULL){
        nextPtr=ptr->lnkNext;
        while(nextPtr!=NULL){
            if(ptr->data > nextPtr->data){
                T temp = ptr->data;
                ptr->data=nextPtr->data;
                nextPtr->data=temp;
            }
            nextPtr=nextPtr->lnkNext;
        }
        ptr=ptr->lnkNext;
    }
}

template<class T>
int List<T>::search(T val){
    Link<T> *srch = head;
    int count=0;
    if(srch->data==val)return count;
    else{
        while(srch->lnkNext!=NULL){
            srch=srch->lnkNext;
            count++;
            if(srch->data==val){
                this->pshFrnt(val);
                this->remove(count);
                return count;
            }
        }
    }
    return -1;
}

template<class T>
T List<T>::operator [](const int &i){
    Link<T> *output=head;
    int count = 0;
    while(output->lnkNext!=NULL && count!=i){
        output=output->lnkNext;
        count++;
    }
    return output->data;
}

#endif /* LIST_H */

