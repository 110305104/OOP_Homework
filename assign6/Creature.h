#ifndef _CREATURE_H
#define _CREATURE_H
#include <iostream>
using namespace std;

class Creature{
    public:
    Creature(){
    moven=0;
    age=0;
    }

    virtual ~Creature(){}

    virtual void print() const=0;
    virtual bool addAge()=0;

    void ymove(){
    moven=1;
    }

    void dontmove(){
        moven=0;
    }

    virtual void baby()=0;

    virtual int getMove(){
    return moven;
    }

    virtual int what()=0;

    protected:
    int x;
    int y;
    int name;
    int age;
    int foodpoint;

    private:
    int moven;


};

#endif