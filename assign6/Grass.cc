#include<iostream>

#include"Grass.h"
#include"RandomNum.h"

using namespace std;

Grass::Grass( World &ifate, int x,int y):fate(ifate)
{
    this->x=x;
    this->y=y;
        age=0;
        name=1;
}

Grass::~Grass()
{
}

int Grass::what()
{
    return name;
}

void Grass::print() const
{
    cout<<'I';
}

bool Grass::addAge()
{
    age++;
    if( age==6 ) return false;
    if(age>=3 && age<=5) baby();
    ymove();
    return true;
}

void Grass::baby()
{
    int hold = fate.rannum[x][y];
    int tx,ty;
    if(hold==0){ //上
        tx=x-1,ty=y;
    }
    else if(hold==1){ //下
        tx=x+1,ty=y;
    }
    else if(hold==2){ //左
        tx=x,ty=y-1;
    }
    else if(hold==3){ //右
        tx=x,ty=y+1;
    }
    if( fate.outOfScope(tx,ty)==false && fate.null(tx,ty)==true)
        fate.babyGrass(tx,ty);
}
                  