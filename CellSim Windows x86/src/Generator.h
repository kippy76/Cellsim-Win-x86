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

#ifndef EVOLVER_H_
#define EVOLVER_H_
#include "Colony.h"
#include "Model.h"
#include"View.h"
#include "SDL_video.h"	// 2D graphics library
#include <vector>
#include <list>

using namespace std;

struct Coords
{
		int x, y;
};

class Generator
{
	public:
		Generator(int maxCells, float maxFlowRate, int wallWidth, Model* model, View* view, int border,
				int modeX, int modeY);
		virtual ~Generator();
		bool generate();
		Coords getNearestFreePixel(int x, int y, bool includeMucusWall);
	private:
		void updateColours(Cell* cell);
		bool continueSimulationCheck();
		unsigned int getPixelColour(int x, int y);
		bool isCoordsInBounds(int x, int y, bool includeMucusWall);
		bool isColourEnemy(Cell* cell, unsigned int col);
		void physicsMove(Cell* cell);
		void physicsDivide(Cell* cell);
		void physicsDeath(Cell* cell);
		void physicsFlow(Cell* cell);
		//
		int border;
		int wallWidth;
		int modeX, modeY;
		list<unsigned int> colours;
		int maxCells;
		float maxFlowRate;
		Model* model;
		View* view;
};

#endif /* EVOLVER_H_ */
