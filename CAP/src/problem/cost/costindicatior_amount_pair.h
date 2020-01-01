#pragma once
#ifndef COST_INDICATOR_AMOUNT_PAIR_H
#define COST_INDICATOR_AMOUNT_PAIR_H
#include "../../util/cost_indicators.h"

/**
 * @brief pair<�ɱ���ص�ָ�ָ꣬�����>
 * �漰���ɱ���������deadhead��������ֵ��ʱ���
 **/
struct CostIndicatorAmountPair
{	
	utils::EventPathCostIndicators indicator;
	unsigned value;
};

#endif // !COST_INDICATOR_AMOUNT_PAIR_H
