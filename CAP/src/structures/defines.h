#pragma once
#ifndef DEFINES_H_
#define DEFINES_H_
#include "../util/cost_indicators.h"

#include <string>
#include <vector>
#include <map>


namespace defines 
{
	using Skill = std::string;

	using seqIdVec = std::vector<int>; ///< ���seq��_rankCombinationSet�е�id

	const int kSECONDS_ONE_DAY = 24 * 3600; //24 hour * 3600 secends

	/*using EventPathCostIndicatorValueMap = std::map<utils::EventPathCostIndicators, double>;
	using CrewCostIndicatorValueMap = std::map<utils::CrewCostIndicators, double>;*/
	
}



#endif // !DEFINES_H_
