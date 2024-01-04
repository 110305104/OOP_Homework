/* Copyright (c) 2005 by The National Chengchi Univ. All Rights Reserved */

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
}

#include <iostream>
#include <cassert>
#include "Card.h"
#include "SHPlayer.h"
#include "AnsiPrint.h"

using namespace std;


/**
 * Print my ID
 */
void
PrintMyID(const char* studId)
{
    char *str = new char[sizeof(studId) + 5];
    sprintf(str, "ID: %s", studId);
    AnsiPrint(str, yellow, red, true, true);
    cout << endl << endl;
    delete [] str;
}


/**
 * print the usage
 */
void
PrintUsage(const char* progName)
{
    assert(progName);
    cout << "Usage: " << progName << " [Seed] [ShowFirst(0/1)]" << endl;
}

int
main(int argc, char** argv)
{
    bool showFirst = false;
    long seed = 0;

    if( argc > 3 ) {
        PrintUsage(argv[0]);
        exit(-1);
    }
    if( argc == 3 ) {
        showFirst = atoi(argv[2]);      // the third argument shows the first card
    }
    if( argc > 1 ) {
        seed = atoi(argv[1]);
    }
    srand(seed);


    SHPlayer shplayer("Player");

    // put your code here
	
	int totalPoint=0;

	Card mycard;//check
	shplayer.start();

	int i,n, cardA[52]={0};
	//int randCard[52];
	for(i=0;i<5;i++)
	{
		do
		{
			n=rand()%52;
		}while(cardA[n] != 0);
		{
			//randCard[i] = n;
			cardA[n]++;
		}
		mycard.setID(n);
		shplayer.addCard(mycard);
		totalPoint+=n/4;
	}


	if(showFirst)
	{
		shplayer.openFirstCard();
	}

	shplayer.showCards();
		
	HandType mytype=shplayer.getHandPattern();
	//cout<<mytype<<"\n";

	cout<<"It's "<<HandTypeName[mytype]<<"\n";
	//cout<<"\n\ntry\n";
	//shplayer.outputPattern(shplayer.getHandPattern());
	//shplayer.outputPattern(mytype);
	
	//totalPoint=shplayer.totalPips();
	totalPoint+=5;
	cout<<"Total points: "<<totalPoint<<"\n";


    PrintMyID("110305104");

    return 0;
}

