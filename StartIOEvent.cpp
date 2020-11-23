#include "StartIOEvent.h"
#include<iostream>
using namespace std;

StartIOEvent::StartIOEvent()
{
	time = 0;
	pid = 0;
	burstLength = 0;
}

StartIOEvent::StartIOEvent(int processID, int t, int burstValue)
{
	time = t;
	pid = processID;
	burstLength = burstValue;
}

int StartIOEvent::getBurstLength()
{
	return burstLength;
}

void StartIOEvent::setBurstLength(int burstValue)
{
	burstLength = burstValue;
}

void StartIOEvent::processEvent()
{
	Devent::processEvent();
	cout << " begins I/O burst of length " << burstLength << ".";
	cout << endl;
}
