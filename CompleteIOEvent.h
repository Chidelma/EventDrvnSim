#include "Devent.h"

class CompleteIOEvent : public Devent
{
	private:
		bool stillPending;

	public:
		CompleteIOEvent();
		CompleteIOEvent(int processID, int t, bool sPending);
		bool getStillPending();
		void setStillPending(bool sPending);
		void processEvent();
};
