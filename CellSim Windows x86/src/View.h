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

#ifndef VIEW_H_
#define VIEW_H_
#include "Model.h"
#include "SDL.h"		// 2D graphics library
#include "SDL_video.h"	// 2D graphics library
#include "SDL_ttf.h"	// SDL TTF support


class View
{
	public:
		View(int x, int y, bool fullScreen, Model* model, int border);
		virtual ~View();
		void render();
		bool initGUI();
		void clearSurface(SDL_Surface* surf);
		void renderCells(Cell* cell);
		SDL_Surface* getCellSurface();
		SDL_Surface* getOverlaySurface();
	private:
		bool initFont();
		void initSurfaces();
		void renderBorder();
		void renderOverlay();
		void renderText(int x, int y, std::string text, SDL_Surface* destSurf, unsigned int r, unsigned int g, unsigned int b, bool large);
		void renderMerged();
		void drawPixel(Uint32 colour, int x, int y);
		void drawLine(int x1, int y1, int x2, int y2, SDL_Surface* surf, Uint32 colour);
		std::string iterationsToFormattedTime();
		std::string ItoS(unsigned int value);
		std::string FtoS(float value, int decimalPlaces);
		//
		int modeX, modeY;
		int border;
		Model* model;
		SDL_Surface* screenSurface;
		SDL_Surface* cellSurface;
		SDL_Surface* overlaySurface;
		TTF_Font* fontFaceLarge; // pointer to font struct
		TTF_Font* fontFaceSmall; // pointer to font struct
		Uint32 VIDEOFLAG;
};

#endif /* VIEW_H_ */
