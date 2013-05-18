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

#include "Generator.h"
#include <stdlib.h>
#include "SDL_video.h"	// 2D graphics library
#include <vector>
#include "Colours.h"
#include "Utils.h"
#include <cmath>
#include <iostream>

using namespace std;

Generator::Generator(int maxCells, float maxFlowRate, int wallWidth, Model* model, View* view, int border,
					 int modeX, int modeY)
{
	this->border = border;
	this->wallWidth = wallWidth;
	this->modeX = modeX;
	this->modeY = modeY;
	this->maxCells = maxCells;
	this->maxFlowRate = maxFlowRate;
	this->model = model;
	this->view = view;
}

Generator::~Generator()
{
	colours.clear();
}

bool Generator::generate()
{
	view->clearSurface(view->getCellSurface());
	// Returns true if simulation to continue
	for (unsigned int colonyIndex = 0; colonyIndex < model->getAllColonies()->size(); colonyIndex++)
	{
		for (std::set<Cell*>::reverse_iterator cellIter =
			(*this->model->getAllColonies())[colonyIndex]->getColony()->rbegin(); cellIter
			!= (*this->model->getAllColonies())[colonyIndex]->getColony()->rend(); cellIter++)
		{
			if ((*cellIter)->isAlive())
			{
				updateColours(*cellIter);
				physicsDeath(*cellIter);
				// Feed, supply new nutrients and get remaining nutrient level
				if (model->feed() > 1)
				{
					physicsDivide(*cellIter);
				}
				physicsFlow(*cellIter);
				physicsMove(*cellIter);
				view->renderCells(*cellIter);
			}
			else
			{
				bool breakOutFlag = false;

				/*
				* Need to delete the object, then the vector entry.
				* However, if we are on the last cell in the vector, and delete it,
				* iterator would increment past the bounds of the vector. So...
				* if we only have 1 cell, and are about to delete it, we do not want
				* to loop again, and simply break out of cell iteration. Check vector size,
				* if 1 we set a breakOut flag, otherwise leave to carry on
				*/
				if ((*this->model->getAllColonies())[colonyIndex]->getColony()->size() == 1)
				{
					breakOutFlag = true;
				}
				delete *cellIter;
				(*this->model->getAllColonies())[colonyIndex]->getColony()->erase(*cellIter);
				if (breakOutFlag)
				{
					break;
				}
			}
		}
	}
	return continueSimulationCheck();
}

void Generator::updateColours(Cell* cell)
{
	unsigned int thisColour = cell->getColour();
	for (list<unsigned int>::iterator iter = colours.begin(); iter != colours.end(); iter++)
	{
		if (*iter == thisColour)
		{
			return;
		}
	}
	colours.push_back(thisColour);
}

bool Generator::continueSimulationCheck()
{
	int cellCount = 0;
	for (unsigned int colonyIndex = 0; colonyIndex < model->getAllColonies()->size(); colonyIndex++)
	{
		cellCount += ((*model->getAllColonies())[colonyIndex])->getColony()->size();
	}	
	return cellCount == 0 ? false : (cellCount > maxCells ? false : true);
}

Coords Generator::getNearestFreePixel(int x, int y, bool includeMucusWall)
{
	Coords result;
	result.x = -1;
	result.y = -1;
	vector<Coords> pointsFree;
	for (int radius = 1; radius < modeY - (border * 2); radius++)
	{
		for (int currentX = x - radius; currentX <= x + radius; currentX++)
		{
			for (int currentY = y - radius; currentY <= y + radius; currentY++)
			{
				if ((currentX >=0) && (currentY >=0) && (currentX < modeX) && (currentY < modeY))
				{
					if ((getPixelColour(currentX, currentY) == Colours::black) || ((currentX == x) && (currentY == y)))
					{
						Coords option = { currentX, currentY };
						pointsFree.push_back(option);
					}
				}
			}
		}
		if (pointsFree.size() != 0)
		{
			// we have closest point(s) found. Pick one at random
			int chosen = Utils::getRandomInt(0, (int)(pointsFree.size() - 1));
			result.x = pointsFree[chosen].x;
			result.y = pointsFree[chosen].y;
			pointsFree.clear();
			return result; // stop search loop after radius iteration
		}
	}
	return result;
}

unsigned int Generator::getPixelColour(int x, int y)
{
	return *((Uint32 *) view->getCellSurface()->pixels + (int) y * view->getCellSurface()->pitch / 4
		+ (int) x);
}

bool Generator::isCoordsInBounds(int x, int y, bool includeMucusWall)
{
	bool okay = true;
	if (x < border)
		okay = false;
	if (x > modeX - (border + 1))
		okay = false;
	if (includeMucusWall)
	{
		if (y < border)
			okay = false;
		if (y > (modeY - (border + 1)))
			okay = false;
	}
	else
	{
		if (y < border + wallWidth)
			okay = false;
		if (y > (modeY - (border + 1) - wallWidth))
			okay = false;
	}
	return okay;
}

bool Generator::isColourEnemy(Cell* cell, unsigned int col)
{
	if (cell->getColour() == col)
		return false;
	if ((col == Colours::black) || (col == Colours::white))
		return false;
	return true;
}

void Generator::physicsMove(Cell* cell)
{
	// Move cell
	float x = cell->getX();
	float y = cell->getY();
	Coords dest = getNearestFreePixel((int)x, (int)y, true);
	if (isCoordsInBounds((int)x, (int)y, false))
	{
		x -= ((int) x - dest.x);
		y -= ((int) y - dest.y);
	}
	// Constrain limits
	y = y < border ? border : y;
	y = y > modeY - (border + 1) ? modeY - (border + 1) : y;
	if ((x < border) || (x > (modeX - (border + 1))))
	{
		cell->setAlive(false);
	}
	cell->setX(x);
	cell->setY(y);
}

void Generator::physicsDivide(Cell* cell)
{
	// Need to find nearest spare pixel location and spawn cell there - same specs as parent cell
	if (cell->mytosisPoll())
	{
		for (unsigned int loop = 0; loop < model->getAllColonies()->size(); loop++)
		{
			if ((*model->getAllColonies())[loop]->getColonyID() == cell->getColonyID())
			{
				Coords dest = getNearestFreePixel((int)cell->getX(), (int)cell->getY(), true);
				(*model->getAllColonies())[loop]->addNewCell((float)dest.x,(float) dest.y, true, cell->getColour(),
					cell->getColonyID(), cell->getOriginalSplitTimeMins());
				return;
			}
		}
	}
}

void Generator::physicsDeath(Cell* cell)
{
	int x = (int)cell->getX();
	int y = (int)cell->getY();
	if (colours.size() != 0)
	{
		if (!(model->getStrainNameForCell(cell) == "E.coli"))
		{
			for (int currentX = x - 1; currentX <= x + 1; currentX++)
			{
				for (int currentY = y - 1; currentY <= y + 1; currentY++)
				{
					if ((currentX >=0) && (currentY >=0) && (currentX < modeX) && (currentY < modeY))
					{
						unsigned int touchingCellColour = getPixelColour(currentX, currentY);
						if (isColourEnemy(cell, touchingCellColour))
						{
							cell->setAlive(false);
							return; // fail fast
						}
					}
				}
			}
		}
	}
}

void Generator::physicsFlow(Cell* cell)
{
	if (!isCoordsInBounds((int)cell->getX(), (int)cell->getY(), false))
	{
		return;
	}
	float y = cell->getY();
	float x = cell->getX();
	float numerator = abs((modeY / 2) - y);
	float denominator = (float)((modeY / 2) - border - wallWidth);
	float p = abs((numerator / denominator) - 1);
	float c = maxFlowRate * (sqrt(2 * p - (p * p)));
	cell->setX(x - c);
	if ((x - c < border) || (x - c > (modeX - (border + 1))))
	{
		cell->setAlive(false);
	}
}
