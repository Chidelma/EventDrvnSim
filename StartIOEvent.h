#include "Devent.h"

class StartIOEvent : public Devent
{
	private:
		int burstLength; 

	public:
		StartIOEvent();
		StartIOEvent(int processID, int t, int burstValue);
		int getBurstLength();
		void setBurstLength(int burstValue);
		void processEvent();
};
