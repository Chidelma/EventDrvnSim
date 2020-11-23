#include "CompleteCPUEvent.h"
#include<iostream>
using namespace std;

CompleteCPUEvent::CompleteCPUEvent()
{
	time = 0;
	pid = 0;
	stillPending = true;
}

CompleteCPUEvent::CompleteCPUEvent(int processID, int t, bool sPending)
{
	time = t;
	pid = processID;
	stillPending = sPending;
}

bool CompleteCPUEvent::getStillPending()
{
	return stillPending;
}

void CompleteCPUEvent::setStillPending(bool sPending)
{
	stillPending = sPending;
}

void CompleteCPUEvent::processEvent()
{
	Devent::processEvent();
	cout << " completes CPU burst.";
	if(stillPending)
	{
		cout << " Queueing for I/O.";
	}
	cout << endl;
}
