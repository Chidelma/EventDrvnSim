#include <iostream>
#include <cstdlib>
#include "DEsimulation.h"
using namespace std;

void setupDEsimulation(char* inpFileName)
{
	DEsimulation simulationCtxt;
	simulationCtxt.readProcessData(inpFileName);
	simulationCtxt.runDEsimulation();
}

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		cout << "You might want to say: " << argv[0] << " < inputfile_1 [inputfile_2] [inputfile_3] ... [inputfile_N]>" << endl;
		exit(1);
	}

	for(int i=2;i<=argc;i++)
	{
		setupDEsimulation(argv[i-1]);
	}
	return 0;
}

