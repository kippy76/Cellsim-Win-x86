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

#ifndef UTILS_H_
#define UTILS_H_

#include <cstdlib>

class Utils
{
	public :
		static int getRandomInt(int min, int max)
		{
			int ranNum = rand() % (max - min + 1) + min;
			return ranNum;
		}
};

#endif /* UTILS_H_ */
