#pragma once
#ifndef COLUMN_POOL_MANAGER
#define COLUMN_POOL_MANAGER
#include "column.h"
#include "ilcplex\ilocplex.h"
#include <vector>

class ColumnPoolManager
{
public:
	//! δ��Ϊ����������������������
	//! ��ĳһ������maxNbIterationsNonBasis�ζ�û�г�Ϊ�����������Ƴ�����
	int maxNbIterationsNonBasis = 3;
	
	void recordColumnBecomeBasis(const IloCplex& cplex, const IloNumVarArray& decisionVars);
	//! �ֱ��globalPool��ɾ�������У�������Ӧ�ı����Ƴ�������fixed��ֵΪ0��
	void removeBadColumns(ColumnPool* globalPool, IloNumVarArray* decisionVars);


private:
	//! index = index of column in global_pool
	//! value = number of column not be a basis
	std::vector<int> _num_be_non_basis;


};

#endif // !COLUMN_POOL_MANAGER

