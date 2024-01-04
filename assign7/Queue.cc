#include "Queue.h"
#include "AnsiPrint.h"
#include <iostream>
using namespace std;

bool isEmpty();

template<typename Type>
Queue<Type>::Queue()
{
    sptr=NULL;
    eptr=NULL;
    
    try
    {
        if((sptr!=NULL&&eptr==NULL)||(sptr==NULL&&eptr!=NULL))
        {
            throw "Internal error";
        }
    }
    catch(const char *error)
    {
        AnsiPrint(error,red,yellow,true,false);
        cout<<endl;
    }
}


template<typename Type>
Queue<Type>::Queue(const Queue &src)
{
    sptr=NULL;
    eptr=NULL;
    
    try
    {
        if((sptr!=NULL&&eptr==NULL)||(sptr==NULL&&eptr!=NULL))
        {
            throw "Internal error";
        }
    }
    catch(const char *error)
    {
        AnsiPrint(error,red,yellow,true,false);
        cout<<endl;
    }

    Node<Type> *cptr=src.sptr;
    while(cptr!=NULL)
    {
        enqueue(cptr->val);
        cptr=cptr->nptr;
    }



}

template<typename Type>
Queue<Type>::~Queue()
{
    while(isEmpty()==false)
    {
        dequeue();
    }
    delete sptr;
    delete eptr;
}


template<typename Type>
void Queue<Type>::enqueue(Type n)
{
    try
    {
        Node<Type> *newptr = new Node<Type>;
        if( newptr==NULL) throw "Can not allocate more memory";

        newptr->val=n;
        newptr->nptr=NULL;
        newptr->pptr=NULL;

        if(isEmpty()==true)
        {
            sptr=newptr;
            eptr=newptr;
        }
        else
        {
            eptr->nptr=newptr;
            newptr->pptr=eptr;
            eptr=eptr->nptr;
        }

    }
    catch(const char *error)
    {
        AnsiPrint(error,red,yellow,true,false);
        cout<<endl;
    }



}


template<typename Type>

void Queue<Type>::dequeue()
{
    try
    {
        if(sptr==NULL) throw "Attemp to dequeue empty queue";
        if(sptr == eptr)
        {
            Node<Type> *hptr = sptr;
            delete hptr;
            sptr=NULL;
            eptr=NULL;
        }
        else
        {
            Node<Type> *hptr = eptr;
            eptr = eptr->pptr;
            eptr->nptr = NULL;
            delete hptr;
        }
    }
    catch(char const *error)
    {
        AnsiPrint(error,red,yellow,true,false);
        cout<<endl;
    }
}


template<typename Type>
void Queue<Type>::print()
{
    Node<Type> *cptr=sptr;
    while(cptr!=NULL)
    {
        cout<<cptr->val<<endl;
        cptr=cptr->nptr;
    }
}

template<typename Type>
Queue<Type> &Queue<Type>::operator=(const Queue &src)
{
    while(isEmpty()==false)
    {
        dequeue();
    }
    Node<Type> *cptr=src.sptr;
    while(cptr!=NULL)
    {
        enqueue(cptr->val);
        cptr=cptr->nptr;
    }
    return *this;
}




template<typename Type>
bool Queue<Type>::isEmpty()
{
    if(sptr==NULL&&eptr==NULL)
    {
        return true;
    }
    return false;

}