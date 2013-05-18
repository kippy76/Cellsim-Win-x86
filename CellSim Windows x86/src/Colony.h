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

#ifndef COLONY_H_
#define COLONY_H_
#include "Cell.h"
#include <string>
#include <set>

using namespace std;

class Colony
{
	public:
		// Methods
		Colony();
		Colony(int maxCells, short colonyID, short strainID, int size, unsigned int colour, short splitTimeMins);
		virtual ~Colony();
		void addNewCell(float x, float y, bool isAlive, unsigned int colour, short colonyID, short splitTimeMins);
		std::set<Cell*>* getColony();
		int getSize();
		short getStrainID();
		short getColonyID();
	private:
		short strainID;
		short colonyID;
		set<Cell*> colony;
};

#endif /* COLONY_H_ */
