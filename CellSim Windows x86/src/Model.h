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

#ifndef MODEL_H_
#define MODEL_H_
#include "Colony.h"
#include "Strain.h"
#include "Nutrient.h"
#include <vector>

using namespace std;

class Model
{
	public:
		Model(unsigned int maxCells);
		virtual ~Model();
		void initModel();
		vector<Colony*>* getAllColonies();
		string getStrain(Colony& colony);
		map<string, int>* getAllStrains();
		string getStrainNameForCell(Cell* cell);
		void addCell(int x, int y, bool isAlive, unsigned int colour, int colonyID, int splitTimeMins);
		void incrementIterations();
		unsigned int getIterations();
		Nutrient* getAgar();
		int getTotalCellCount();
		int feed();
	private:
		bool go;
		vector<Colony*> colonies;
		Strain* strains;
		unsigned int iterations;
		Nutrient* agar;
		unsigned int maxCells;
};

#endif /* MODEL_H_ */
