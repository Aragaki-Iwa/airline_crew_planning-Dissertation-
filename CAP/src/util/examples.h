#pragma once
#ifndef EXAMPLES_H
#define EXAMPLES_H
/*!
 * \file examles.h
 * \brief class Examples
 *
 * -random set
 *	-some segments with special properties that require crew with special skills
 *	-some crews with special skills
 *	-some combination of crews
 * -try set
 *	-several different group of crew rules parameters
 *  -several different optimization parameters like penalty cost
 *
 * \author dubing xiang
 * \version 0.1.0
 * \date 20191217
 **/

#include "../structures/defines.h"
#include "../structures/crew_rules.h"
#include "../easylogging/easylogging++.h"

#include <set>

namespace utils {
	
	
	/**
	 * @class Example
	 * @brief ���ɲ�ͬ������
	 *
	**/
	class Example
	{
	public:
		Example() {};
		~Example() {};

		static el::Logger* logger;

		/*
		 * @brief ���ѡ��ĳЩ��������������������
		 * @detail �������ԵĻ�����ζ�Ŷ�Ӧ�ĺ�����Ҫ�߱��������ʵ�crew������
		 *
		 * @param
		 *
		 **/
		std::set<std::string> randomCreatePlateauAirptSet(const std::vector<std::string>& airportSet, 
			const int nbOfPlateauAirport);
		void randomSetCrewSkillls(std::vector<Opt_CREW*>* optCrewSet, 
			const std::set<defines::Skill>& skillSet, 
			const double percent = 0.1);
		/// TODO
		void randomSetRankCombination(CrewRules* rules);

	private:
		

	};
}


#endif // !EXAMPLES_H
