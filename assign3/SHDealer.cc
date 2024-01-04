/* Copyright (c) 2005 by The National Chengchi Univ. All Rights Reserved */

#include <iostream>
#include <cstring>
#include <cassert>

#include "AnsiPrint.h"
#include "Card.h"
#include "CardPattern.h"
#include "SHDealer.h"
#include "SHPlayer.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


using namespace std;


// constructor
SHDealer::SHDealer()
{
    num=0;
    isOpen=0;
}


// destructor
SHDealer::~SHDealer()
{

}


// distribute a card to the player
Card
SHDealer::giveCard()
{
    Card newCard;
    bool flag=true;
	int id;
    while(flag)
    {
        id=rand()%52;
        if((id/4==0||id/4>=8)&&record[id]==0)
        {
            record[id]=1;
            flag=false;//有發出一張就停
        }
    }
    newCard.setID(id);
    return newCard;
}


// give the dealer a card
void
SHDealer::addCard()
{
    cards[num]=giveCard();
    num++;
}


// determind who has win the game.
// if both of them have the same pattern,
// the one has more total pips wins the game.
Result
SHDealer::judge(SHPlayer& player)
{
    Result theResult;
    if(player.getHandPattern()<getHandPattern()) 
    {
        theResult=WIN;
    }
    else if(player.getHandPattern()> getHandPattern()) 
    {
        theResult=LOSE;
    }
    else 
    {
        if(player.totalPips()>totalPips()) 
        {
            theResult=WIN;
        }
        else if(player.totalPips()<totalPips()) 
        {
            theResult=LOSE;
        }
        else 
        {
            theResult=TIE;
        }
    }
    return theResult;

}


// start a new game(round)
// before starting a new game(round), you should have
// a new deck, and then shuffle it.
// The deck only has pips A, 8, 9, 10, J, Q, K.
void
SHDealer::start()
{
    isOpen=0;
    num=0;
}


// shuffle the deck of cards
void
SHDealer::shuffle()
{
    for(int k=0;k<52;k++)
    {
        record[k]=0;//把之前抽的牌清空
    }
}


// open the dealer's first card
void
SHDealer::openFirstCard()
{
    isOpen=1;
}


// show the dealer's hand to the screen
void
SHDealer::showCards() const
{
	int o;//contral first card

    char str[kCardWidth+1];
    str[kCardWidth]='\0';
    char name[12]="Dealer     ";
	for(int j=0;j<kCardHeight;j++)
	{
        cout<<name[j]<<" ";
		for(int i=0;i<num;i++)
		{
			if (i==0&&isOpen==0) 
			{
				o=13;
			}
			else
			{
				o=cards[i].getPip();
			}

			for(int k=0;k<kCardWidth;k++)
			{
				if(card[o][j][k]=='x')
					str[k]=cardAbbrev[cards[i].getSuit()];
				else
					str[k]=card[o][j][k];
			}

			if(cards[i].getSuit()==1||cards[i].getSuit()==2)
				AnsiPrint(str,red,white,false,false);
			else 
				AnsiPrint(str,black,white,false,false);
			cout<<' ';
		}
		cout<<"\n";
	}
}



//***//

// get the total points of the current hand
int
SHDealer::totalPips() const
{
	int total=0;
	for(int i=0;i<5;i++)
	{
		total+=cards[i].getPip()+1;
        if(cards[i].getPip()==0)
		{
			total+=13;
		}
	}
	return total;
}

// judge what kind of hand type you own
// you need to have 5 cards
HandType
SHDealer::getHandPattern() 
{
	sortCards();
	if(isStraightFlush())
	{
		return STRAIGHT_FLUSH;
	}
	else if(isFourOfAKind())
	{
		return FOUR_OF_A_KIND;
	}
	else if(isFullHouse())
	{
		return FULL_HOUSE;
	}
	else if(isFlush())
	{
		return FLUSH;
	}
	else if(isStraight())
	{
		return STRAIGHT;
	}
	else if(isThreeOfAKind())
	{
		return THREE_OF_A_KIND;
	}
	else if (isTwoPair())
	{
		return TWO_PAIR;
	}
	else if(isOnePair())
	{
		return ONE_PAIR;
	}
	else
	{
		return OTHER;
	}

}

// return the number of cards at hand
int
SHDealer::getNumCards() const
{
	/*
	int k=0,i=0;
	while(cards[i].getID()!=0)
	{
		k++;
	}
	return k;
	*/

	return num;
}




void
SHDealer::sortCards()
{
   
    Card temp;
    for(int i=0;i<num;i++)
    {
        sortedCards[i]=cards[i];
    }

    for(int i=0;i<num-1;i++)
    {
        for(int j=0;j<num-1;j++)
        {
            if(sortedCards[j].getPip() > sortedCards[j+1].getPip() )
            {
                temp=sortedCards[j];
                sortedCards[j]=sortedCards[j+1];
                sortedCards[j+1]=temp;
            }
        }
    }

    for(int i=0;i<num-1;i++)
    {
        for(int j=0;j<num-1;j++)
        {
            if(sortedCards[j].getPip()==sortedCards[j+1].getPip() && sortedCards[j].getSuit() < sortedCards[j+1].getSuit())
            {
                temp=sortedCards[j];
                sortedCards[j]=sortedCards[j+1];
                sortedCards[j+1]=temp;
            }
        }
    }
}





// any five card sequence of same suit
bool 
SHDealer::isStraightFlush() const
{
	if (isStraight()==true&&isFlush()==true)
		return true;
	else
		return false;
}

// four cards of the same pip
bool 
SHDealer::isFourOfAKind() const
{
    // O O O O X
    if( sortedCards[0].getPip() == sortedCards[1].getPip() &&
            sortedCards[2].getPip() == sortedCards[3].getPip() &&
            sortedCards[0].getPip() == sortedCards[2].getPip() )
        return true;
    // X O O O O
    if( sortedCards[1].getPip() == sortedCards[2].getPip() &&
            sortedCards[3].getPip() == sortedCards[4].getPip() &&
            sortedCards[1].getPip() == sortedCards[3].getPip() )
        return true;

    return false;
}

// three of a kind combined with a pair
bool 
SHDealer::isFullHouse() const
{
    // O O O X X
    if( sortedCards[0].getPip() == sortedCards[1].getPip() &&
            sortedCards[1].getPip() == sortedCards[2].getPip() &&
            sortedCards[3].getPip() == sortedCards[4].getPip() )
        return true;
    // X X X O O
    if( sortedCards[0].getPip() == sortedCards[1].getPip() &&
            sortedCards[2].getPip() == sortedCards[3].getPip() &&
            sortedCards[3].getPip() == sortedCards[4].getPip() )
        return true;

    return false;
}

// five cards of the same suit
bool
SHDealer::isFlush() const
{
    for( int i = 0; i < kMaxCards - 1; i++ )
        if( sortedCards[i].getSuit() != sortedCards[i+1].getSuit() )
            return false;

    return true;
}

// five cards in sequence
bool 
SHDealer::isStraight() const
{
    for( int i = 0; i < kMaxCards - 1; i++ )
        if( sortedCards[i].getPip() + 1 != sortedCards[i+1].getPip() )
            return false;

    return true;
}

// three cards of the same pip
bool 
SHDealer::isThreeOfAKind() const
{
    for( int i = 0; i < kMaxCards - 2; i++ )
        if( sortedCards[i].getPip() == sortedCards[i+1].getPip() &&
                sortedCards[i].getPip() == sortedCards[i+2].getPip() )
            return true;

    return false;
}

// two cards of one pip, two cards of another pip
bool 
SHDealer::isTwoPair() const
{
    // O O @ @ X
    if( sortedCards[0].getPip() == sortedCards[1].getPip() &&
            sortedCards[2].getPip() == sortedCards[3].getPip() )
        return true;
    // O O X @ @
    if( sortedCards[0].getPip() == sortedCards[1].getPip() &&
            sortedCards[3].getPip() == sortedCards[4].getPip() )
        return true;
    // X O O @ @
    if( sortedCards[1].getPip() == sortedCards[2].getPip() &&
            sortedCards[3].getPip() == sortedCards[4].getPip() )
        return true;

    return false;
}

// two cards of one pip
bool 
SHDealer::isOnePair() const
{
    for( int i = 0; i < kMaxCards - 1; i++ )
        if( sortedCards[i].getPip() == sortedCards[i+1].getPip() )
            return true;

    return false;
}
