#include "Process.h"
#include "GQueue.hpp"
#include "Devent.h"

#define MAXCHARS 100
#define MAXPROCESSES 100
#define CPUTIME	4

class DEsimulation
{
	private:
		Process* processList;
		int processes;
		GQueue<Devent*> eventQueue;
		GQueue<Process*> readyQueue;
		GQueue<Process*> cpuQueue;
		GQueue<Process*> ioQueue;
		GQueue<Devent*> pendingQueue;

	public:
		DEsimulation();
		//~DEsimulation();
		void readProcessData(char* filename);
		void printProcessData();
		void runDEsimulation();
		void processCPU();
		void processIO();
		void decideCPU(int t);
		void decideIO(int t);
		void scheduleCPU(Process* p,int t,bool pri);
		void scheduleIO(Process* p,int t, bool pri);
		bool nextCPU(int t, bool pri);
		bool nextIO(int t, bool pri);
		void getAllArrivalEvents(int t);
		void getAllCPUEvents(int t);
		void getAllIOEvents(int t);
		void keepCollectingEvents(int t);

		bool isCPUBusy;
		bool isIOBusy;
		int currCpuTime;
		Process* runningProcess;
		Process* runningIO;
		int doneProcesses;
		int priCnt;
};
