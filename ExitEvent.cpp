#include "ExitEvent.h"
#include<iostream>
using namespace std;

ExitEvent::ExitEvent()
{
	time = 0;
	pid = 0;
	waitTime = 0;
}

ExitEvent::ExitEvent(int processID, int t, int wTime)
{
	time = t;
	pid = processID;
	waitTime = wTime;
}

int ExitEvent::getWaitTime()
{
	return waitTime;
}

void ExitEvent::setWaitTime(int wTime)
{
	waitTime = wTime;
}

void ExitEvent::processEvent()
{
	Devent::processEvent();
	cout << " complete. Total wait time is: " << waitTime;
	cout << endl;
}
