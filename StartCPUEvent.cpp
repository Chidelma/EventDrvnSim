#include "StartCPUEvent.h"
#include<iostream>
using namespace std;

StartCPUEvent::StartCPUEvent()
{
	time = 0;
	pid = 0;
	burstLength = 0;
}

StartCPUEvent::StartCPUEvent(int processID, int t, int burstValue)
{
	time = t;
	pid = processID;
	burstLength = burstValue;
}

int StartCPUEvent::getBurstLength()
{
	return burstLength;
}

void StartCPUEvent::setBurstLength(int burstValue)
{
	burstLength = burstValue;
}

void StartCPUEvent::processEvent()
{
	Devent::processEvent();
	cout << " begins CPU burst of length " << burstLength << ".";
	cout << endl;
}
