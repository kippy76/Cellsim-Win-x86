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

#include "View.h"
#include "Colours.h"
#include <math.h>		// sqrt function
#include <vector>
#include "SDL_ttf.h"	// SDL TTF support
#include <sstream>
#include "CAException.cpp"

View::View(int x, int y, bool fullScreen, Model* model, int border)
{
	VIDEOFLAG = SDL_SWSURFACE;
	if (fullScreen)
	{
		VIDEOFLAG = VIDEOFLAG | SDL_FULLSCREEN;
	}
	modeX = x;
	modeY = y;
	this->border = border;
	this->model = model;
	if (!initGUI())
	{
		string errorText =  "Error: Video Failed To Initialise.\n";
		errorText += SDL_GetError();
		throw CAException(&errorText[0]);
	}
	initSurfaces();
	initFont();
}

View::~View()
{
	try
	{
		SDL_FreeSurface(cellSurface);
		SDL_FreeSurface(overlaySurface);
		TTF_CloseFont(fontFaceLarge);
		TTF_CloseFont(fontFaceSmall);
		TTF_Quit();
	}
	catch (std::exception exc)
	{
	}
	SDL_Quit();
}

void View::render()
{
	clearSurface(screenSurface);
	clearSurface(overlaySurface);
	renderBorder();
	renderOverlay();
	renderMerged();
	SDL_Flip(screenSurface);
}

void View::renderBorder()
{
	if (border > 0)
	{
		drawLine(border - 1, border - 1, modeX - border, border - 1, overlaySurface, Colours::white);
		drawLine(modeX - border, modeY - border, border - 1, modeY - border, overlaySurface, Colours::white);
	}
}

void View::renderCells(Cell* cell)
{
	int x, y;
	unsigned int colour;
	x = (int)cell->getX();
	y = (int)cell->getY();
	colour = cell->getColour();
	drawPixel(colour, x, y);
}

void View::renderOverlay()
{
	// Iterate over all colonies, get the strainID/size and plot
	std::vector<Colony*> allColonies = *(model->getAllColonies());
	int lineHeight = 18;
	int lineCount = 0;
	map<string, int>* strainMap = model->getAllStrains();
	map<string, int>::const_iterator strainIter;
	string colonyStrainName;
	for (strainIter = strainMap->begin(); strainIter != strainMap->end(); strainIter++)
	{
		int cellCount = 0;
		for (unsigned int colonyNo = 0; colonyNo < allColonies.size(); colonyNo++)
		{
			colonyStrainName = model->getStrain(*allColonies[colonyNo]);
			if (colonyStrainName == strainIter->first)
			{
				cellCount += allColonies[colonyNo]->getSize();
			}
		}
		renderText(border + 20, (border + 20 + (lineCount * lineHeight)),
				strainIter->first + " : " + ItoS(cellCount), overlaySurface, 255, 255, 255, false);
		lineCount++;
	}
	renderText(border + 20, (border + 20 + (lineCount * lineHeight)),
			"Nutr. : " + FtoS(model->getAgar()->getNutrientLevel(), 2), overlaySurface, 255, 255, 255, false);
	lineCount++;
	renderText(border + 20, (border + 20 + (lineCount * lineHeight)),
			"Gens. : " + ItoS(model->getIterations()) + " " + iterationsToFormattedTime(), overlaySurface,
			255, 255, 255, false);
	lineCount++;
	// Render outer box
	int height = lineCount * lineHeight;
	int width = 220;
	drawLine(border + 18, border + 18, width + 18, border + 18, overlaySurface, Colours::white);
	drawLine(width + 18, border + 18, width + 18, border + 18 + height, overlaySurface, Colours::white);
	drawLine(width + 18, border + 18 + height, border + 18, border + 18 + height, overlaySurface,
			Colours::white);
	drawLine(border + 18, border + 18 + height, border + 18, border + 18, overlaySurface, Colours::white);
}

void View::renderText(int x, int y, std::string text, SDL_Surface* destSurf, unsigned int r, unsigned int g,
		unsigned int b, bool large)
{
	SDL_Surface* txtSurface = NULL;
	SDL_Rect txtArea;
	SDL_Color convCol;
	convCol.r = r;
	convCol.g = g;
	convCol.b = b;
	txtSurface = large ? TTF_RenderText_Blended(fontFaceLarge, &text[0], convCol) : TTF_RenderText_Blended(
			fontFaceSmall, &text[0], convCol);
	if (txtSurface == NULL)
	{
		return;
	}
	// Got text surface, update screen...
	txtArea.x = x;
	txtArea.y = y;
	txtArea.w = txtSurface->w;
	txtArea.h = txtSurface->h;
	SDL_BlitSurface(txtSurface, NULL, destSurf, &txtArea);
	SDL_FreeSurface(txtSurface);
}

void View::renderMerged()
{
	SDL_BlitSurface(cellSurface, NULL, screenSurface, NULL);
	SDL_BlitSurface(overlaySurface, NULL, screenSurface, NULL);
}

void View::drawPixel(Uint32 colour, int x, int y)
{
	*((Uint32 *) cellSurface->pixels + (int) y * cellSurface->pitch / 4 + (int) x) = colour;
}

void View::drawLine(int x1, int y1, int x2, int y2, SDL_Surface* surf, Uint32 colour)
{
	double x = x2 - x1;
	double y = y2 - y1;
	double length = sqrt(x * x + y * y);
	double addx = x / length;
	double addy = y / length;
	x = x1;
	y = y1;
	for (double i = 0; i < length; i += 1)
	{
		Uint32 *bufp;
		bufp = (Uint32 *) surf->pixels + (int) y * surf->pitch / 4 + (int) x;
		*bufp = colour;
		x += addx;
		y += addy;
	}
}

bool View::initGUI()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return false;
	}
	atexit(SDL_Quit);
	char envContents1[] = "SDL_VIDEO_CENTERED=1";
	SDL_putenv(envContents1);
	screenSurface = SDL_SetVideoMode(modeX, modeY, 32, VIDEOFLAG);
	if (screenSurface == NULL)
	{
		return false;
	}
	SDL_WM_SetCaption("CellSim - Dundee iGEM 2012 - Christopher Walker", NULL);
	return true;
}

void View::initSurfaces()
{
	SDL_PixelFormat& fmt = *(screenSurface->format);
	cellSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, modeX, modeY, fmt.BitsPerPixel, fmt.Rmask,
			fmt.Gmask, fmt.Bmask, fmt.Amask);
	overlaySurface = SDL_CreateRGBSurface(SDL_SWSURFACE, modeX, modeY, fmt.BitsPerPixel, fmt.Rmask,
			fmt.Gmask, fmt.Bmask, fmt.Amask);
	SDL_SetColorKey(cellSurface, SDL_SRCCOLORKEY, SDL_MapRGB(cellSurface->format, 0, 0, 0));
	SDL_SetColorKey(overlaySurface, SDL_SRCCOLORKEY, SDL_MapRGB(overlaySurface->format, 0, 0, 0));
	SDL_SetAlpha(cellSurface, 0, 0);
	SDL_SetAlpha(overlaySurface, 0, 0);
}

void View::clearSurface(SDL_Surface* surf)
{
	SDL_FillRect(surf, NULL, 0x000000);
}

SDL_Surface* View::getCellSurface()
{
	return cellSurface;
}

SDL_Surface* View::getOverlaySurface()
{
	return overlaySurface;
}

bool View::initFont()
{
	if (TTF_Init() == -1)
	{
		printf("Unable to initialise SDL_ttf: %s \n", TTF_GetError());
		return 1;
	}
	if (((fontFaceSmall = TTF_OpenFont("font.ttf", 14)) == NULL) || ((fontFaceLarge = TTF_OpenFont(
			"font.ttf", 16)) == NULL))
	{
		printf("Unable to load TTF font\n");
		return 1;
	}
	return 0;
}

std::string View::iterationsToFormattedTime()
{
	unsigned int totalGens = model->getIterations();
	unsigned int totalMins = totalGens / 10;
	unsigned int mins = totalMins % 60;
	unsigned int hrs = (totalMins / 60) % 60;
	return "[" + ItoS(hrs) + "h:" + ItoS(mins) + "m]";
}

std::string View::ItoS(unsigned int value)
{
	std::stringstream ss;
	ss << value;
	return ss.str();
}

std::string View::FtoS(float value, int decimalPlaces)
{
	std::stringstream ss;
	ss.precision(decimalPlaces);
	ss.setf(ios::fixed, ios::floatfield);
	ss << value;
	return ss.str();
}
