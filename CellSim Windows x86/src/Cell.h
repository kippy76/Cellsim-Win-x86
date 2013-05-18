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

#ifndef CELL_H_
#define CELL_H_

class Cell
{
	public:
		// Methods
		Cell();
		Cell(float x, float y, bool isAlive, unsigned int colour, short colonyID, short splitTimeMins);
		virtual ~Cell();
		void setX(float);
		void setY(float);
		void setAlive(bool);
		void setColonyID(short);
		void setColour(unsigned int colour);
		float getX();
		float getY();
		bool isAlive();
		short getColonyID();
		Cell* getCell();
		unsigned int getColour();
		bool mytosisPoll();
		short getOriginalSplitTimeMins();
	private:
		bool alive;
		float x, y;
		short colonyID;
		unsigned int colour;
		short mytosisTicker;
		short mytosisTimeOriginal;
};

#endif /* CELL_H_ */
