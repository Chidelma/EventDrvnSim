#include "ArrivalEvent.h"
#include<iostream>
using namespace std;

ArrivalEvent::ArrivalEvent()
{
	time = 0;
	pid = 0;
	isBusy = false;
}

ArrivalEvent::ArrivalEvent(int processID, int t, bool busy)
{
	time = t;
	pid = processID;
	isBusy = busy;
}

bool ArrivalEvent::getIsBusy()
{
	return isBusy;
}

void ArrivalEvent::setIsBusy(bool busy)
{
	isBusy = busy;
}

void ArrivalEvent::processEvent()
{
	Devent::processEvent();
	cout << " arrives in system: ";
	if(isBusy)
	{
		cout << "CPU is busy (process will be queued).";
	}
	else
	{
		cout << "CPU is free (process begins execution).";
	}
	cout << endl;
}
