#include "column_pool_manager.h"
#include <memory>

//! ���Ҳ����жϱ����Ƿ��ǻ������ķ���
//! ��reduced cost����ѡ������
void ColumnPoolManager::recordColumnBecomeBasis(const IloCplex& cplex, const IloNumVarArray& decisionVars) {
	for (size_t i = 0; i < _num_be_non_basis.size(); i++) {
		if (cplex.getBasisStatus(decisionVars[i]) != IloCplex::BasisStatus::Basic) { //NotABasicStatus
			_num_be_non_basis[i] += 1;
		}
	}
}

void ColumnPoolManager::removeBadColumns(ColumnPool* globalPool, IloNumVarArray* decisionVars) {
	assert(globalPool->size() == decisionVars->getSize());

	ColumnPool::iterator pool_begin = globalPool->begin();		
	//int count = 0;
	for (size_t i = 0; i < _num_be_non_basis.size(); i++) {		
		if (_num_be_non_basis[i] >= maxNbIterationsNonBasis) {
			// remove column i from global pool			
			//globalPool->erase(pool_begin + i - count);
			//++count;
			
			// set var = 0
			(*decisionVars)[i].setBounds(0.0, 0.0);
		}
	}
	// TODO: reset num_be_non_basis
	//_num_be_non_basis

}