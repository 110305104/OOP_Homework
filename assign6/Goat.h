#ifndef _GOAT_H
#define _GOAT_H

#include<iostream>
#include"World.h"
#include "Creature.h"

using namespace std;

//Goat is a Creature
class Creature;
class World;

class Goat:public Creature
{
    public:
        Goat(World &ifate, int x,int y);
        ~Goat(){}

        void move();
        void back();
        bool hungry();

        void print() const{
            cout<<'X';
        }

        bool addAge();
        void baby();

        int what(){
            return name;
        }

    private:
        int d;
        World &fate;
};
#endif