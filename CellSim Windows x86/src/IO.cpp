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

#include "IO.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

vector<IO::valueNode> IO::parseFile()
{
	vector<valueNode> sectionList;
	ifstream file("settings.dat", ios::in);
	string textLine = "";
	string currentSectionName = "";
	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, textLine);
			// PARSE
			if (textLine.length() == 0)
			{
				continue;
			}
			if ((textLine[0] == '[') && (textLine[textLine.length() - 1] == ']'))
			{
				currentSectionName = textLine.substr(1, textLine.length() - 2);
				getline(file, textLine);
			}
			if ((textLine.length() != 0) && (textLine[0] != '#'))
			{
				valueNode* ns = new valueNode();
				ns->key = "";
				ns->sectionName = "";
				ns->type = 0;
				ns->valueC = "";
				ns->valueF = 0;
				ns->valueI = 0;
				ns->valueU = 0;
				ns->sectionName = currentSectionName;
				string key = textLine.substr(0, textLine.find_first_of('='));
				string value = textLine.substr(textLine.find_first_of('=') + 1);
				stripSpaces(key);
				stripSpaces(value);
				ns->key = key;
				// Convert to either char/int/float/uint & store
				float floatTest;
				if (!safefloat(&value[0], floatTest))
				{
					ns->valueC = value;
					ns->type = 1;
				}
				else
				{
					ns->valueF = floatTest; // FLOAT
					ns->type = 4;
					int intTest = (int) floatTest;
					unsigned int uintTest = (unsigned int) floatTest;
					if ((unsigned int) intTest == uintTest)
					{
						ns->valueI = intTest;
						ns->type = 2;
					}
					else
					{
						ns->valueU = uintTest;
						ns->type = 3;
					}
				}
				sectionList.push_back(*ns);
				delete ns;
			}
		}
	}
	file.close();
	return sectionList;
}

vector<IO::valueNode> IO::getValue(string section, string key)
{
	vector<valueNode> sectionList = IO::parseFile();
	vector<valueNode> results;
	stripSpaces(section);
	stripSpaces(key);
	for (unsigned int sec = 0; sec < sectionList.size(); sec++)
	{
		if (sectionList[sec].sectionName == section)
		{
			if (sectionList[sec].key == key)
			{
				results.push_back(sectionList[sec]);
			}
		}
	}
	if (results.size() == 0)
	{
		valueNode* nullData = new valueNode();
		nullData->key = "";
		nullData->sectionName = "";
		nullData->type = 0;
		nullData->valueC = "";
		nullData->valueF = 0;
		nullData->valueI = 0;
		nullData->valueU = 0;
		results.push_back(*nullData);
		delete nullData;
	}
	return results;
}

bool IO::safefloat(char *c, float &f)
{
	bool neg = false;
	if (*c == '-')
		neg = true;
	if (neg)
		++c;
	if (*c == '\0')
		return false;
	f = 0;
	while (*c != '\0' && *c != '.')
	{
		if (*c < '0' || *c > '9')
			return false;
		f = f * 10 + *c++ - '0';
	}
	if (*c == '.')
	{
		double weight = 1;
		while (*++c != '\0')
		{
			if (*c < '0' || *c > '9')
				return false;
			f += (float)((*c - '0') / (weight *= 10));
		}
	}
	if (neg)
		f = -f;
	return true;
}

void IO::stripSpaces(string &data)
{
	size_t startpos = data.find_first_not_of(" \t");
	size_t endpos = data.find_last_not_of(" \t");
	if ((string::npos == startpos) || (string::npos == endpos))
		data = "";
	else
		data = data.substr(startpos, endpos - startpos + 1);
}

