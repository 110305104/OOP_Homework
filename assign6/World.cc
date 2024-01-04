#include<iostream>

#include"Creature.h"
#include"Grass.h"
#include"Goat.h"
#include"RandomNum.h"
#include"World.h"
class RandomNum;
class Creature;

using namespace std;
World::World(int n,int s,RandomNum &number)
    :num(number)
{
    pass=n;
    seed=s;
    day=0;
    for(int i=0;i<20;i++){
        for(int j=0;j<35;j++){
            world[i][j]=NULL;
        }
    }
    start();
}

World::~World()
{
}

void World::start()
{
    int x,y,hold=0;
    while(hold!=5){ //5 goat
        x=num.getRandomNum(0,19);
        y=num.getRandomNum(0,34);
        if( world[x][y]==NULL ){
            world[x][y]=new Goat( (*this),x,y );
            hold++;
        }
    }
    hold=0;
    while(hold!=10){ //10 grass
        x=num.getRandomNum(0,19);
        y=num.getRandomNum(0,34);
        if( world[x][y]==NULL ){
            world[x][y]=new Grass( (*this),x,y);
            hold++;
        }
    }
}

void World::mainLoop(int i)
{
    if(i<=0){
        interval=1;
    }
    else{
        interval=i;
    }
    
    day=1;
    print();
    while( day<pass ){
        day++;
        oneday();
        if( (day-1) % interval ==0) print();
    }
}

int World::getSeed()
{
    return seed;
}

void World::print()
{
    cout<<' ';
    for(int i=0;i<35;i++){
        cout<<' '<<i%10;
    }
    cout<<endl;
    for(int i=0;i<20;i++){
        cout<<i%10;
        for(int j=0;j<35;j++){
            if(world[i][j]==NULL) cout<<' '<<' ';
            else {
                cout<<' ';
                world[i][j]->print();
            }
        }
        cout<<endl;
    }
    cout<<"------------------------------------------------------------------------"<<endl;
}

void World::oneday()
{
    reset();
    for(int i=0;i<20;i++){
        for(int j=0;j<35;j++){
            if(world[i][j]!=NULL ){
                if( world[i][j]->getMove()==0 ){
                    if( world[i][j]->addAge() ==false ) {
                        Creature *ptr=world[i][j];
                        world[i][j]=NULL;
                        delete ptr;
                    }
                }
            }
        }
    }
}

void World::reset()
{
    for(int i=0;i<20;i++){
        for(int j=0;j<35;j++){
            if(world[i][j]!=NULL) world[i][j]->dontmove();
            rannum[i][j]=num.getRandomNum(0,3);
        }
    }
}

bool World::outOfScope(int x,int y)
{
    if( x>=0 && x<20 && y>=0 && y<35 ) return false;
    else return true;
}

bool World::null(int x,int y)
{
    if(world[x][y]==NULL) return true;
    else return false;
}

void World::babyGrass(int x,int y)
{
    world[x][y] = new Grass( *this,x,y);
    world[x][y]->ymove();
}

void World::babyGoat(int x,int y)
{
    world[x][y] = new Goat( *this,x,y);
    world[x][y]->ymove();
}

void World::eatGrass(int x,int y)
{
    Creature *ptr=world[x][y];
    world[x][y]=NULL;
    delete ptr;
}

int World::what(int x,int y)
{
    return world[x][y]->what();
}

void World::moveGoat(int tx,int ty,int x,int y)
{
    Creature * ptr=world[x][y];
    world[tx][ty]=world[x][y];
    world[x][y]=NULL;
    delete ptr;
}
                                                                                                                                      