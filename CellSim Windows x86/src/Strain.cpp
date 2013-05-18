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

#include "Strain.h"
#include <map>
#include <string>

using namespace std;

Strain::Strain()
{
}

Strain::~Strain()
{
	Strains.clear();
}

void Strain::addStrain(string name, int ID)
{
	map<string, int>::iterator iter;
	iter = Strains.find(name);
	if (iter == Strains.end())
	{
		Strains[name] = ID;
	}
}

int Strain::getStrainID(string name)
{
	map<string, int>::iterator iter;
	iter = Strains.find(name);
	return iter == Strains.end() ? -1 : Strains[name];
}

string Strain::getStrainName(int strainID)
{
	for (map<string, int>::iterator iter = Strains.begin(); iter != Strains.end(); iter++)
	{
		if (iter->second == strainID)
		{
			return iter->first;
		}
	}
	return "";
}

map<string, int>* Strain::getStrains()
{
	return &Strains;
}
