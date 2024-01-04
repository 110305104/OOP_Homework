#ifndef _GRASS_H
#define _GRASS_H

#include<iostream>
#include"World.h"
#include "Creature.h"

using namespace std;

class Creature;
class World;
//Grass is a Creature
class Grass:public Creature{
    public:
    Grass( World &ifate, int x, int y);
    ~Grass();
    void print() const;
    bool addAge();
    void baby();
    int what();

    private:
    World &fate;

};

#endif
