#include "DEsimulation.h"
#include "ArrivalEvent.h"
#include "StartCPUEvent.h"
#include "CompleteCPUEvent.h"
#include "StartIOEvent.h"
#include "CompleteIOEvent.h"
#include "TimeoutEvent.h"
#include "ExitEvent.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

DEsimulation::DEsimulation()
{
	processList = 0;
	isCPUBusy = false;
	isIOBusy = false;
	currCpuTime = 0;
	runningProcess = 0;
	runningIO = 0;
	doneProcesses = 0;
	priCnt = 0;
}

/*
DEsimulation::~DEsimulation()
{
	if(processList != 0)
	{
		delete processList;
	}
}
*/

void DEsimulation::readProcessData(char* filename)
{
	ifstream inpStream;
	char buff[MAXCHARS];

	// Open the input file stream
	inpStream.open(filename);

	// Read the first line and store it in the buffer memory space
	inpStream.getline(buff, MAXCHARS);

	int p=0;
	int temp[MAXPROCESSES][MAXCHARS];
	int nval[MAXPROCESSES];
	int atime[MAXPROCESSES];

	// Loop until done with reading all the lines in the file
	while(!inpStream.eof())
	{
		// Create a string stream from the buffer space
		stringstream lineStream(buff);
		int readValue;
		int i=0;

		// Keep reading all of the input data from the current line
		while (!lineStream.eof())
		{
			lineStream >> readValue;
			if(i)
			{
				temp[p][i-1] = readValue;
			}
			else
			{
				atime[p] = readValue;
			}
			i++;
		}
		inpStream.getline(buff, MAXCHARS);
		nval[p] = i - 1;
		p++;
	}

	processList = new Process[p];
	processes = p;
	for(int j=0;j<p;j++)
	{
		processList[j].setBurstArray(temp[j], nval[j], atime[j]);
	}

	// Close the input file stream
	inpStream.close();
}

void DEsimulation::printProcessData()
{
	cout << setw(9) << "Process" << setw(10) << "Arrival" << setw(10) << "CPU" << setw(10) << "I/O" << setw(10) << "Exit" << setw(10) << "Wait" << endl;
	cout << setw(9) << "#" << setw(10) << "Time" << setw(10) << "Time" << setw(10) << "Time" << setw(10) << "Time" << setw(10) << "Time" << endl;
	cout << "-----------------------------------------------------------" << endl;
	for(int i=0;i<processes;i++)
	{
		processList[i].printDetails();
	}
}

void DEsimulation::getAllArrivalEvents(int t)
{
	while((!readyQueue.isEmpty()) && (t == readyQueue.getFrontData()->getArrivalTime()))
	{
		Process* p = readyQueue.dequeueItem();
		//pendingQueue.priQueueItem(new ArrivalEvent(p->getPid(),t,isCPUBusy), isCPUBusy ? p->getPriority() * 4 : p->getPriority() * 2);
		//pendingQueue.priQueueItem(new ArrivalEvent(p->getPid(),t,isCPUBusy), p->getPriority() + priCnt++);
		pendingQueue.priQueueItem(new ArrivalEvent(p->getPid(),t,isCPUBusy), priCnt++);
		//pendingQueue.priQueueItem(new ArrivalEvent(p->getPid(),t,isCPUBusy), isCPUBusy ? p->getPriority() - 5: p->getPriority() - 10);
		//pendingQueue.priQueueItem(new ArrivalEvent(p->getPid(),t,isCPUBusy), p->getPriority() - 10);
		//pendingQueue.priQueueItem(new ArrivalEvent(p->getPid(),t,isCPUBusy), p->getPriority());
		scheduleCPU(p, t, false);
	}
}

void DEsimulation::keepCollectingEvents(int t)
{
	GQueue<Devent*> allEvents;
	getAllArrivalEvents(t);
	int pPri = 99999;
	int iPri = 99999;
	if(runningProcess != 0)
	{
		pPri = runningProcess->getPriority();
	}
	else if(!cpuQueue.isEmpty())
	{
		pPri = cpuQueue.getFrontData()->getPriority();
	}
	if(runningIO != 0)
	{
		iPri = runningIO->getPriority();
	}
	else if(!ioQueue.isEmpty())
	{
		iPri = ioQueue.getFrontData()->getPriority();
	}

	if(pPri <= iPri)
	{
		getAllCPUEvents(t);
		getAllIOEvents(t);
	}
	else
	{
		getAllIOEvents(t);
		getAllCPUEvents(t);
	}
}

void DEsimulation::runDEsimulation()
{
	for(int i=0;i<processes;i++)
	{
		readyQueue.queueItem(&processList[i]);
	}
	int t = processList[0].getArrivalTime();
	//Process* currProcess = 0;
	//int prevTime = t;
	//int nextArrival = 0;
	while(doneProcesses < processes)
	{
		processCPU();
		processIO();

		keepCollectingEvents(t);

		while(!pendingQueue.isEmpty())
		{
			eventQueue.queueItem(pendingQueue.dequeueItem());
		}

		t++;
	}
	cout << "Simulation begins..." << endl;
	while(!eventQueue.isEmpty())
	{
		Devent* currEvent = eventQueue.dequeueItem();
		currEvent->processEvent();
	}
	cout << endl;
	cout << "...All Processes complete.  Final Summary:" << endl;
	cout << endl;
	printProcessData();
	cout << endl;
	cout << "End of processing.";
	cout << endl;
}

bool DEsimulation::nextCPU(int t, bool pri)
{
	bool next = false;
	if(!cpuQueue.isEmpty())
	{
		scheduleCPU(cpuQueue.dequeueItem(),t,pri);
		next = true;
	}
	return next;
}

bool DEsimulation::nextIO(int t, bool pri)
{
	bool next = false;
	if(!ioQueue.isEmpty())
	{
		scheduleIO(ioQueue.dequeueItem(),t,pri);
		next = true;
	}
	return next;
}

void DEsimulation::scheduleCPU(Process* process, int t, bool pri)
{
	if(!isCPUBusy)
	{
		runningProcess = process;
		isCPUBusy = true;
		int currBurst = runningProcess->getBurstValue();
		int pid = runningProcess->getPid();
		runningProcess->setRemBurstTime(currBurst);
		//pendingQueue.priQueueItem(new StartCPUEvent(pid,t,currBurst), runningProcess->getPriority() * 8);
		if(pri)
		{
			pendingQueue.priQueueItem(new StartCPUEvent(pid,t,currBurst), runningProcess->getPriority() + priCnt++);
		}
		else
		{
			pendingQueue.queueItem(new StartCPUEvent(pid,t,currBurst));
		}
		//pendingQueue.queueItem(new StartCPUEvent(pid,t,currBurst));
	}
	else
	{
		cpuQueue.queueItem(process);
	}
}

void DEsimulation::scheduleIO(Process* process, int t, bool pri)
{
	if(!isIOBusy)
	{
		runningIO = process;
		isIOBusy = true;
		int currBurst = runningIO->getBurstValue();
		int pid = runningIO->getPid();
		runningIO->setRemIOBurstTime(currBurst);
		//pendingQueue.priQueueItem(new StartIOEvent(pid,t,currBurst), runningIO->getPriority() * 8);
		if(pri)
		{
			pendingQueue.priQueueItem(new StartIOEvent(pid,t,currBurst), runningIO->getPriority() + priCnt++);
		}
		else
		{
			pendingQueue.queueItem(new StartIOEvent(pid,t,currBurst));
		}
		//pendingQueue.queueItem(new StartIOEvent(pid,t,currBurst));
	}
	else
	{
		ioQueue.queueItem(process);
	}
}

void DEsimulation::processCPU()
{
	if(runningProcess != 0)
	{
		runningProcess->incrCpuTime();
		runningProcess->decrRemBurstTime();
		currCpuTime++;
	}
}

void DEsimulation::getAllCPUEvents(int t)
{
	if(runningProcess != 0)
	{
		int pid = runningProcess->getPid();
		if(runningProcess->isCurrBurstDone())
		{
			currCpuTime = 0;
			runningProcess->incrCurrBurstIndex();
			bool done = runningProcess->isAllDone();
			//pendingQueue.priQueueItem(new CompleteCPUEvent(pid, t, !done), runningProcess->getPriority() * 8);
			pendingQueue.priQueueItem(new CompleteCPUEvent(pid, t, !done), runningProcess->getPriority() + priCnt++);
			//pendingQueue.queueItem(new CompleteCPUEvent(pid, t, !done));
			if(done)
			{
				doneProcesses++;
				int wTime = t - (runningProcess->getArrivalTime() + runningProcess->getCpuTime() + runningProcess->getIoTime());
				runningProcess->setExitTime(t);
				runningProcess->setWaitTime(wTime);
				//pendingQueue.priQueueItem(new ExitEvent(pid, t, wTime), runningProcess->getPriority() * 8);
				pendingQueue.priQueueItem(new ExitEvent(pid, t, wTime), runningProcess->getPriority() + priCnt++);
				//pendingQueue.queueItem(new ExitEvent(pid, t, wTime));
				runningProcess = 0;
				isCPUBusy = false;
				nextCPU(t, false);
			}
			else
			{
				scheduleIO(runningProcess, t, true);
				runningProcess = 0;
				isCPUBusy = false;
				nextCPU(t, false);
			}
		}
		else
		{
			if(currCpuTime >= CPUTIME)
			{
				currCpuTime = 0;
				//pendingQueue.priQueueItem(new TimeoutEvent(pid, t , runningProcess->getRemBurstTime()), runningProcess->getPriority() + 10);
				//pendingQueue.priQueueItem(new TimeoutEvent(pid, t , runningProcess->getRemBurstTime()), runningProcess->getPriority() * 10);
				pendingQueue.priQueueItem(new TimeoutEvent(pid, t , runningProcess->getRemBurstTime()), runningProcess->getPriority() + priCnt++);
				//pendingQueue.queueItem(new TimeoutEvent(pid, t , runningProcess->getRemBurstTime()));
				//pendingQueue.priQueueItem(new TimeoutEvent(pid, t , runningProcess->getRemBurstTime()), runningProcess->getPriority());
				runningProcess->setBurstValue(runningProcess->getRemBurstTime());
				cpuQueue.queueItem(runningProcess);
				runningProcess = 0;
				isCPUBusy = false;
				nextCPU(t, false);
			}
		}
	}
	else
	{
		nextCPU(t, true);
	}
}
		
void DEsimulation::processIO()
{
	if(runningIO != 0)
	{
		runningIO->incrIoTime();
		runningIO->decrRemIOBurstTime();
	}
}

void DEsimulation::getAllIOEvents(int t)
{
	if(runningIO != 0)
	{
		int pid = runningIO->getPid();
		if(runningIO->isCurrIOBurstDone())
		{
			runningIO->incrCurrBurstIndex();
			bool done = runningIO->isAllDone();
			pendingQueue.priQueueItem(new CompleteIOEvent(pid, t, !done), runningIO->getPriority() + priCnt++);
			//pendingQueue.queueItem(new CompleteIOEvent(pid, t, !done));
			if(done)
			{
				doneProcesses++;
				int wTime = t - (runningIO->getArrivalTime() + runningIO->getCpuTime() + runningIO->getIoTime());
				runningIO->setExitTime(t);
				runningIO->setWaitTime(wTime);
				pendingQueue.priQueueItem(new ExitEvent(pid, t, wTime), runningIO->getPriority() + priCnt++);
				//pendingQueue.queueItem(new ExitEvent(pid, t, wTime));
				runningIO = 0;
				isIOBusy = false;
				nextIO(t, false);
			}
			else
			{
				scheduleCPU(runningIO,t,true);
				runningIO = 0;
				isIOBusy = false;
				nextIO(t, false);
			}
		}
	}
	else
	{
		nextIO(t, true);
	}
}
