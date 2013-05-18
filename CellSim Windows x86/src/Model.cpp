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

#include "Model.h"
#include "Colours.h"
#include <vector>
#include "IO.h"
#include "CAException.cpp"

using namespace std;

Model::Model(unsigned int maxCellCount)
{
	maxCells = maxCellCount;
}

Model::~Model()
{
	delete strains;
	for (unsigned int colIdx = 0; colIdx < colonies.size(); colIdx++)
	{
		delete colonies[colIdx];
	}
	colonies.clear();
	delete agar;
}

void Model::initModel()
{
	strains = new Strain();
	vector<IO::valueNode> strainNames = IO::getValue("Strain", "name");
	vector<IO::valueNode> strainIDs = IO::getValue("Strain", "id");
	int strainCount = strainNames.size();
	if (strainCount == 0)
	{
		throw CAException("Error: No strains specified in input file.");
	}
	for (int loopa = 0; loopa < strainCount; loopa++)
	{
		strains->addStrain(strainNames[loopa].valueC, strainIDs[loopa].valueI);
		//strains->addStrain("C.diff", 2);
	}
	vector<IO::valueNode> colonyIDs = IO::getValue("Colony", "colonyid");
	vector<IO::valueNode> colonyStrainIDs = IO::getValue("Colony", "strainid");
	vector<IO::valueNode> colonySizes = IO::getValue("Colony", "size");
	vector<IO::valueNode> colonyColours = IO::getValue("Colony", "colour");
	vector<IO::valueNode> colonyTimes = IO::getValue("Colony", "mitosismins");
	for (unsigned int col = 0; col < colonyIDs.size(); col++)
	{
		short colID = (short)colonyIDs[col].valueI;
		short strID = (short)colonyStrainIDs[col].valueI;
		int colSize = colonySizes[col].valueI;
		int colCol = Colours::getColourFromName(colonyColours[col].valueC);
		short mitMins = (short)colonyTimes[col].valueI;
		colonies.push_back(new Colony(maxCells, colID, strID, colSize, colCol, mitMins));
	}
	iterations = 0;
	agar = new Nutrient(IO::getValue("Nutrients", "supplypergen")[0].valueF,
			IO::getValue("Nutrients", "consumptionpercellpergen")[0].valueF,
			IO::getValue("Nutrients", "initialvolume")[0].valueF);
}

vector<Colony*>* Model::getAllColonies()
{
	return &colonies;
}

string Model::getStrain(Colony& colony)
{
	int ID = colony.getStrainID();
	return strains->getStrainName(ID);
}

map<string, int>* Model::getAllStrains()
{
	return strains->getStrains();
}

string Model::getStrainNameForCell(Cell* cell)
{
	int colonyIDofCell = cell->getColonyID();
	int strainIDofCell = -1;
	for (unsigned int loop = 0; loop < colonies.size(); loop++)
	{
		if (colonies[loop]->getColonyID() == colonyIDofCell)
		{
			strainIDofCell = colonies[loop]->getStrainID();
		}
	}
	return strains->getStrainName(strainIDofCell);
}

void Model::addCell(int x, int y, bool isAlive, unsigned int colour, int colonyID, int splitTimeMins)
{
	for (unsigned int loop = 0; loop < colonies.size(); loop++)
	{
		if (colonies[loop]->getColonyID() == colonyID)
		{
			colonies[loop]->addNewCell((float)x, (float)y, isAlive, colour, colonyID, splitTimeMins);
			return;
		}
	}
}

void Model::incrementIterations()
{
	iterations++;
}

unsigned int Model::getIterations()
{
	return iterations;
}

Nutrient* Model::getAgar()
{
	return this->agar;
}

int Model::getTotalCellCount()
{
	int cellCount = 0;
	for (unsigned int loop = 0; loop < colonies.size(); loop++)
	{
		cellCount += colonies[loop]->getColony()->size();
	}
	return cellCount;
}

int Model::feed()
{
	// Feeds, supplies new nutrients, and returns remaining nutrients
	return (int)(agar->pollSupply(getTotalCellCount()));
}
