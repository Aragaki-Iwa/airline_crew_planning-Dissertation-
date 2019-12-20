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

#include "../io/input/input_handle.h"




namespace util {
	
	
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

		/*
		 * @brief ���ѡ��ĳЩ��������������������
		 * @detail �������ԵĻ�����ζ�Ŷ�Ӧ�ĺ�����Ҫ�߱��������ʵ�crew������
		 *
		 * @param
		 *		 
		 * @attention
		 * @warning
		 * @exception
		 *
		 **/
		void randomCreateSpecialAirptSet();
		void randomCreateCrewSkillls();
		void randomCreateRankCombination();

	private:

	};


}


#endif // !EXAMPLES_H
