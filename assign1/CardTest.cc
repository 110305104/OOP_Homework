	/* Copyright (c) 1999 by The National Chengchi Univ. All Rights Reserved */

/***************************************************************************
   NAME
     CardTest.cc
   PURPOSE
     Testing card displaying
   NOTES

   AUTHOR
     Tsai-Yen Li (li@cs.nccu.edu.tw)
   HISTORY
     Tsai-Yen Li - Oct 7, 1999: Created.
***************************************************************************/

/* $Log:$ */

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <assert.h>
}

#include <iostream>
#include "AnsiPrint.h"
#include "Cards.h"

using namespace std;

/**
 * Print my id 
 */
void
PrintMyID(const char *studId) {

  char *str= new char[sizeof(studId)+5];
  // we put string in a buffer first 
  sprintf(str,"ID: %s",studId);
  // print the buffer out with color
  AnsiPrint(str,yellow,red, true, true);
  cout << endl << endl;
  delete [] str;

}


/**
 * PrintUsage
 */
void
PrintUsage(const char *progName) {

  assert(progName);
  cout << "Usage: " << progName << " NCards [Seed]" << endl;

}

/**
 * Main Function Call
 */
int
main(int argc, char **argv) {

  int ncards=0;  // number of cards to draw 
  if (argc==3) {
    long seed=atoi(argv[2]); // the third argument is the seed
    srand(seed);
    ncards=atoi(argv[1]); // the second argument is the number of cards
  } else if (argc==2) {
    ncards=atoi(argv[1]);
  } else {
    PrintUsage(argv[0]);
    exit(-1);
  }

// You are asked to fill in a few missing statements here

  //洗牌
 	int ksize =ncards,jsize,conter=0;
	int i, n, cardA[52] = { 0 };
	int randCard[52];
	
	for (i = 0; i < 52; i++)
	{
		do
		{
			n = rand() % 52;
		} while (cardA[n] != 0);
		{
			randCard[i] = n;
			cardA[n]++;
		}
	}

  //印牌
if (ncards>52)
{
	printf("Sorry, number of cards can not be greater than 52.\n");
}
else
{

 while(ksize>0)
  {
	if(ksize>5)
	{
		ksize-=5;
	    jsize=5;
	}
	else
	{
		jsize=ksize;
		ksize =-1;
	}
  	for(int i=0;i<11;i++)
  	{
		 for(int j=0;j<jsize;j++)
	 	{ 
			
			if(randCard[conter+j]<26)
			{
				AnsiPrint(*card[randCard[conter+j]]+(i*12),red,white,false,false);
			}else
			{	   
		   		AnsiPrint(*card[randCard[conter+j]]+(i*12),black,white,false,false);
			}
			printf(" ");
		
	 	}
		
 		printf("\n");
  	}
	conter+=5;
	//printf("\n");	
  } 
  // Print my id at the end of the program
  PrintMyID("110305104");
}

  return 0;
}
