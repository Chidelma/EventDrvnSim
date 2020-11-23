#include "TimeoutEvent.h"
#include<iostream>
using namespace std;

TimeoutEvent::TimeoutEvent()
{
	time = 0;
	pid = 0;
	moreBurst = 0;
}

TimeoutEvent::TimeoutEvent(int processID, int t, int burstValue)
{
	time = t;
	pid = processID;
	moreBurst = burstValue;
}

int TimeoutEvent::getMoreBurst()
{
	return moreBurst;
}

void TimeoutEvent::setMoreBurst(int burstValue)
{
	moreBurst = burstValue;
}

void TimeoutEvent::processEvent()
{
	Devent::processEvent();
	cout << " exhausts its time quantum (requires " << moreBurst << " units more).";
	cout << endl;
}
