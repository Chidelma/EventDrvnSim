#include "Devent.h"

class ArrivalEvent : public Devent
{
	private:
		bool isBusy; 

	public:
		ArrivalEvent();
		ArrivalEvent(int processID, int t, bool busy);
		bool getIsBusy();
		void setIsBusy(bool busy);
		void processEvent();
};
