#include<iostream>
#include<stdlib.h>
#include<time.h>
#include"Goat.h"
#include"RandomNum.h"
using namespace std;
Goat::Goat( World &ifate, int x,int y ):fate(ifate)
{
    this->x=x;
    this->y=y;
    foodpoint=20;
    age=0;
    name=2;
    d=-1;
}

/*
int Goat::what()
{
    return name;
}

void Goat::print() const
{
    cout<<'X';
}
*/

bool Goat::addAge(){
    age++;
    foodpoint--;
    if(age>=70) return false;
    else if(age>=50 && age<=55) {
        baby();
        if(hungry()==true) return false;
    }
    else {
        move();
        if(hungry()==true ) {
            if(d!=-1)back();
            return false;
        }
    }
    ymove();
    return true;
}

void Goat::baby(){
    int randDir=fate.rannum[x][y];
    int tx,ty;
    if(randDir==0){ //上
        tx=x-1,ty=y;
    }
    else if(randDir==1){ //下
        tx=x+1,ty=y;
    }
    else if(randDir==2){ //左
        tx=x,ty=y-1;
    }
    else if(randDir==3){ //右
        tx=x,ty=y+1;
    }
    if( fate.outOfScope(tx,ty)==false ){
        if( fate.null(tx,ty)==true ) fate.babyGoat(tx,ty);
        else{
            if( fate.what(tx,ty)==1 ) {
                foodpoint+=5;
                fate.eatGrass(tx,ty);
                fate.babyGoat(tx,ty);
            }
        }
    }
}

void Goat::move(){
    int randDir=fate.rannum[x][y];
    int tx,ty;
    if(randDir==0){ //上
        tx=x-1,ty=y;
    }
    else if(randDir==1){ //下
        tx=x+1,ty=y;
    }
    else if(randDir==2){ //左
        tx=x,ty=y-1;
    }
    else if(randDir==3){ //右
        tx=x,ty=y+1;
    }
    if( fate.outOfScope(tx,ty)==false ){
        if( fate.null(tx,ty)==true ) {
            d=randDir;
            fate.world[tx][ty]=fate.world[x][y];
            fate.world[x][y]=NULL;
            x=tx,y=ty;
        }
        else{
            if( fate.what(tx,ty)==1 ){//is grass
                foodpoint+=5;
                fate.eatGrass(tx,ty);
                fate.world[tx][ty]=fate.world[x][y];
                fate.world[x][y]=NULL;//
                x=tx,y=ty;
                d=randDir;
            }
            else d=-1;
        }
    }
    else d=-1;
}

void Goat::back(){
    int tx,ty;
    if(d==0){//up->down
        tx=x+1,ty=y;
    }
    else if(d==1){//down->up
        tx=x-1,ty=y;
    }
    else if(d==2){//l->r
        tx=x,ty=y+1;
    }
    else if(d==3){//r->l
        tx=x,ty=y-1;
    }
    fate.world[tx][ty]=fate.world[x][y];
    fate.world[x][y]=NULL;
    x=tx,y=ty;
    d=-1;
}

bool Goat::hungry(){
    if(foodpoint==0) return true;
    else return false;
}
