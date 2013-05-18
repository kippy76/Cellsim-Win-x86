//=======================================================================
// Name        : CellSim.cpp
// Author      : Christopher Walker
// Version     : 1.0
// Copyright   : Christopher Walker
// Description : Cellular automata model of the Dundee iGem 2012 project.
//               http://dundeeigem.blogspot.co.uk
//               http://2012.igem.org/Team:Dundee
// License     : GNU GPL 3.0
//=======================================================================

#include <iostream>
#include "Controller.h"
#include "IO.h"
#include "CAException.cpp"
#include "SDL.h"
using namespace std;

int main(int argc, char *argv[])
{
	int maximumCellCount = IO::getValue("General", "maxcells")[0].valueI;
	float maxFlowrate = IO::getValue("General", "flowrate")[0].valueF;
	int mucusBorder = IO::getValue("General", "mucuslayerdepth")[0].valueI;
	int screenWidth = IO::getValue("General", "screenwidth")[0].valueI;
	int screenHeight = IO::getValue("General", "screenheight")[0].valueI;
	bool FULLSCREEN = IO::getValue("General", "fullscreen")[0].valueI == 0 ? false : true;
	maximumCellCount = maximumCellCount == 0 ? 300000 : maximumCellCount;
	Controller* control = NULL;
	//
	try
	{
		if (screenWidth == 0)
		{
			throw CAException("Error: Screen width must be specified in settings.dat");
		}
		if (screenHeight == 0)
		{
			throw CAException("Error: Screen height must be specified in settings.dat");
		}
		control = new Controller(maximumCellCount, maxFlowrate, mucusBorder, screenWidth,
				screenHeight, FULLSCREEN);
		control->runSimulation();
		delete control;
	}
	catch (CAException& e)
	{
		std::cout << e.what() << std::endl;
		if (control != NULL)
		{
			delete control;
		}
	}
	return 0;
}
