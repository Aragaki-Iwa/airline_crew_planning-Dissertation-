#pragma once
#ifndef OPTIMIZER_H
#define OPTIMIZER_H
#include "..\pch.h"
#include "..\io\input\input_handle.h"
#include "..\algorithm\column_generation\column_generation.h"


class CrewRules;
class PosOrderSeqvec;
class OrderPosSeqvec;

class Opt_Segment;
class Opt_CREW;

class SegNetwork;
class CrewNetwork;
class CrewGroup;
class SegPath;
class GroupSearcher;

/**
 * @class Optimizer
 * @brief �Ż������
 * ��������Ż��Ļ������
 * ��������е���Column Generation�㷨
 */

class Optimizer
{
public:
	Optimizer();
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

	/*******input*******/
	/**
	 * @brief ��������
	 * @param ����ģ�����ݵļ���
	 * @param ����ģ�����ݵ�����
	 * ��csvReader�Ѿ���������ݣ�void*�ͣ�ת��Ϊ����ģ���������
	 */
	void loadData(std::map<std::string, std::vector<void*>>& dataSet, const std::vector<std::string>& objNameSet);
	/**
	 * @brief ���������򣬸���˽�г�Ա
	 * @param �������
	 */
	void loadCrewRules(CrewRules& rules);	
	/**
	 * @brief ����ͷ��ɱ�����ֵ
	 * @param �ͷ��ɱ�������
	 */
	void loadPenaltySetting(const Penalty& penaltySeeting);
	/**
	 * @brief ��ʼ�������������	 
	 */
	void init();
	/**
	 * @brief ���Ժ������������԰���	 
	 */
	void createCase();
	/// ȫ�ֽ��		
	std::vector<Solution*> soln_pool;
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
	void updateStatus(const time_t startCurDay, Solution& soln);

	InputHandler _inputHandler;
	CrewRules* _rules;
	const Penalty* _penalty;
	
	std::vector<Opt_Segment*> _optSegSet;
	std::vector<Opt_CREW*> _optCrewSet;

	SegNetwork* _segNet;
	CrewNetwork* _crewNet;	

	/*for calculate*/
	std::map<std::string, SegNodeSet> _day_segnode_map;
	std::map<time_t, SegNodeSet> _daytime_segnode_map;
	
	time_t _begining_plan;
	const int _SECONDS_ONE_DAY = 24 * 3600; //24 hour * 3600 secends
	SegNodeSet* _cur_day_segnode_set;

	// added-20190819

	std::map<std::string, std::vector<CrewNode*>> _pos_crewnodes; //position-vector<CrewNode*>
};

#endif // !OPTIMIZER_H