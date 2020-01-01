#pragma once
#ifndef SEG_NETWORK_H
#define SEG_NETWORK_H
#include "INetwork.h"
#include "seg_node_arc.h"
#include <string>


namespace Network {
	
	
	/**
	 * @class SegNetwork
	 * @brief segment������-�̳���INetwork
	 */
	class SegNetwork : public INetwork
	{
	public:
		SegNetwork(std::vector<Opt_Segment*>* optSegSet, std::vector<BASE*>* baseSet, CrewRules* rules);

		virtual ~SegNetwork();
		/**
		 * @brief ��������
		 */
		virtual void createNetwork();
		/**
		 * @brief resource and sink node updated every day
		 */
		void updateResourceAndSink();
		/**
		 * @brief vitual arcs updated every day
		 */
		void updateVirtualArcs(SegNodeSet& startNodeSet);

		SegNode* resource;
		SegNode* sink;
		SegNodeSet nodeSet;
		SegArcSet arcSet;

	private:
		std::vector<Opt_Segment*>* _optSegSet;
		std::vector<BASE*>* _baseSet;
		CrewRules* _rules;
		std::vector<SegNode*> _base_nodeset;

		//void setOptSegNodeSet(/*const std::vector<Opt_Segment*>& optSegSet, std::vector<BASE*>& baseSet*/);
		/**
		 * @brief ����segment�ڵ�
		 */
		void createOptSegNodes(/*const std::vector<Opt_Segment*>& optSegSet*/);
		/**
		 * @brief ����segment�ڵ㣬����dhd�ڵ�
		 */
		void createDeadheadNodes();
		/**
		 * @brief sort by startTime ascending
		 */
		void sortNodeSet();
		/**
		 * @brief create segnode for base, store these node in _base_nodeset
		 */
		void createBaseNodes();

		//create only once

		/**
		 * @brief ����segnode֮������ӻ�
		 */
		void createOptSegArcs(/*const CrewRules& rules*/);
		/**
		 * @brief �ж�����ͬһ���͵�segment֮���Ƿ������
		 */
		bool isSameFleetConnectble(const Opt_Segment& seg1, const Opt_Segment& seg2);
		/**
		 * @brief �ж�������ͬ���͵�segment֮���Ƿ������
		 */
		bool isDiffFleetConnectble(const Opt_Segment& seg1, const Opt_Segment& seg2, const int minTransMint);
		/**
		 * @brief �������س��˳˻�
		 */
		void createBaseArcs();
		/**
		 * @brief add extra long arcs for node whose in/out degree is little
		 */
		void addLongArcs();
		/**
		 * @brief delete segnode whose indegree or outdegree equals zero�� and output to file
		 */
		void removeIsolatedNode();

	};
}

#endif // !SEG_NETWORK_H