#ifndef DEVENT_H
#define DEVENT_H

class Devent
{
	protected:
		int time;
		int pid;

	public:
		Devent();
		virtual void processEvent();
};

#endif
