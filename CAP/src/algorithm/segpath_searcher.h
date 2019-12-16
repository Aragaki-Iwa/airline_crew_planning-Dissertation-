#pragma once
#ifndef SEGPATH_SEARCHER_H
#define SEGPATH_SEARCHER_H
#include "../pch.h"



class SegNetwork;
class SegPath;
class SegNode;
class SegArc;
class Label;

class CrewRules;

class SegPathSearcher
{
public:
	//��֮ǰд��PathFinder::createCurResource�Ĺ���Ӧ�ý�������ģ�鴦��
	//���õ���_s���Ѿ�����õ��������
	//SegPathSearcher(SegNetwork& segNet, SegNode& s, CrewRules& rules);
	~SegPathSearcher();
	
	void init(SegNetwork& segNet, SegNode& s, CrewRules& rules);
	void reset(SegNode& s);
	void search();
	std::vector<SegPath*>& getPathSet() { return _segpath_set; }
	void clear();

private:
	SegNetwork* _net;
	SegNode* _s;
	//SegNode* _t; _t is not necessary
	CrewRules* _rules;
	//! output all the feasible (single day) paths 
	std::vector<SegPath*> _segpath_set;

	/* For enumerate */


	std::map<SegArc*, int> _visited_by_path;		
	//! initialize _s
	void initStartNode();
	void enumerateByDFS();

	void extend(const Label& curLabel, const SegArc& curArc, Label* nextLabel);	
	void updateLabel(Label& curLabel, SegArc& curArc, Label* nextLabel);
	//�����ʱ��Լ��	
	bool isValidDuration(const Label& curLabel);
	//! ���ﵽ��ֹ������˵������ǰ�ڵ����һ�ڵ��Ѿ�����Ŀ���·���ˡ�
	//���������ټ�������һ��ڵ����죬������Ҫ��������һ��
	bool isMetTermination(const Label& curLabel);
	
	////�����·���Ƿ�����dhdԼ��
	////! ��Ҫ�Ǽ��dhd�Ƿ��������start_node or end_node
	//bool isValidDeahhead(Label& label);
		
	SegPath* backtrack(Label& endLabel);
};


#endif // !SEGPATH_SEARCHER_H