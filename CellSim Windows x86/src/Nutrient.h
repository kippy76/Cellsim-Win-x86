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

#ifndef NUTRIENT_H_
#define NUTRIENT_H_

class Nutrient
{
	public:
		Nutrient();
		Nutrient(float supplyRate, float cellConsumptionRate, float startingQuantity);
		virtual ~Nutrient();
		float pollSupply(int totalCells);
		void setConsumptionRatePerCell(float cellConsumptionRate);
		void setSupplyRate(float supplyRate);
		float getNutrientLevel();
	private:
		float supply;
		float supplyCrate;
		float supplyFrate;
};

#endif /* NUTRIENT_H_ */
