#include "CompleteIOEvent.h"
#include<iostream>
using namespace std;

CompleteIOEvent::CompleteIOEvent()
{
	time = 0;
	pid = 0;
	stillPending = true;
}

CompleteIOEvent::CompleteIOEvent(int processID, int t, bool sPending)
{
	time = t;
	pid = processID;
	stillPending = sPending;
}

bool CompleteIOEvent::getStillPending()
{
	return stillPending;
}

void CompleteIOEvent::setStillPending(bool sPending)
{
	stillPending = sPending;
}

void CompleteIOEvent::processEvent()
{
	Devent::processEvent();
	cout << " completes I/O burst.";
	if(stillPending)
	{
		cout << " Queueing for CPU.";
	}
	cout << endl;
}
