#include "Devent.h"

class StartCPUEvent : public Devent
{
	private:
		int burstLength; 

	public:
		StartCPUEvent();
		StartCPUEvent(int processID, int t, int burstValue);
		int getBurstLength();
		void setBurstLength(int burstValue);
		void processEvent();
};
