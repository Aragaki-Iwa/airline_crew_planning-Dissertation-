#pragma once
#ifndef COLUMN_H
#define COLUMN_H
#include "../../structures/network/seg_path.h"
#include "../../structures/network/crew_path.h"


/**
 * @class Column
 * @brief ʵ�ʵľ��߱���
 * ������1��duty 2��crewGroup
 */
class Column 
{
public:
	/*
	 * @brief ö���� �е�����
	 * ������0-relax 1-duty
	 **/
	enum ColumnType
	{
		RELAX,
		DUTY,
		PRE_ASSIGNED
	};

	Column() {
		cost = FIXED_COST;
		type = ColumnType::DUTY;
	};
	/**
	 * @brief ���캯��
	 * @param ���ɸ��е�duty
	 * @param ���ɸ��е�crewGroup
	 */
	Column(SegPath& segPath, CrewGroup& crewGroup) {
		_segpath = &segPath;
		_crewgroup = &crewGroup;

		cost = FIXED_COST;
		type = ColumnType::DUTY;
	}
	~Column() {
		_segpath = NULL;
		_crewgroup = NULL;
	}
	

	double cost;
	const int FIXED_COST = 0;//100; //�̶��ɱ�
	double reduced_cost;

	SegPath* _segpath;
	CrewGroup* _crewgroup;

	ColumnType type;
};
using ColumnPool = std::vector<Column*>;

//class ColumnPool
//{
//public:
//	std::vector<Column*> column_pool;
//};

#endif // !COLUMN_H