#pragma once
#ifndef OUTPUT_HANDLER_H
#define OUTPUT_HANDLER_H
#include "..\..\..\UtilFunc.h"
#include "..\..\algorithm\column_generation\column_generation.h"
#include <iostream>
#include <sstream>
#include <fstream>

const std::vector<string> scheduleHeader = { "crewID","rank","position", "startDtLoc", "endDtLoc","dutys content<startDt-endDt-<fltId-fltNum>" };
const std::vector<string> crewStatusHeader = { "crewID","rank","position", "accumFltMin","accumCreditMin","totalFlyMin","totalCreditMint" };
const std::vector<std::string> crewStatisticHeaders = { "crewID","rank","position","wholePlanTotalFlyMint", "wholePlanTotalCreditMint" };
const std::vector<std::string> segmentStatisticHeaders = { "fltId", "fltNum", "startDtLoc","endDtLoc","depArp","arvArp" };

class OutputHandler 
{
public:
	//! ��¼����ļƻ�
	//������Ϊ���ǵİ�
	void writeSchedule(const Solution& soln, const SegNodeSet& curDaySegSet, const std::string& schFile);
	//! ��¼����crew��״̬
	//! �Գ�����Ϊ��λ
	void writeCrewStatus(const Solution& soln, const std::string& statusFile);
	//! ��¼��������ÿ��crew��״̬
	void writeCrewStatus(const vector<Opt_CREW*>& crewSet, const char* statusFile);
	
	//! ���crew��ͳ��ָ��
	//! �ܷ�ʱ����ִ��ʱ��
	void writeCrewStatistic(const vector<Opt_CREW*>& crewSet, const char* statisticCsvFile);
	//! ÿ������ĸ������(��Ҫ���δ���ǵĺ���)
	//! ������
	void writeUncoveredFlight(const SegNodeSet& allSegNodeSet, const char* statisticFile);
};

#endif // !OUTPUT_HANDLER_H

