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

#ifndef IO_H_
#define IO_H_

#include <string>
#include <vector>

using namespace std;

class IO
{
	public:
		struct valueNode
		{
				string sectionName;
				string key;
				short type;
				string valueC;
				int valueI;
				float valueF;
				unsigned int valueU;
		};
		static vector<IO::valueNode> getValue(string section, string key);
	private:
		static vector<IO::valueNode> parseFile();
		static void stripSpaces(string &data);
		static bool safefloat(char *c, float &f);

};

#endif /* IO_H_ */
