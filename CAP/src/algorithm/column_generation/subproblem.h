#pragma once
#ifndef SUBPROBLEM_H
#define SUBPROBLEM_H
#include "../../pch.h"
#include "../crewgroup_searcher.h"
#include "../segpath_searcher.h"
#include "../../structures/network/crew_network.h"
#include "../../structures/network/seg_network.h"
#include "../../structures/generic/csvClassesTransOptimizable.h"
#include "../../structures/crew_rules.h"
#include "column.h"
#include "../../structures/param_setting/cost_parameters.h"


/**
 * @class SubProblem
 * @brief �����������
 * ������
 * 1��ö�پ��ߵ������п���duty 
 * 2��CG����������Ϊduty�������еĳ�����
 * 3��duty�ͳ����������ϣ���ѡreduced costС��0������
 */
class SubProblem 
{
public:
	SubProblem(CrewNetwork& crewNet, SegNetwork& segNet, const CrewRules& rules);
	~SubProblem();
	/**
	 * @brief set��ʼ������
	 */
	void setInitialGroups(std::vector<CrewGroup*>& initialGroups);
	/**
	 * @brief ö�����п���duty
	 * �����������ִֻ��һ��
	 */	
	void findSegPaths();
	/**
	 * @brief ����duty�ĳɱ�
	 * @param ����ͷ��ɱ�����
	 * 
	 */
	void setPathStatus(const Penalty& penalty); //TODO������
	/**
	 * @brief ���þ��ߵ����븲�ǵ�segment����
	 * �ȵ�����˽�к����õ����������segPath
	 * Ȼ��ִ�иú���
	 */		
	void setCurDaySegSet();
	/**
	 * @brief ���þ��ߵ����븲�ǵ�segment��index
	 * ��ֵÿ��segment��ȫ�ֵ�segment�����е�λ�ã����±��ʾ	 
	 */
	void setIndexOfCurSeg();
	/**
	 * @brief ���duty����������
	 * duty�Ƿ���Ҫ�������ʵ���Ա����
	 */
	void labelSpecialSegPath(std::vector<std::string>& specialAirports);
	/**
	 * @brief ��duty����ȷ���	 
	 */	
	void groupingSegPathByComposition();
	
	
	/*��ֵ�Ĺ��ܲ�Ӧ����subproblemʵ�֣���ֵӦ����Ϊsubproblem��һ������*/	
	/**
	 * @brief ����duty_set��crew_set��flymint�ľ�ֵ����Ԥ��
	 */
	void estimateMeanFlyMin();
	/**
	 * @brief ��ͬrank�и��ԵĹ��ƾ�ֵ, ����duty_set��crew_set��flymint�ľ�ֵ����Ԥ��
	 * ���㹫ʽ��mean_fly_min_rank[i] = sum(seg.fly_min * required_num_rank[i]) / total_num_rank[i]
	 */		
	void estimateMeanFlyMinPrecisly();
	/**
	 * @brief ��ù��Ƶķ�ʱ��ֵ
	 */
	int getMeanFlyMin() const { return _mean_fly_mint; }
	/**
	 * @brief ���¶�ż�۸�
	 * @param segment����Լ����Ӧ�ĳ���
	 * @param crewָ��Լ����Ӧ�ĳ���
	 */
	void updateDuals(std::vector<double>& segCoverDuals, std::vector<double>& crewAssignDuals);
	/**
	 * @brief ������ż���ӽϴ�ĳ�����
	 */
	void findGroups();
	
	/**
	 * @brief ��ù��Ƶķ�ʱ��ֵ	 
	 * create new columns, add to this->_local_pool
	 * match crew group and segment path
	 * to get columns that have small negetive reduced cost
	 * actually, is assign group for each segpath in _seg_path_searcher._segpath_set
	 */
	void matchGroupAndPath();	
	/**
	 * @brief ����crewGroup����ƥ��Group��segpath�õ�����
	 * TODO
	 */	
	void findColumnSet();
	
	/**
	 * @brief Ϊcrew�����Ϣ���߱������൱���˹�����
	 *
	 */	
	void addRestColumns();

	/*output for master problem*/
	
	/**
	 * @brief ��õ�ǰ�븲�ǵ�segment����
	 * ֻ����һ�Σ��������ʼ����ʱ��
	 */	
	std::vector<Opt_Segment*>& getCurDaySegSet() { return _cur_day_seg_set; }
	/**
	 * @brief ���ÿ�����õ�������
	 * 
	 */
	ColumnPool& getCurLocalPool() { return _local_pool; }

private:		
	/**
	 * @brief ��������Գɱ�-����ֵ��ʽ
	 * @param duty�ķ�ʱ 
	 * @param ��duty��Եĳ�����
	 * ����Ԥ����flymint��ֵ����������column��cost
	 * cost = sum(crewGroup's flyMin + dutyFlyMin - meanFlyMin)	
	 */
	int calBalanceCost(const int dutyFlyMin, CrewGroup& crewGroup);
	/**
	 * @brief ��������Գɱ�-������ʽ
	 * @param duty�ķ�ʱ
	 * @param ��duty��Եĳ�����
	 * ����Ԥ���ĸ�rank��flymint��ֵ����������column�ľ���cost
	 */	
	int calBalanceCostByVariance(const int dutyFlyMin, CrewGroup& crewGroup);
	/**
	 * @brief ��������Գɱ�-������ʽ
	 * ��opt_crew�Ķ�ż�۸�������
	 */	
	void sort_pos_crew_set();
	/**
	 * @brief ������������Ϸ���crewGroup
	 * @param ��ȵ�������Ϣ����"1CAP1FO"
	 * @param ������� compositionName������Ӧ�ĺϷ������鼯��
	 */	
	void searchGroupByComposition(const std::string compositionName, std::vector<CrewGroup*>* crewGroupSet);
	/**
	 * @brief �жϳ������duty�Ƿ�������
	 * @param ������
	 * @param duty
	 * @return true if ����Լ��:1��ʱ�� 2���ռ� 3����� 4����������
	 */
	bool isMatchable(CrewGroup& group, SegPath& segPath);

	std::map<std::string, std::vector<CrewNode*>> _pos_crewnodes_map;
	std::map<std::string, int> _rank_to_num_crew_map;

	const CrewRules* _rules;
	std::vector<Opt_Segment*> _cur_day_seg_set;
	std::vector<CrewNode*> _crewnode_set; //TODO:δ��ʼ��
	ColumnPool _local_pool; //ÿ��������õ�������

	GroupSearcher _group_searcher;
	SegPathSearcher _seg_path_searcher;
	std::vector<SegPath*> _cur_day_path_set;
	
	int _mean_fly_mint;
	std::map<std::string, int> _rank_to_mean_fly_mint;
	/*std::vector<double> _seg_cover_duals;
	std::vector<double> _crew_assign_duals;
	std::vector<double> _balance_flytime_duals;
	std::vector<double> _balance_resttime_duals;*/

	std::map<std::string, std::vector<SegPath*>> _compo_mode_segpath_set;


};

#endif // !SUBPROBLEM_H

