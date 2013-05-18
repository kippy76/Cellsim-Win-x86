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

#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include "Model.h"
#include "View.h"
#include "Generator.h"

class Controller
{
	public:
		Controller(int maxCells, float maxFlowRate, short wallWidth, int x, int y, bool fullScreen);
		virtual ~Controller();
		void runSimulation();
		Model* getModel();
		View* getView();
	private:
		void initCells();
		//
		Model* model;
		View* view;
		Generator* generator;
		int modeX, modeY;
		int border, maxCells;
		float maxFlowRate;
		short wallWidth;
		bool fullScreen;
};

#endif /* CONTROLLER_H_ */
