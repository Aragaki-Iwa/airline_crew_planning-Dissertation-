#pragma once
#ifndef SEGPATH_SEARCHER_H
#define SEGPATH_SEARCHER_H
#include "../pch.h"
#include "../structures/network/seg_network.h"
#include "../structures/path/seg_path.h"

class CrewRules;

class SegPathSearcher
{
public:
	//��֮ǰд��PathFinder::createCurResource�Ĺ���Ӧ�ý�������ģ�鴦��
	//���õ���_s���Ѿ�����õ��������
	//SegPathSearcher(SegNetwork& segNet, SegNode& s, CrewRules& rules);
	~SegPathSearcher();
	
	void init(Network::SegNetwork& segNet, Network::SegNode& s, const CrewRules& rules);
	void reset(Network::SegNode& s);
	void search();
	std::vector<EventPath*>& getPathSet() { return _segpath_set; }
	void clear();

private:
	Network::SegNetwork* _net;
	Network::SegNode* _s;
	//SegNode* _t; _t is not necessary
	const CrewRules* _rules;
	//! output all the feasible (single day) paths 
	std::vector<EventPath*> _segpath_set;

	/* For enumerate */


	std::map<Network::SegArc*, int> _visited_by_path;
	//! initialize _s
	void initStartNode();
	void enumerateByDFS();

	void extend(const Network::Label& curLabel, const Network::SegArc& curArc, Network::Label* nextLabel);
	void updateLabel(Network::Label& curLabel, Network::SegArc& curArc, Network::Label* nextLabel);
	//�����ʱ��Լ��	
	bool isValidDuration(const Network::Label& curLabel);
	//! ���ﵽ��ֹ������˵������ǰ�ڵ����һ�ڵ��Ѿ�����Ŀ���·���ˡ�
	//���������ټ�������һ��ڵ����죬������Ҫ��������һ��
	bool isMetTermination(const Network::Label& curLabel);
	
	////�����·���Ƿ�����dhdԼ��
	////! ��Ҫ�Ǽ��dhd�Ƿ��������start_node or end_node
	//bool isValidDeahhead(Label& label);
		
	EventPath* backtrack(Network::Label& endLabel);
};


#endif // !SEGPATH_SEARCHER_H