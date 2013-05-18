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

#include "Nutrient.h"

Nutrient::Nutrient()
{
	this->supply = 1;
	this->supplyCrate = 0;
	this->supplyFrate = 0;
}

Nutrient::Nutrient(float supplyRatePerGen, float cellConsumptionRate, float initialQuantity)
{
	this->supply = initialQuantity;
	this->supplyCrate = cellConsumptionRate;
	this->supplyFrate = supplyRatePerGen;
}

Nutrient::~Nutrient()
{
}

float Nutrient::pollSupply(int totalCells)
{
	this->supply += supplyFrate / (float)totalCells;	// Supply new nutrients
	if (this->supply > this->supplyCrate)
	{
		this->supply -= this->supplyCrate;			// And feed for each cell
	}
	this->supply = this->supply < 0 ? 0 : this->supply;
	return this->supply;
}

void Nutrient::setConsumptionRatePerCell(float cellConsumptionRate)
{
	this->supplyCrate = cellConsumptionRate;
}

void Nutrient::setSupplyRate(float supplyRate)
{
	this->supplyFrate = supplyRate;
}

float Nutrient::getNutrientLevel()
{
	return this->supply;
}
