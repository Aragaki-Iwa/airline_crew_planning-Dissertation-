#pragma once
#ifndef MASTER_PROBLEM_H
#define MASTER_PROBLEM_H
#include "column.h"
#include "..\..\structures\network\crew_network.h"
#include "..\..\structures\network\seg_network.h"
#include "..\..\structures\generic\csvClassesTransOptimizable.h"
#include "ilcplex\ilocplex.h"
#include <memory>


const int PENALTY_UNCOVER = 200000;

/**
 * @class MasterProblem 
 * @brief ������-ָ������
 * 
 */
class MasterProblem 
{
public:
	MasterProblem();		
	~MasterProblem();

	/**	 
	 * @brief ���û�������
	 *
	 */
	void initSetting();
	/**
     * @brief ��ʼ���������     
     * @param ��ʼ���г�
	 * @param Ҫ���ǵ�segment����
	 * @param Ҫָ�ɵ�crew����
     */
	void init(ColumnPool* columnpool_ptr, std::vector<Opt_Segment*>& segSet, std::vector<CrewNode*>& crewNodeSet);
	/**
	 * @brief ��¼crew����ǰ�ĳ�ʼ��ʱ
	 *
	 */	
	void initParameters();	
	/**
	 * @brief ����cplex����ģ��
	 */
	void buildModel();
	/**
	 * @brief ����cplex���ģ���ļ�
	 * @param ��ǰ�������id
	 * @param ��ǰ������������
	 */
	void exportModel(const std::string& curDayStr, int iter);
	/**
	 * @brief ����cplex���ģ��
	 */
	int solve();
	/**
	 * @brief ����cplex������ļ�
	 * @param ��ǰ�������id
	 * @param ��ǰ������������
	 */
	void writeSoln(const std::string& curDayStr, int iter);
	/**
	 * @brief ���Ŀ�꺯��ֵ
	 */
	double getObjValue() const { return _objValue; }
	/**
	 * @brief ���segment��ż�۸�
	 */
	std::vector<double>& getSegCoverDuals();
	/**
	 * @brief ���crew��ż�۸�
	 */
	std::vector<double>& getCrewAssignDuals();
	/**
	 * @brief ���·�����߱����ļ���
	 */
	IloNumVarArray& getPathDvar() { return _dvars_path; }
	/**
	 * @brief ���segmentδ���Ǿ��߱����ļ���
	 */
	IloNumVarArray& getUncoverDvar() { return _dvars_uncover; }

	/**
	 * @brief ������е�ģ����
	 * @param ���м���
	 */
	void addNewColumns(ColumnPool& columnpool_ptr);

	ColumnPool* global_pool; //������ռ���м���
	IloModel _model;
	IloCplex _cplex;
	
private:
	/**
	 * @brief end all except _env
	 */	
	void end();
	/**
	 * @brief ���Ŀ�꺯����ģ��
	 * ������1��duty����С�ɱ��ܺ� 2��������Ŀ��-��С����
	 */
	void addObjFunction();
	/**
	 * @brief ���Լ����ģ��
	 * ������1��segment����Լ�� 2��crewָ��Լ��
	 */
	void addConstraints2();
	
	IloEnv _env;
	
	IloObjective _obj;
	double _objValue;
	IloNumVarArray _dvars_path; //·�����߱���
	IloNumVarArray _dvars_uncover; //·�����߱���

	/*IloNumVar _dvar_upper_flytime;
	IloNumVar _dvar_lower_flytime;*/
	/*IloNumVar _dvar_upper_seg_num;
	IloNumVar _dvar_lower_seg_num;*/

	IloRangeArray _constraints_all;
	IloRangeArray _constraints_segcover;
	IloRangeArray _constraints_crewassign;
	/*IloRangeArray _constraints_blance_u;
	IloRangeArray _constraints_blance_l;*/

	std::map<int, IloRange> _seg_index_cover_constraint;
	std::map<int, IloRange> _crew_index_assign_constraint;

	//std::vector<double> cost;
	std::vector<int> _init_crew_fly_mint;

	std::vector<Opt_Segment*>* _seg_set;
	std::vector<CrewNode*>* _crewnode_set;
	size_t _seg_num;
	size_t _crew_num;

	std::vector<double> seg_cover_duals;
	std::vector<double> crew_assign_duals;
};


#endif // !MASTER_PROBLEM_H