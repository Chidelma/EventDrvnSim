#include "Devent.h"
#include <iostream>
#include <iomanip>
using namespace std;

Devent::Devent()
{
	time = 0;
	pid = 0;
}

void Devent::processEvent()
{
	cout << "Time  " << setw(4) << time << ": Process  " << setw(2) << pid;
}
