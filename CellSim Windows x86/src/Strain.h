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

#ifndef STRAIN_H_
#define STRAIN_H_
#include <map>
#include <string>

using namespace std;

class Strain
{
	public:
		Strain();
		virtual ~Strain();
		void addStrain(string name, int ID);
		int getStrainID(string name);
		string getStrainName(int strainID);
		map<string, int>* getStrains();
	private:
		map<string, int> Strains;
};

#endif /* STRAIN_H_ */
