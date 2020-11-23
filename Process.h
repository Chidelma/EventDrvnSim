
class Process
{
	private:
		static int processes;
		int pid;
		int numBursts;
		int *burstArray;
		int arrivalTime;
		int currBurstIndex;
		int remBurstTime;
		int cpuTime;
		int ioTime;
		int exitTime;
		int waitTime;
		int remIOBurstTime;

	public:
		Process();
		Process(int* burstValues, int bursts, int arrTime);
		~Process();

		int getPid();

		int getNumBursts();
		void setNumBursts(int bursts);

		int* getBurstArray();
		void setBurstArray(int* burstValues, int bursts, int arrTime);

		int getArrivalTime();
		void setArrivalTime(int arrTime);

		int getCurrBurstIndex();
		void setCurrBurstIndex(int burstIndex);

		int getRemBurstTime();
		void setRemBurstTime(int bursts);

		void printBurstArray();
		void printDetails();

		int getBurstValue();
		int getBurstValue(int burstIndex);

		void setBurstValue(int burstValue);
		void setBurstValue(int burstValue, int burstIndex);

		void incrBurstIndex();

		int getCpuTime();
		void setCpuTime(int cTime);

		int getIoTime();
		void setIoTime(int iTime);

		int getExitTime();
		void setExitTime(int eTime);

		int getWaitTime();
		void setWaitTime(int wTime);

		void incrCpuTime();
		void incrIoTime();

		void decrRemBurstTime();
		void decrRemIOBurstTime();
		bool isCurrBurstDone();
		bool isCurrIOBurstDone();
		void incrCurrBurstIndex();
		bool isAllDone();

		int getRemIOBurstTime();
		void setRemIOBurstTime(int bursts);

		int getPriority();

};
