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

#include "Controller.h"
#include "Model.h"
#include "View.h"
#include "Utils.h"
#include "CAException.cpp"
#include "IO.h"

Controller::Controller(int maxCellCount, float maxFlow, short mucusWidth, int screenX, int screenY, bool full)
{
	border = 0;
	maxCells = maxCellCount;
	maxFlowRate = maxFlow;
	wallWidth = mucusWidth;
	modeX = screenX;
	modeY = screenY;
	fullScreen = full;
	model = NULL;
	view = NULL;
	generator = NULL;
}

Controller::~Controller()
{
	if (view != NULL)
	{
		delete view; // May not be instantiated if model threw exception!
	}
	delete model;
	delete generator;
}

void Controller::initCells()
{
	int x, y;
	for (unsigned int colonyIndex = 0; colonyIndex < model->getAllColonies()->size(); colonyIndex++)
	{
		/*
		* Colonies in the vector will appear in same order as they appear in
		* settings file. Start X/Y should therefore mirror order.
		*/
		Colony* thisColony = (*model->getAllColonies())[colonyIndex];
		int thisColonyID = thisColony->getColonyID();
		vector<IO::valueNode> startX = IO::getValue("Colony", "startX");
		vector<IO::valueNode> startY = IO::getValue("Colony", "startY");
		if ((startX.size() != model->getAllColonies()->size()) || (startY.size()
			!= model->getAllColonies()->size()))
		{
			throw CAException(
				"Error: settings.dat file is missing 'startX/startY' data for colony ID number "
				+ thisColonyID);
		}

		for (std::set<Cell*>::iterator cellIter =
			(*model->getAllColonies())[colonyIndex]->getColony()->begin(); cellIter
			!= (*model->getAllColonies())[colonyIndex]->getColony()->end(); cellIter++)
		{
			Cell* thisCell = *cellIter;
			if ((startX[colonyIndex].valueI == 0) && (startY[colonyIndex].valueI == 0))
			{
				x = Utils::getRandomInt(border, modeX - border);
				y = Utils::getRandomInt(border, modeY - border);
			}
			else
			{
				x = startX[colonyIndex].valueI;
				y = startY[colonyIndex].valueI;
			}
			x = generator->getNearestFreePixel(x, y, true).x;
			y = generator->getNearestFreePixel(x, y, true).y;
			thisCell->setX((float)x);
			thisCell->setY((float)y);
			view->renderCells(thisCell);
		}
	}
}

void Controller::runSimulation()
{
	model = new Model(maxCells);
	border = IO::getValue("General", "screenborder")[0].valueI;
	try
	{
		model->initModel();
		view = new View(modeX, modeY, fullScreen, model, border);
		generator = new Generator(maxCells, maxFlowRate, wallWidth, model, view, border, modeX, modeY);
	}
	catch (CAException& e)
	{
		throw CAException(e.what());
	}
	this->initCells();
	bool run = true;
	bool evolve = true;
	do
	{
		if (evolve)
		{
			evolve = generator->generate();
			model->incrementIterations();
		}
		{
			view->render();
			SDL_Event event;
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
					// Keyscan
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						run = false;
						break;
					default:
						break;
					}
				case SDL_QUIT:
					run = false;
					break;
				}
			}
		}
	}
	while (run);
}
