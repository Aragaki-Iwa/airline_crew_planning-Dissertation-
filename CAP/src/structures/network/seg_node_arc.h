#pragma once
#ifndef SEGMENT_NODE_ARC_H
#define SEGMENT_NODE_ARC_H
#include "INetwork.h"

class BASE;
class CrewRules;
class Opt_Segment;

namespace Network {
	class SegNode;
	class SegArc;
	class Label;

	using SegNodeSet = std::vector<SegNode*>;
	using SegArcSet = std::vector<SegArc*>;
	/**
	 * @class SegNode
	 * @brief segment�ڵ��� �̳���INode
	 */
	class SegNode : public INode
	{
	public:
		SegNode();
		SegNode(Opt_Segment& optSeg);
		virtual ~SegNode();
		/**
		 * @brief ���ýڵ�����
		 * @param �ڵ�����
		 */
		virtual void setNodeType(NodeType type);

		SegArcSet outArcSet;
		SegArcSet inArcSet;

		Opt_Segment* optSegment;
		std::string depStation;
		std::string arvStation;
		//std::string name;
		time_t startDtUtc;
		time_t startDtLoc;
		time_t endDtUtc;
		time_t endDtLoc;
		int taskMin;


		//std::vector<Label*> labelSet;
		Label* label;

	};

	/**
	 * @class SegArc
	 * @brief segment��صĻ�-�̳���IArc
	 */
	class SegArc : public IArc
	{
	public:
		SegArc(SegNode* startNode, SegNode* endNode);
		virtual ~SegArc();
		/**
		 * @brief ���û�������
		 * @param ��������
		 */
		virtual void setArcType(ArcType type);
		/**
		 * @brief ���û��ĳ���
		 * @param ���ĳ���
		 */
		virtual void setArcLen(int length);

		SegNode* startNode;
		SegNode* endNode;
	};

	/**
	 * @class Label
	 * @brief �����-ö��dutyʱ��¼������Ϣ
	 */
	class Label
	{
	public:
		Label() {
			accumuFlyMin = 0;
			accumuWorkMin = 0;
			accumuCost = 0;
			preLabel = NULL;
			preArc = NULL;
		}
		int accumuFlyMin;
		int accumuWorkMin;
		int accumuCost;
		Label* preLabel;
		SegArc* preArc;
	};

}// end namespace Network

#endif // !SEGMENT_NODE_ARC_H
