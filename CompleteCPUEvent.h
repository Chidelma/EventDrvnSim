#include "Devent.h"

class CompleteCPUEvent : public Devent
{
	private:
		bool stillPending;

	public:
		CompleteCPUEvent();
		CompleteCPUEvent(int processID, int t, bool sPending);
		bool getStillPending();
		void setStillPending(bool sPending);
		void processEvent();
};
