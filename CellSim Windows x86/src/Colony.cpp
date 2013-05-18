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

#include <string>
#include <set>
#include "Cell.h"
#include "Colony.h"

using namespace std;

Colony::Colony(int maxCells, short colonyID, short strainID, int size, unsigned int colour, short splitTimeMins)
{
	this->strainID = strainID;
	this->colonyID = colonyID;
	for (int thisCell = 0; thisCell < size; thisCell++)
	{
		colony.insert(new Cell(0, 0, true, colour, colonyID, splitTimeMins));
	}
}

Colony::~Colony()
{
	for (std::set<Cell*>::reverse_iterator thisCell = colony.rbegin(); thisCell != colony.rend(); thisCell++)
	{
		delete *thisCell;			// delete Cell object
	}
	colony.clear();
}

void Colony::addNewCell(float x, float y, bool isAlive, unsigned int colour, short colonyID, short splitTimeMins)
{
	colony.insert(new Cell(x, y, isAlive, colour, colonyID, splitTimeMins));
}

std::set<Cell*>* Colony::getColony()
{
	return &colony;
}

int Colony::getSize()
{
	return colony.size();
	int count = 0;
	for (std::set<Cell*>::iterator thisCell = colony.begin(); thisCell != colony.end(); thisCell++)
	{
		if ((*thisCell)->isAlive())
		{
			count++;
		}
	}
	return count;
}

short Colony::getStrainID()
{
	return this->strainID;
}

short Colony::getColonyID()
{
	return this->colonyID;
}
