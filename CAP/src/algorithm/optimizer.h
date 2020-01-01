#pragma once
#ifndef OPTIMIZER_H
#define OPTIMIZER_H
#include "../pch.h"

#include "../problem/problem.h"
#include "../structures/network/seg_network.h"
#include "../structures/network/crew_network.h"
#include "../algorithm/column_generation/column_generation.h"


class PosOrderSeqvec;
class OrderPosSeqvec;


//class CrewGroup;
//class EventPath;

//class GroupSearcher;

/**
 * @class Optimizer
 * @brief �Ż������
 * ��������Ż��Ļ������
 * ��������е���Column Generation�㷨
 */

class Optimizer
{
public:
	Optimizer(const Problem* problem, const CrewRules* rules/*, const Penalty* penelty*/) :
		_problem(problem),
		_rules(rules)
		/*_penalty(penelty)*/ {
	
	}
	~Optimizer();

	/**
	 * @brief �Ż��㷨��������
	 * 1.Initialize: construct crew and segment network
	 * 2.SegpathSearching: search seg path, actually, enumerate all feasible path in a single day	 
	 * 3.CrewgroupSearching: search crew groups
	 * 4.MatchGroupAndPath: to get a match which has the smallest (negtive) reduced cost. actually, get multiple path(column)
	 * 5.MasterModelSolver: construct master model according to columns got in last process, and solve linear relaxatiion problem
	 * 6.DualInfomationPassing: uapate dual information of crew and seg network according the dual info got from last process
	 * 7.Repeat step 2-5 unless optimal solution found
	 */
	void optimize();

	static el::Logger* logger;

	/// ȫ�ֽ��		
	std::vector<CrewSchedulingSolution*> soln_pool;
private:	
	/**
	 * @brief ѡ���ʼ������
	 * @param ��ʼ������
	 * ��������ʽ��������ÿ����ߵĳ�ʼ�����飬�����ɳ�ʼ��	 
	 */
	void initialCrewGroup(CrewGroup& initGroup);
	/**
	 * @brief ��segment�������������࣬����map��	 	 
	 */
	void clusterSegNode();
	/**
	 * @brief ��ֵ����Ҫ������ߵ�����segmentNode
	 * @param ��ǰ������
	 * 
	 */
	void setCurDayStartNodeSet(int curDay);
	/**
	 * @brief ����crew��״̬������������ִ��
	 * @param ��ǰ�����ʼʱ��
	 * @param ��ǰ��ľ��߽��
	 */ 
	void updateStatus(const time_t startCurDay, CrewSchedulingSolution& soln);
	
	const Problem* _problem;
	const CrewRules* _rules;
	//const Penalty* _penalty; //changed 20191229
	
	std::vector<Opt_Segment*> _optSegSet;
	std::vector<Opt_CREW*> _optCrewSet;

	Network::SegNetwork* _segNet;
	Network::CrewNetwork* _crewNet;

	/*for calculate*/
	std::map<std::string, Network::SegNodeSet> _day_segnode_map;
	std::map<time_t, Network::SegNodeSet> _daytime_segnode_map;
	
	time_t _begining_plan;
	
	Network::SegNodeSet* _cur_day_segnode_set;

	// added-20190819

	std::map<std::string, std::vector<Network::CrewNode*>> _pos_crewnodes; //position-vector<CrewNode*>
};

#endif // !OPTIMIZER_H