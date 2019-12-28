#pragma once
#ifndef COLUMN_GENERATION_H
#define COLUMN_GENERATION_H
#include "../../pch.h"
#include "../../problem/solution/crew_scheduling_solution.h"

#include "master_problem.h"
#include "subproblem.h"
#include "column_generation_module.h"

#include "ilcplex/ilocplex.h"

const int MAX = 1000 * 1000 * 1000;
const int MAX_NUM_ITER = 300;
const int REQUIRE_CAVERAGE_RATE = 0.95; //���Ҫ�ﵽ�ĸ����ʣ����ﵽ�󣬲��ܿ�ʼ��������
const int FREQUENCY_SOLVE_MIP = 20; //���ﵽREQUIRE_CAVERAGE_RATE��ÿFREQUENCY_SOLVE_MIP�ε�������һ��������


/**
 * @class ColumnGeneration
 * @brief �������㷨��
 * �������㷨�����ܣ�����������������������Ͷ��ߵĵ���
 */
class CrewSchedulingColumnGenerationModule :public AbstractColumnGenerationModule
{
public:
	CrewSchedulingColumnGenerationModule();
	~CrewSchedulingColumnGenerationModule();

	

	/**
	 * @brief ��ʼ�����ߵ��������
	 * @param ��ǰ������������
	 * @param ��ʼ������
	 * @param ����Ա����	  
	 * @param segment����
	 * @param �������
	 * @param �ͷ��ɱ�����
	 */
	void init(/*ColumnPool& initialPool*/int curDay, std::vector<CrewGroup*>& initialGroups, 
			  CrewNetwork& crewNet, 
			  SegNetwork& segNet, 
			  const CrewRules& rules,
			  const Penalty& penaltySetting);
	/**
	 * @brief ���������
	 */
	void solve();
	/**
	 * @brief �õ���ǰ���߽׶ε����Ž�
	 */
	CrewSchedulingSolution getBestSoln() { return *_best_solution_pool.front(); }
	
private:

	void solveMasterProblem() override;
	void solveSubProblem() override;
	void updateDuals() override;
	bool terminate() override;

	/**
	 * @brief �жϸ������Ƿ��㹻��
	  @return true if �����ʴﵽREQUIRE_CAVERAGE_RATE
	 */	 
	bool isCoverageHigh();
	/**
	 * @brief �ж�LP�Ƿ����������
	 * @return true if LP�ɳڽ����������
	 */	
	bool isFeasibelSoln(IloNumVarArray& dvars);
	/**
	 * @brief �ж�LP�Ƿ����������
	 * @return return 1 if solve mip succeed
	 */	
	int solveMIP();
	/**
	 * @brief ��ÿ��н�
	 * @param ����ֵ�Ľ�
	 * ��mip����Ŀ��н��������ֵ��soln
	 */
	void getFeasibleSolution(CrewSchedulingSolution* soln);

	std::string _cur_day_str;

	CrewNetwork* _crew_net;
	SegNetwork* _seg_net;
	const CrewRules* _rules;
	const Penalty* _penalty;
	std::vector<CrewNode*>* _crew_node_set;
	std::vector<SegNode*>* _seg_node_set;

	MasterProblem* _master;
	SubProblem* _sub_pro;
	IloModel _mip_model;
	IloCplex _mip_cplex;

	std::vector<CrewSchedulingSolution*> _solution_pool; //��������
	std::vector<CrewSchedulingSolution*> _best_solution_pool; //��ý��

	ColumnPool* _global_pool;
	double _lb;
	double _ub;
	int _max_num_iter;
	int _frequency_solve_mip = FREQUENCY_SOLVE_MIP;


	int _num_uncoverd_segments;
	int _num_rest_crews;


};
#endif // !COLUMN_GENERATION_H