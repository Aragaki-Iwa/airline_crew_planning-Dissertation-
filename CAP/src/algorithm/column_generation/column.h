#pragma once
#ifndef COLUMN_H
#define COLUMN_H
#include "..\..\structures\network\seg_path.h"
#include "..\..\structures\network\crew_path.h"

/**
 * @brief 枚举类 列的类型 
 * 包括：1）relax-休息 2）duty-任务
 */
enum ColumnType 
{
	relax = 0,
	duty = 1
};

/**
 * @class Column
 * @brief 实际的决策变量
 * 包括：1）duty 2）crewGroup
 */
class Column 
{
public:
	Column() {
		cost = FIXED_COST;
		type = ColumnType::duty;
	};
	/**
	 * @brief 构造函数
	 * @param 构成该列的duty
	 * @param 构成该列的crewGroup
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
	const int FIXED_COST = 0;//100; //固定成本
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