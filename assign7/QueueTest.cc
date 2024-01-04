/* Copyright (c) 1998 by The National Chengchi Univ. All Rights Reserved */

/***************************************************************************
   NAME
     QueueTest.cc
   PURPOSE
     
   NOTES
     
   AUTHOR
     Tsai-Yen Li (li@cs.nccu.edu.tw)
   HISTORY
     Tsai-Yen Li - Dec 11, 1998: Created.
***************************************************************************/

/* $Log:$ */

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
}

#include <iostream>
#include <fstream>
#include "AnsiPrint.h"

#include "Queue.h"
#include "Queue.cc"

using namespace std;

/**
 * Print my id 
 */

void
PrintMyID(const char *studId) {

  char *str= new char[strlen(studId)+5];
  sprintf(str,"ID: %s",studId);
  AnsiPrint(str, yellow, red, true, true);
  cout << endl ;
  delete [] str;

}

/**
 * PrintUsage
 */

void
PrintUsage(const char *progName) {

    assert(progName);
    cout << "Usage: " << progName << " [passes [display [seed]]]" << endl;

}

int
main(int argc, char **argv) {

	istream *is1=&cin, *is2=&cin;

	if (argc>3) {
		PrintUsage(argv[0]);
		exit(-1);
	} else if (argc>2) {
		is2 = new ifstream(argv[2]);
		if (is2==NULL) {
			cerr << "Can't open file " << argv[2] << endl;
			exit(1);
		}
	} 
	if (argc>1) {
		is1 = new ifstream(argv[1]);
		if (is1==NULL) {
			cerr << "Can't open file " << argv[1] << endl;
			exit(2);
		}
	}

	// You need to provide testing exercises here

	//test integer queue
	Queue<int> *myIntQPtr=new Queue<int>;

	//enqueue exercises on myIntQPtr
	int n;
	while((*is1)>>n)
	{
		myIntQPtr->enqueue(n);
	}

	//test copy constructer
	Queue<int> myIntQ=*myIntQPtr;

	//test destructer
	delete myIntQPtr;

	//print myIntQ
	char prst[]="Interger Queue:";
	AnsiPrint(prst,yellow,black,true,false);
	cout<<endl;
	myIntQ.print();

	//dequeue exercises on myIntQ
	while(myIntQ.isEmpty()==false)
	{
		myIntQ.dequeue();
	}

	//********//
	
	//test char queue
	Queue<char> myCharQ, myCharQ1;

	//enqueue exercise on myCharQ
	char tmp;
	while((*is2)>>tmp)
	{
		myCharQ.enqueue(tmp);
	}

	//test assignment operator
	myCharQ1=myCharQ;

	//print myCharQ
	char prst2[]="Character Queue:";
 	AnsiPrint(prst2,yellow,black,true,false);
	cout<<endl;
	myCharQ.print();

	//dequeue exercise on myCharQ1
	while(myCharQ1.isEmpty()==false)
	{
		myCharQ1.dequeue();
	}

	myCharQ1.dequeue();//error，throw exceptions

	
	PrintMyID("110305104");
	return 0;
    
}
