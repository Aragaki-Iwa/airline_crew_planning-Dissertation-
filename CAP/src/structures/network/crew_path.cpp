#include "crew_path.h"
#include "crew_network.h"
#include "../../structures/generic/csvClassesTransOptimizable.h"

CrewGroup::~CrewGroup() {
	_crewNodeSequence.clear();
}

double CrewGroup::getCost() const {
	return _crewsPrice.getTotalPrice();
}
void CrewGroup::computeCost() {
	
	_crewsPrice.fly_balance_price = 0;
	for (const auto& node : _crewNodeSequence) {
		_crewsPrice.fly_balance_price += node->price;
	}	
	_crewsPrice.calTotalPrice();
}
void CrewGroup::setCrewGroup() {
	for (const auto& node : _crewNodeSequence) {
		_crewGroup.emplace_back(node->optCrew);
	}
}

void CrewGroup::setCrewIndexSet(/*const std::vector<Opt_CREW*>& optCrewSet*/) {
	/*auto begin = optCrewSet.begin();
	auto end = optCrewSet.end();
	for (const auto& crewnode : _crewNodeSequence) {
		auto pos = std::find(begin, end, crewnode->optCrew);
		int index = pos - begin;
		optcrew_id_set.emplace_back(index);
	}*/
	for (const auto& crewnode : _crewNodeSequence) {
		optcrew_id_set.emplace_back(crewnode->optCrew->getIndex());
	}

}
void CrewGroup::setBasicProperties() {	
	auto first_status = _crewNodeSequence.front()->optCrew->workStatus;		
	max_total_fly_mint = first_status->accumuFlyMin;
	max_credit_mint =first_status->accumuCreditMin;	
	endDtLoc = first_status->endDtLoc;
	curStation = first_status->restStation;
	std::string skill;
	spetialCredentials[skill] = 1;
	
	std::map<std::string, int> rank_num;
	std::stringstream ranks_str;

	for (const auto& crewnode : _crewNodeSequence) {	
		spetialCredentials[skill] *= crewnode->optCrew->getSkillSet()[skill];
		
		auto temp_status = crewnode->optCrew->workStatus;		
		time_t temp_end_loc = temp_status->endDtLoc;
		endDtLoc = temp_end_loc > endDtLoc ? temp_end_loc : endDtLoc; //Group��endDtLoc == ���а�����crew������endDtLoc
		curStation = temp_status->restStation == "" ? curStation : temp_status->restStation;

		int temp_fly_mint = temp_status->accumuFlyMin;
		int temp_credit_mint = temp_status->accumuCreditMin;
		max_total_fly_mint = temp_fly_mint > max_total_fly_mint ? temp_fly_mint : max_total_fly_mint;
		max_credit_mint = temp_credit_mint > max_credit_mint ? temp_credit_mint : max_credit_mint;

		//��ȡ�����Ϣ
		++rank_num[crewnode->optCrew->getCurRank()];
	}

	//�����漰��map��key�������ַ���"CAP"С��"FO"��
	//������ͬ��rank������Ҫ������compoMode���Ӧ
	for (const auto& k_v : rank_num) {
		if (k_v.first == "CAP") {
			ranks_str << k_v.second << k_v.first;
		}
		else if (k_v.first == "FO") {
			ranks_str << k_v.second << k_v.first;
		}
	}
	this->compo_mode = &compoModeMap[ranks_str.str()];

}
