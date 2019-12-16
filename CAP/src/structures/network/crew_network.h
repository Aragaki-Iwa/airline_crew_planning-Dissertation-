#pragma once
#ifndef CREW_NETWORK_H
#define CREW_NETWORK_H
#include "INetwork.h"
#include "../../pch.h"

class Opt_CREW;
class CrewRules;

class CrewNode;
class CrewArc;

using CrewNodeSet = std::vector<CrewNode*>;
using CrewArcSet = std::vector<CrewArc*>;

class CrewNode :public INode
{
public:
	CrewNode() {};
	CrewNode(Opt_CREW* optCrew);
	virtual ~CrewNode();
	virtual void setNodeType(NodeType type);

	void setPrice(double price);
	CrewArcSet outArcSet;
	CrewArcSet inArcSet;

	Opt_CREW* optCrew;
	double price;

	//bool visited;
};

class CrewArc :public IArc
{
public:
	CrewArc(CrewNode* startNode, CrewNode* endNode);
	virtual ~CrewArc();
	virtual void setArcType(ArcType type);
	virtual void setArcLen(int length);

	CrewNode* startNode;
	CrewNode* endNode;
};


class CrewNetwork :public INetwork
{
public:
	CrewNetwork(std::vector<Opt_CREW*>* optCrewSet, CrewRules* rules) {
		_optCrewSet = optCrewSet;
		_rules = rules;

		resource = new CrewNode();
		sink = new CrewNode();
	}
	virtual ~CrewNetwork();
	virtual void createNetwork();
	//! �ؽ����磬ÿһ����ߺ�crew�����ڵػ�仯������ֻ�����ڵ���ͬ��crew��������
	void rebuildNetwork();
	CrewNode* resource;
	CrewNode* sink;

	CrewNodeSet nodeSet;
	CrewArcSet arcSet;

private:
	std::vector<Opt_CREW*>* _optCrewSet;
	CrewRules* _rules;

	std::map<std::string, std::vector<CrewNode*>> _pos_nodeset_map;
	void clusterCrewNode();

	void setOptCrewNodeSet();
	void createOptCrewNodes();

	void createOptCrewArcs();
	void createVirtualArcs();
};

#endif // !CREW_NETWORK_H