#pragma once
#ifndef CREW_GROUP_COST_CALCULATOR_H
#define CREW_GROUP_COST_CALCULATOR_H
#include "../../util/cost_indicators.h"

// ֻ����̬ʹ��
class CrewGroupCostCalculator 
{
public:
	static double calCost(std::map<utils::CrewCostType, int> penaltyMap,
		std::map<utils::CrewCostType, int> amountMap);
};

#endif // !CREW_GROUP_COST_CALCULATOR_H
