/* Copyright (c) 2005 by The National Chengchi Univ. All Rights Reserved */

#include <iostream>
#include <cstring>
#include <cassert>
#include "AnsiPrint.h"
#include "Card.h"
#include "CardPattern.h"
#include "SHPlayer.h"


using namespace std;

const char* HandTypeName[9] = {
    "Straight flush",
    "Four of a kind",
    "Full house",
    "Flush",
    "Straight",
    "Three of a kind",
    "Two pair",
    "One pair",
    "Other"
};

// constructor
SHPlayer::SHPlayer(const char* name)
{
	//num=0;
	//isOpen=0;
	//strcpy(name,playerName);
}

// initialize the number of cards to 0
void
SHPlayer::start()
{
	num=0;
	isOpen=1;
	/*
	for(int i=0;i<52;i++)
	{
		mycards[i]=0;
	}
	*/
}

// add a new card to the current hand
// need to protect the array from overflowing
void SHPlayer::addCard(Card newCard)
{
	if(num==kMaxCards)
		return;	//protect from overflowing
	cards[num]=newCard;
	num++;
}

// open the first card so it faces up
void
SHPlayer::openFirstCard()
{
	isOpen=1;
}

//Suit



// print the current hand to the screen graphically
void
SHPlayer::showCards() const
{
	int o;//contral first card
	
    char str[kCardWidth+1];
	str[kCardWidth]='\0';
    char name[12]="Player     ";
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

// get the total points of the current hand
int
SHPlayer::totalPips() const
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
SHPlayer::getHandPattern() 
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
SHPlayer::getNumCards() const
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
SHPlayer::sortCards()
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
SHPlayer::isStraightFlush() const
{
	if (isStraight()==true&&isFlush()==true)
		return true;
	else
		return false;
}

// four cards of the same pip
bool 
SHPlayer::isFourOfAKind() const
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
SHPlayer::isFullHouse() const
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
SHPlayer::isFlush() const
{
    for( int i = 0; i < kMaxCards - 1; i++ )
        if( sortedCards[i].getSuit() != sortedCards[i+1].getSuit() )
            return false;

    return true;
}

// five cards in sequence
bool 
SHPlayer::isStraight() const
{
    for( int i = 0; i < kMaxCards - 1; i++ )
        if( sortedCards[i].getPip() + 1 != sortedCards[i+1].getPip() )
            return false;

    return true;
}

// three cards of the same pip
bool 
SHPlayer::isThreeOfAKind() const
{
    for( int i = 0; i < kMaxCards - 2; i++ )
        if( sortedCards[i].getPip() == sortedCards[i+1].getPip() &&
                sortedCards[i].getPip() == sortedCards[i+2].getPip() )
            return true;

    return false;
}

// two cards of one pip, two cards of another pip
bool 
SHPlayer::isTwoPair() const
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
SHPlayer::isOnePair() const
{
    for( int i = 0; i < kMaxCards - 1; i++ )
        if( sortedCards[i].getPip() == sortedCards[i+1].getPip() )
            return true;

    return false;
}

void outputPattern(HandType pattern)
{
	if(pattern == STRAIGHT_FLUSH)
	{
		cout<<"It's Straight flush\n";
	}
	else if(pattern==FOUR_OF_A_KIND)
	{
		cout<<"It's Four of a kind\n";
	}
	else if(pattern==FULL_HOUSE)
	{
		cout<<"It's Full house\n";
	}
	else if(pattern==FLUSH)
	{
		cout<<"It's Flush\n";
	}
	else if(pattern==STRAIGHT)
	{
		cout<<"It's Straight\n";
	}
	else if(pattern==THREE_OF_A_KIND)
	{
		cout<<"It's Three of a kind\n";
	}
	else if(pattern==TWO_PAIR)
	{
		cout<<"It's Two pair\n";
	}
	else if(pattern==ONE_PAIR)
	{
		cout<<"It's One pair\n";
	}
	else
	{
		cout<<"It's Other\n";
	}

}
