/* Copyright (c) 2005 by The National Chengchi Univ. All Right Reserved */

#ifndef _SHDEALER_H_
#define _SHDEALER_H_

// result of a game
enum Result {TIE, WIN, LOSE};

// foreward declaration of class SHPlayer
class SHPlayer;


#include "Card.h"

#include "SHPlayer.h"



extern const char* HandTypeName[9];

/**
 * The Dealer class simulate the dealer in a show hand game.
 * It's responsible for
 * 1. shuffing the cards,
 * 2. draw and distribute a hand to a player.
 */
class SHDealer {

    public:

        /**
         * constructor
         */
        SHDealer();

        /**
         * destructor
         */
        ~SHDealer();

        /**
         * return a valid catd ID to the player
         */
        Card giveCard();

        /**
         * give myself(the dealer) onmore card
         */
        void addCard();

        /**
         * judge who has won the game
         * input argument is the show hand player
         */
        Result judge(SHPlayer& player);

        /**
         * starting a new game
         */
        void start();

        /**
         * open the first card so it faces up
         */
        void openFirstCard();

        /**
         * retain the whole set of cards and shuffle
         */
        void shuffle();

        /**
         * show the dealer's cards to the screen
         */
        void showCards() const;
        //int getLast();
        //void setLast();

        int totalPips() const;
        int getNumCards() const;
        HandType getHandPattern();
        //int SHDealer::totalPips() const;



    private:
    // TODO: your private or internal stuff goes here ...

            bool isStraightFlush() const;
            bool isFourOfAKind() const;
            bool isFullHouse() const;
            bool isFlush() const;
            bool isStraight() const;
            bool isThreeOfAKind() const;
            bool isTwoPair() const;
            bool isOnePair() const;
            void sortCards() ;

            static const int kMaxCards = 5;  // maximal number of cards I can hold
            Card cards[kMaxCards];              // the current hand
            Card sortedCards[kMaxCards];        // sorted cards
            int num;//the number of cards at hand
            //char Dname[];
            int isOpen;
            int record[52];// record drawn or not

        
};


#endif // _SHDEALER_H_
