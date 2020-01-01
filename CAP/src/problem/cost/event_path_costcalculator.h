#pragma once
#ifndef COST_EVENTPATH_H
#define COST_EVENTPATH_H
#include "../../util/cost_indicators.h"

// ֻ����̬ʹ��
class EventPathCostCalculator
{
public:
	static double calCost(std::map<utils::EventPathCostType, int> penaltyMap, 
		std::map<utils::EventPathCostType, int> amountMap);
private:
	EventPathCostCalculator(); //ֻ����̬ʹ��
};



//class EventPathCostCalculator
//{
//public:
//	EventPathCostCalculator() {}
//	void calTotalCost() {
//		total_cost = 0;
//		total_cost = /*fly_time_costtuple.cost +*/ dhd_costtuple.cost + special_credential_costtuple.cost;
//	}
//	double getTotalCost() const {
//		return total_cost;
//	}
//	double total_cost;
//	//double fly_time_cost;
//	//double credit_time_cost;
//	//double dhd_cost;
//	//double longtime_stop_cost;
//	////����Ҫ������������⼮����...��
//	////Ϊ��ʹ��Щ���༯����һ��·�ϣ���cost������Ϊ���̶�cost(���ͷ�) * ����path�������ܵĺ�����/����Ҫ�������⺽�ࣩ������(�ٷ�����ʾ)����Ȼ����ĸ��Ϊ0
//	//double special_credential_cost;
//	//costTuple fly_time_costtuple;
//	CostTuple dhd_costtuple;
//	CostTuple special_credential_costtuple;
//};

#endif // !COST_EVENTPATH_H
