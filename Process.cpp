#include "Process.h"
#include <iostream>
#include <iomanip>
using namespace std;

int Process::processes = 0;

Process::Process()
{
	processes++;
	pid = processes;
	numBursts = 0;
	burstArray = 0;
	arrivalTime = 0;
	currBurstIndex = 0;
	remBurstTime = 0;
	cpuTime = 0;
	ioTime = 0;
	exitTime = 0;
	waitTime = 0;
}

Process::Process(int* burstValues, int bursts, int arrTime)
{
	processes++;
	pid = processes;
	currBurstIndex = 0;
	setBurstArray(burstValues, bursts, arrTime);
	cpuTime = 0;
	ioTime = 0;
	exitTime = 0;
	waitTime = 0;
}

Process::~Process()
{
	if(burstArray != 0)
	{
		delete burstArray;
	}
}

int Process::getPid()
{
	return pid;
}

int Process::getNumBursts()
{
	return numBursts;
}

void Process::setNumBursts(int bursts)
{
	numBursts = bursts;
}

int* Process::getBurstArray()
{
	return burstArray;
}

void Process::setBurstArray(int* burstValues, int bursts, int arrTime)
{
	setNumBursts(bursts);
	burstArray = new int[bursts];
	for(int i = 0; i < bursts; i++)
	{
		burstArray[i] = burstValues[i];
	}
	setRemBurstTime(burstArray[0]);
	setArrivalTime(arrTime);
}

int Process::getArrivalTime()
{
	return arrivalTime;
}

void Process::setArrivalTime(int arrTime)
{
	arrivalTime = arrTime;
}

int Process::getCurrBurstIndex()
{
	return currBurstIndex;
}

void Process::setCurrBurstIndex(int burstIndex)
{
	currBurstIndex = burstIndex;
}

int Process::getRemBurstTime()
{
	return remBurstTime;
}

void Process::setRemBurstTime(int remTime)
{
	remBurstTime = remTime;
}

void Process::printBurstArray()
{
	for(int i=0;i<numBursts;i++)
	{
		cout << burstArray[i] << " ";
	}
	cout << endl;
}

void Process::printDetails()
{
//	cout << "Myself with pid [" << pid << "] arrived at time t=[" << arrivalTime << "] and going to burst index [" <<  currBurstIndex << "] from the below burst array of [" << numBursts << "] bursts" << endl;
//	printBurstArray();
	cout << setw(9) << pid;
	cout << setw(10) << arrivalTime;
	cout << setw(10) << cpuTime;
	cout << setw(10) << ioTime;
	cout << setw(10) << exitTime;
	cout << setw(10) << waitTime;
	cout << endl;
}

int Process::getBurstValue()
{
	return burstArray[currBurstIndex];
}

int Process::getBurstValue(int burstIndex)
{
	return burstArray[burstIndex];
}

void Process::setBurstValue(int burstValue)
{
	burstArray[currBurstIndex] = burstValue;
}

void Process::setBurstValue(int burstValue, int burstIndex)
{
	burstArray[burstIndex] = burstValue;
}

void Process::incrBurstIndex()
{
	currBurstIndex++;
}

int Process::getCpuTime()
{
	return cpuTime;
}

void Process::setCpuTime(int cTime)
{
	cpuTime = cTime;
}

int Process::getIoTime()
{
	return ioTime;
}

void Process::setIoTime(int iTime)
{
	ioTime = iTime;
}

int Process::getExitTime()
{
	return exitTime;
}

void Process::setExitTime(int eTime)
{
	exitTime = eTime;
}

int Process::getWaitTime()
{
	return waitTime;
}

void Process::setWaitTime(int wTime)
{
	waitTime = wTime;
}

void Process::incrCpuTime()
{
	cpuTime++;
}

void Process::incrIoTime()
{
	ioTime++;
}

void Process::decrRemBurstTime()
{
	remBurstTime--;
}

void Process::decrRemIOBurstTime()
{
	remIOBurstTime--;
}

bool Process::isCurrBurstDone()
{
	return (remBurstTime == 0);
}

bool Process::isCurrIOBurstDone()
{
	return (remIOBurstTime == 0);
}

void Process::incrCurrBurstIndex()
{
	currBurstIndex++;
}

bool Process::isAllDone()
{
	return (currBurstIndex == numBursts);
}

int Process::getRemIOBurstTime()
{
	return remIOBurstTime;
}

void Process::setRemIOBurstTime(int remTime)
{
	remIOBurstTime = remTime;
}

int Process::getPriority()
{
	return pid + arrivalTime;
}
