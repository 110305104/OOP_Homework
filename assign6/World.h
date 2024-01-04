#ifndef _WORLD_H
#define _WORLD_H

#include<iostream>
using namespace std;

#include"RandomNum.h"
#include"Creature.h"
#include "Goat.h"
#include "Grass.h"

class Creature;

class World{
    public:
        World(int n,int s,RandomNum &number);
        ~World();
        bool outOfScope(int x,int y);
        bool null(int x,int y);
        void mainLoop(int i);
        void print();
        void start();
        void oneday();
        void reset();
        int getSeed();
        void babyGrass(int x,int y);
        void babyGoat(int x,int y);
        int what(int x,int y);
        void eatGrass(int x,int y);
        void moveGoat(int tx,int ty,int x,int y);
        int rannum[20][35];
    private:
        int seed;
        int pass;
        int interval;
        int day;
    public:
        Creature *world[20][35];
        RandomNum &num;
};
#endif
