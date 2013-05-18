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

#include "Cell.h"
#include "Utils.h"

Cell::Cell()
{
	alive = true;
	x = y = 0;
	colonyID = 0;
}

Cell::Cell(float x, float y, bool isAlive, unsigned int colour, short colonyID, short splitTimeMins)
{
	this->x = x;
	this->y = y;
	this->alive = isAlive;
	this->colonyID = colonyID;
	this->colour = colour;
	this->mytosisTicker = 10 * splitTimeMins;
	this->mytosisTimeOriginal = this->mytosisTicker;
	int randomTime = Utils::getRandomInt(0, this->mytosisTicker / 10); // 10% either way random
	this->mytosisTicker += Utils::getRandomInt(0, 1) == 1 ? randomTime : (0 - randomTime);
	// Finally. set phase of mitosis to random for kick off
	this->mytosisTicker = Utils::getRandomInt(1, this->mytosisTicker);
}

Cell::~Cell()
{
}

void Cell::setX(float x)
{
	this->x = x;
}

void Cell::setY(float y)
{
	this->y = y;
}

void Cell::setAlive(bool alive)
{
	this->alive = alive;
}

void Cell::setColonyID(short ID)
{
	this->colonyID = ID;
}

void Cell::setColour(unsigned int colour)
{
	this->colour = colour;
}

float Cell::getX()
{
	return x;
}

float Cell::getY()
{
	return y;
}

bool Cell::isAlive()
{
	return alive;
}

Cell* Cell::getCell()
{
	return this;
}

short Cell::getColonyID()
{
	return this->colonyID;
}

unsigned int Cell::getColour()
{
	return this->colour;
}

bool Cell::mytosisPoll()
{
	this->mytosisTicker--;
	if (this->mytosisTicker < 0)
	{
		this->mytosisTicker = this->mytosisTimeOriginal;
		int randomTime = Utils::getRandomInt(0, this->mytosisTicker / 10); // 10% either way random
		this->mytosisTicker += Utils::getRandomInt(0, 1) == 1 ? randomTime : (0 - randomTime);
		return true;
	}
	return false;
}

short Cell::getOriginalSplitTimeMins()
{
	return this->mytosisTimeOriginal / 10;
}
