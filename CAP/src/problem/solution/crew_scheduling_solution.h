#pragma once
#ifndef CREW_SCHEDULING_SOLUTION_H
#define CREW_SCHEDULING_SOLUTION_H

#include "../../algorithm/column_generation/column.h"

/**
 * @class Solution
 * @brief ���ߵĽ�
 * �������Ž��еľ��߱��������Ž��Ŀ�꺯��ֵ
 */
class CrewSchedulingSolution
{
public:
	/*Solution() {
		column_pool = new ColumnPool;
	}
	~Solution() {
		delete column_pool;
	}*/
	void setTotalObjValue(double objValue) { _obj_value = objValue; }
	double getTotalObjValue() const { return _obj_value; }
	
	ColumnPool& getColumnPool() { return _column_pool; }

private:
	ColumnPool _column_pool;
	double _obj_value;
};


#endif // !CREW_SCHEDULING_SOLUTION_H
