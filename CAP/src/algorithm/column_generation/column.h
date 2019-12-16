#pragma once
#ifndef COLUMN_H
#define COLUMN_H
#include "..\..\structures\network\seg_path.h"
#include "..\..\structures\network\crew_path.h"

/**
 * @brief ö���� �е����� 
 * ������1��relax-��Ϣ 2��duty-����
 */
enum ColumnType 
{
	relax = 0,
	duty = 1
};

/**
 * @class Column
 * @brief ʵ�ʵľ��߱���
 * ������1��duty 2��crewGroup
 */
class Column 
{
public:
	Column() {
		cost = FIXED_COST;
		type = ColumnType::duty;
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
		type = ColumnType::duty;
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