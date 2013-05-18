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

#ifndef COLOURS_H_
#define COLOURS_H_

class Colours
{
	public:
		static const unsigned int white = 0x00FFFFFF;
		static const unsigned int black = 0x00000000;
		static const unsigned int red = 0x00FF0000;
		static const unsigned int green = 0x0000FF00;
		static const unsigned int blue = 0x000000FF;
		static const unsigned int cyan = 0x0000FFFF;
		static const unsigned int yellow = 0x00FFFF00;
		static const unsigned int purple = 0x00FF00FF;
		static const unsigned int pink = 0x00FF80FF;
		static const unsigned int orange = 0x00FF8000;
		//
		static const unsigned int rmask = 0x00ff0000;
		static const unsigned int gmask = 0x0000ff00;
		static const unsigned int bmask = 0x000000ff;
		static const unsigned int amask = 0xff000000;
		//
		static int getColourFromName(string colourName)
		{
				if (colourName.compare("white") == 0)
					return Colours::white;
				if (colourName.compare("black") == 0)
					return Colours::black;
				if (colourName.compare("red") == 0)
					return Colours::red;
				if (colourName.compare("green") == 0)
					return Colours::green;
				if (colourName.compare("blue") == 0)
					return Colours::blue;
				if (colourName.compare("cyan") == 0)
					return Colours::cyan;
				if (colourName.compare("yellow") == 0)
					return Colours::yellow;
				if (colourName.compare("purple") == 0)
					return Colours::purple;
				if (colourName.compare("pink") == 0)
					return Colours::pink;
				if (colourName.compare("orange") == 0)
					return Colours::orange;
				return Colours::white;
		}

};

#endif /* COLOURS_H_ */
