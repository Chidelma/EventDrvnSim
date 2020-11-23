#include "Devent.h"

class ExitEvent : public Devent
{
	private:
		int waitTime; 

	public:
		ExitEvent();
		ExitEvent(int processID, int t, int wTime);
		int getWaitTime();
		void setWaitTime(int wTime);
		void processEvent();
};
