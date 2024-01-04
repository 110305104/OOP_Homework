/* Copyright (c) 2005 by The National Chengchi Univ. All Rights Reserved */

#include "SHGame.h"
#include "SHPlayer.h"
#include "SHDealer.h"
#include <iostream>
#include <cstring>
#include <cassert>
#include "AnsiPrint.h"
#include "Card.h"
#include "CardPattern.h"

using namespace std;

// only constructor
// Must be given a valid (initialized) game player and dealer
// Menu is constructed internally to provide basic text interface
// We must use an initialization list here.

 SHGame::SHGame(SHPlayer& shp, SHDealer& shd) 
    : menu(sizeof(menuItems)/sizeof(char*), menuItems),player(shp),dealer(shd)
 {

 }


// one run of the game
// take and process a user action
// show current hands for both players at the end of a run.

int choice=3;//進來預設restart
bool
SHGame::oneRun()
{
        
    //ASK 怎麼在一進來就開好新局-前測試/後測試 用後測試
           
    if(choice==QUIT)
    {
        return false;
    }
    else if(choice==ONE_MORE)
    {
        moreCard();
    }
    else if(choice==RESTART)
    {
        restart();
    }
    else if(choice==GIVE_UP)
    {
        giveUp();
    }

    if(player.getNumCards()>0)
    {
        player.showCards();
        dealer.showCards();
    }
    menu.print();
    choice=menu.getAnswer();
    return true;
}
    



// give the player and dealer one more card
// check if we can do that first.
// and judge who has win the round if the player have 5 cards
void
SHGame::moreCard()
{
    /* ASK 籌碼0時按1跟2要顯示什麼
    if(playerPoint<=0)
    {
        cout<<"Sorry. Game over. No loan here.\n";
        return ;
    }
    else if(dealerPoint<=0)
    {
        cout<<"Sorry. Game over. No loan here.\n";
        return ;
    }
    */

    if(gameOver!=0)
    {
        player.addCard( dealer.giveCard());
        dealer.addCard();
        if(player.getNumCards()==5)
        {
            gameOver=0;
            dealer.openFirstCard();
            Result resultT=dealer.judge(player);//有問題//Fixed
            //Result resultT =WIN;
            if(resultT==WIN)
            {
                playerPoint+=5;
                dealerPoint-=5;
                cout<<"You win. Good Job.(You have "<<playerPoint<<" points, I have "<<dealerPoint<<" points.)\n";
            }
            else if(resultT==TIE)
            {
                cout<<"It's TIE. (You have "<<playerPoint<<" points, I have "<<dealerPoint<<" points.)\n";
            }
            else if(resultT==LOSE)
            {
                playerPoint-=5;
                dealerPoint+=5;
                cout<<"I win. Try again. (You have "<<playerPoint<<" points, I have "<<dealerPoint<<" points.)\n";
            }
        }
    }
    else
    {
        cout<<"Game Over! Please Restart.\n";
        return ;
    }

 

}


// give up this round,
// and you'll lose your credit
// the bet is equivalent to the number of card you keep
void
SHGame::giveUp()
{
    /* ASK 籌碼0時按1跟2要顯示什麼
    if(playerPoint<=0)
    {
        cout<<"Sorry. Game over. No loan here.\n";
        return ;
    }
    else if(dealerPoint<=0)
    {
        cout<<"Sorry. Game over. No loan here.\n";
        return ;
    }
    */
   if(gameOver==0)
    {
        cout<<"Game Over! Please Restart.\n";
        return ;
    }
    //開牌
    dealer.openFirstCard();
    //算籌碼
    playerPoint-=player.getNumCards();
    dealerPoint+=player.getNumCards();
    cout<<"I win. Try again. (You have "<<playerPoint<<" points, I have "<<dealerPoint<<" points.)\n";
    gameOver=0;
    

}


// restart the game by giving each player two new cards
// need to check if any one broke (bankrupt).
void
SHGame::restart()
{
    if(playerPoint<=0)
    {
        cout<<"Sorry. Game over. No loan here.\n";//Dealer Win
        return ;
    }
    else if(dealerPoint<=0)
    {
        cout<<"Sorry. Game over. No loan here.\n";//Player Win
        return ;
    }

    if(gameOver==0)
    {
        reset();
        dealer.shuffle();
        
        dealer.start();
        player.start();
        for(int k=0;k<2;k++)
        {
            player.addCard(dealer.giveCard());
            dealer.addCard();
        }
    }
    else
    {
        cout<<"Game is not over yet. Cannot restart.\n";
        return ;
    }
    


}


void SHGame::start()
{
    //可以直接在.h設好，不用另外開函式
    playerPoint=20;
    dealerPoint=20;
    gameOver=0;
}
void SHGame::reset()
{
    gameOver=1;
}
