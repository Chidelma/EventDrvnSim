#include "Devent.h"

class TimeoutEvent : public Devent
{
	private:
		int moreBurst; 

	public:
		TimeoutEvent();
		TimeoutEvent(int processID, int t, int burstValue);
		int getMoreBurst();
		void setMoreBurst(int burstValue);
		void processEvent();
};
