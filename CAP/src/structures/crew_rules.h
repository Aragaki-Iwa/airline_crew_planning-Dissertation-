#pragma once
#ifndef CREW_RULES_H
#define CREW_RULES_H

#include "defines.h"
#include <unordered_set>

using namespace defines;

class Opt_CREW;

static std::vector<std::string> CAP_positions{ "C1","C2", "C4", "T1", "T2", "T3", "K1", "K2", "K3" };
static std::vector<std::string> FO_positions{ "F1", "F2", "F3", "F4", "F5", "F6", "J1", "J2" };


/**
 * @class PosOrderSeqvec
 * @brief ����map���ṹΪ position-��λ-option��index
 */
class PosOrderSeqvec
{
public:
	~PosOrderSeqvec() {
		for (auto& k_v : orderSeqIdvec) {
			k_v.second.clear();
			k_v.second.shrink_to_fit();
		}
		orderSeqIdvec.clear();
	}
	std::string position;
	std::map<int, seqIdVec> orderSeqIdvec;
};
/**
 * @class OrderPosSeqvec
 * @brief ����map���ṹΪ ��λ-position-option��index
 */
class OrderPosSeqvec
{
public:
	~OrderPosSeqvec() {
		for (auto& k_v : posSeqIdvec) {
			k_v.second.clear();
			k_v.second.shrink_to_fit();
		}
		posSeqIdvec.clear();
	}
	int order;
	std::map<std::string, seqIdVec> posSeqIdvec;
};

/**
 * ��ɵ���dutyʱ�Ĺ���
 */
typedef struct HorizontalRules
{
	int minTransMin;
	int maxTransMin;
	int minOutRestMin;
	int maxOutRestMin;
	int minFlyMin;
	int maxFlyMin;
	int minDutyMin;
	int maxDutyMin;

}HORIZON_RULES;

/**
 * @class CrewRules
 * @brief ���������
 * 
 * �洢���򣬰�����1���鵥��dutyʱ�Ĺ��� 2��"7��"���� 3���������
 * �жϼ���������
 */
class CrewRules
{
public:
	CrewRules() {
		horizon_rules = new HORIZON_RULES();
	}
	void setHorizonRules(int minTransMin,
		int maxTransMin,
		int minOutRestMin,
		int maxOutRestMin,
		int minFlyMin,
		int maxFlyMin,
		int minDutyMin,
		int maxDutyMin);
	void setWeekPara(int maxCreditMinutes, int maxWeekFlyMinutes, int minDayOffMinutes, int maxDayOffMinutes/*allowOverCreditMinutes*/);
	/**
	 * @brief ��ӺϷ�����������������map
	 * @param ����rankCombination����option
	 */	
	void addRankCombination(const std::string& rankCombination);
	/**
	 * @brief ��ֵ�洢option��map	 
	 */
	void setSeqMaps();
	/**
	 * @brief ���ֵ�����������	
	 */
	void sortSeqMaps();

	/**
	 * @brief �ж�option�Ƿ�Ϸ�
	 * @param ���crew��ɵ�option
	 */
	bool isFasibleCombination(const std::vector<Opt_CREW*>& crewComb) const;

	/// ��ɵ���duty�����صĹ���
	HORIZON_RULES* horizon_rules;
	/// ���ִ��ʱ�������������day off
	int maxCreditMin;
	/// ����ܷ���ʱ�䣬���������day off
	int maxWeekFlyMin;	
	/// day off������Ϣʱ��
	int minDayOffMin;
	/// day off������Ϣʱ��
	int maxDayOffMin;
	/// ����option�ļ���
	std::vector<std::string> rankCombinationSet;
	/// ��position-order-optionSet�ṹ�洢��map
	std::map<std::string, PosOrderSeqvec*> _pos_order_seqs;
	/// ��order-position-optionSet�ṹ�洢��map
	std::map<int, OrderPosSeqvec*> _order_pos_seqs;
	/// key <�������>; value <�����������option>
	/// example: key "1CAP1FO"
	std::map<std::string, std::vector<std::string>> compo_sequences_map;
};

#endif // !CREW_RULES_H
